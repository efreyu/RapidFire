// Rapid Fire Game. All Rights Reserved.

#include "Components/RFHealthComponent.h"

FName URFHealthComponent::HealthComponentName(TEXT("HealthComponent"));

URFHealthComponent::URFHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void URFHealthComponent::BeginPlay()
{
    Super::BeginPlay();
    Health = MaxHealth;
}
