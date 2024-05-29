// Rapid Fire Game. All Rights Reserved.

#include "Components/RFHealthComponent.h"
#include "GameFramework/Actor.h"

FName URFHealthComponent::HealthComponentName(TEXT("HealthComponent"));

URFHealthComponent::URFHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void URFHealthComponent::BeginPlay()
{
    Super::BeginPlay();
    Health = MaxHealth;
    if (auto const Owner = GetOwner())
    {
        Owner->OnTakeAnyDamage.AddDynamic(this, &URFHealthComponent::OnTakeAnyDamage);
    }
}

void URFHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, UDamageType const* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
}
