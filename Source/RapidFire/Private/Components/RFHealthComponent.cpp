// Rapid Fire Game. All Rights Reserved.

#include "Components/RFHealthComponent.h"
#include "Dev/RFFireDamageType.h"
#include "Dev/RFIceDamageType.h"
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
    if (auto const Owner = GetOwner())
    {
        Owner->OnTakeAnyDamage.AddDynamic(this, &URFHealthComponent::OnTakeAnyDamage);
    }
}

void URFHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, UDamageType const* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
    if (DamageType && (DamageType->IsA(URFFireDamageType::StaticClass()) || DamageType->IsA(URFIceDamageType::StaticClass())))
    {
        // OnFireDamage.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Actor: '%s', Fire or ice"), *GetName());
    }
}
