// Rapid Fire Game. All Rights Reserved.

#include "Components/RFHealthComponent.h"

URFHealthComponent::URFHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void URFHealthComponent::BeginPlay()
{
    Super::BeginPlay();
}

void URFHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
