// Rapid Fire Game. All Rights Reserved.

#include "Components/RFHealthComponent.h"
#include "GameFramework/Actor.h"

URFHealthComponent::URFHealthComponent()
    : MaxHealth(100.0f)
    , Health(0.0f)
{
    PrimaryComponentTick.bCanEverTick = false;
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

void URFHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, UDamageType const* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    if (Damage <= 0.0f || IsDead())
    {
        return;
    }
    Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
    OnHealthChanged.Broadcast(Health);
    if (IsDead())
    {
        OnDeath.Broadcast();
    }
}
