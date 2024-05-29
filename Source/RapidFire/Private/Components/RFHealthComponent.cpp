// Rapid Fire Game. All Rights Reserved.

#include "Components/RFHealthComponent.h"

URFHealthComponent::URFHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void URFHealthComponent::BeginPlay()
{
    Super::BeginPlay();
    Health = MaxHealth;
}
