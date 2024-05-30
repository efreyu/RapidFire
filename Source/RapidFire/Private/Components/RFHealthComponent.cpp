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
    , LastHitTime(0.0)
{
    PrimaryComponentTick.bCanEverTick = true;
}

void URFHealthComponent::BeginPlay()
{
    Super::BeginPlay();
    Health = MaxHealth;
    OnHealthChanged.Broadcast(Health);
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
    Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
    OnHealthChanged.Broadcast(Health);
    LastHitTime = GetWorld()->TimeSeconds;
    if (AutoHealTimerHandle.IsValid())
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
            if (GetWorld()->TimeSeconds - LastHitTime > AutoHealDelay)
            {
                if (Health < MaxHealth)
                {
                    Health = FMath::Clamp(Health + AutoHealHealth, 0.0f, MaxHealth);
                    OnHealthChanged.Broadcast(Health);
                }
            }
        });
        GetWorld()->GetTimerManager().SetTimer(AutoHealTimerHandle, TimerDelegate, 1.f, true);
    }
}
