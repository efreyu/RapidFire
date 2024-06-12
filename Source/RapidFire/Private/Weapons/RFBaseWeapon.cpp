// Rapid Fire Game. All Rights Reserved.

#include "Weapons/RFBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

ARFBaseWeapon::ARFBaseWeapon()
{
    SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComponent");
    PrimaryActorTick.bCanEverTick = false;
    SetRootComponent(SkeletalMeshComponent);
}

void ARFBaseWeapon::BeginPlay()
{
    Super::BeginPlay();
    check(SkeletalMeshComponent);
}

void ARFBaseWeapon::StartFire()
{
    // Check this should be implemented in derived classes
    checkNoEntry();
}

void ARFBaseWeapon::StopFire()
{
    // Check this should be implemented in derived classes
    checkNoEntry();
}

void ARFBaseWeapon::MakeShot()
{
    // Check this should be implemented in derived classes
    checkNoEntry();
}

APlayerController* ARFBaseWeapon::GetPlayerController() const
{
    auto const Player = Cast<ACharacter>(GetOwner());
    if (!Player)
        return nullptr;
    return Player->GetController<APlayerController>();
}

bool ARFBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
    auto const Character = Cast<ACharacter>(GetOwner());
    if (!Character)
        return false;

    if (Character->IsPlayerControlled())
    {
        auto const Controller = Character->GetController<APlayerController>();
        if (!Controller)
            return false;

        Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
        return true;
    }
    return false;
}

bool ARFBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
    FVector ViewLocation;
    FRotator ViewRotation;
    if (!GetPlayerViewPoint(ViewLocation, ViewRotation))
        return false;

    TraceStart = ViewLocation;
    TraceEnd = TraceStart + ViewRotation.Vector() * ShootDirectionRange;
    return true;
}

void ARFBaseWeapon::MakeHit(FHitResult& HitResult, FVector const& TraceStart, FVector const& TraceEnd) const
{
    FCollisionQueryParams CollisionQueryParams;
    CollisionQueryParams.AddIgnoredActor(GetOwner());
    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionQueryParams);
}

FVector ARFBaseWeapon::GetMuzzleLocation() const
{
    return SkeletalMeshComponent->GetSocketTransform(MuzzleSocketName).GetLocation();
}
