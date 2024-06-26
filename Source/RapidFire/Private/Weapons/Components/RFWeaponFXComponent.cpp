// Rapid Fire Game. All Rights Reserved.

#include "Weapons/Components/RFWeaponFXComponent.h"

URFWeaponFXComponent::URFWeaponFXComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void URFWeaponFXComponent::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void URFWeaponFXComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
