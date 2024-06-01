// Rapid Fire Game. All Rights Reserved.

#include "Weapons/RFBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"

ARFBaseWeapon::ARFBaseWeapon()
    : SkeletalMeshComponent(CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComponent"))
{
    PrimaryActorTick.bCanEverTick = false;
    SetRootComponent(SkeletalMeshComponent);
}

void ARFBaseWeapon::BeginPlay()
{
    Super::BeginPlay();
}

void ARFBaseWeapon::Fire()
{
    UE_LOG(LogTemp, Warning, TEXT("Actor: '%s', Debug info FIRE"), *GetName());
}
