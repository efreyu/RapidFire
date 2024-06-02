// Rapid Fire Game. All Rights Reserved.

#include "Weapons/RFBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"

ARFBaseWeapon::ARFBaseWeapon()
    : SkeletalMeshComponent(CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComponent"))
{
    PrimaryActorTick.bCanEverTick = false;
    SetRootComponent(SkeletalMeshComponent);
}

void ARFBaseWeapon::BeginPlay()
{
    Super::BeginPlay();
    check(SkeletalMeshComponent);
}

void ARFBaseWeapon::Fire()
{
    UE_LOG(LogTemp, Warning, TEXT("Actor: '%s', Debug info FIRE"), *GetName());
    MakeShot();
}

void ARFBaseWeapon::MakeShot()
{
    if (!GetWorld())
        return;
    // FTransform const SocketTransform = SkeletalMeshComponent->GetSocketTransform(RapidFire::Constants::Socket::MuzzleSocket);
}
