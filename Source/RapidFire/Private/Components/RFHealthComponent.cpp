// Rapid Fire Game. All Rights Reserved.

#include "Components/RFHealthComponent.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

URFHealthComponent::URFHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void URFHealthComponent::BeginPlay()
{
    Super::BeginPlay();
    SetHealth(MaxHealth);
    if (auto const Owner = GetOwner())
    {
        Owner->OnTakeAnyDamage.AddDynamic(this, &URFHealthComponent::OnTakeAnyDamage);
        if (auto const Character = Cast<ACharacter>(Owner))
        {
            Character->LandedDelegate.AddDynamic(this, &URFHealthComponent::OnGroundLanded);
        }
    }
}

void URFHealthComponent::EndPlay(EEndPlayReason::Type const EndPlayReason)
{
    if (AutoHealTimerHandle.IsValid())
    {
        GetWorld()->GetTimerManager().ClearTimer(AutoHealTimerHandle);
    }
}

void URFHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, UDamageType const* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    if (Damage <= 0.0f || IsDead())
    {
        return;
    }
    SetHealth(Health - Damage);
    if (GetWorld() && AutoHealTimerHandle.IsValid())
    {
        GetWorld()->GetTimerManager().ClearTimer(AutoHealTimerHandle);
    }
    if (IsDead())
    {
        OnDeath.Broadcast();
    }
    else if (IsAutoHeal)
    {
        FTimerDelegate TimerDelegate;
        TimerDelegate.BindLambda([this]() {
            if (!IsAutoHeal || IsDead() || !GetWorld())
            {
                return;
            }
            if (Health < MaxHealth)
            {
                SetHealth(Health + AutoHealHealth);
            }
            if (FMath::IsNearlyEqual(Health, MaxHealth) || IsDead())
            {
                GetWorld()->GetTimerManager().ClearTimer(AutoHealTimerHandle);
            }
        });
        GetWorld()->GetTimerManager().SetTimer(AutoHealTimerHandle, TimerDelegate, AutoHealTime, true, AutoHealDelay);
    }
}

void URFHealthComponent::SetHealth(float const NewHealth)
{
    Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
    OnHealthChanged.Broadcast(Health);
}

void URFHealthComponent::OnGroundLanded(FHitResult const& Hit)
{
    auto const Character = Cast<ACharacter>(GetOwner());
    if (!Character)
        return;
    auto const FallVelocity = -Character->GetCharacterMovement()->Velocity.Z;
    UE_LOG(LogTemp, Warning, TEXT("Actor: '%s', Debug info %f"), *GetName(), FallVelocity);
    if (FallVelocity < LandedDamageVelocity.X)
        return;

    auto const Damage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocity);
    Character->TakeDamage(Damage, FDamageEvent{}, nullptr, nullptr);
}
