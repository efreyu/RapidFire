// Rapid Fire Game. All Rights Reserved.

#include "Components/RFHealthComponent.h"
#include "GameFramework/Actor.h"

URFHealthComponent::URFHealthComponent()
    : MaxHealth(100.0f)
    , IsAutoHeal(false)
    , AutoHealDelay(3.f)
    , AutoHealTime(1.f)
    , AutoHealHealth(1.f)
    , Health(0.0f)
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
