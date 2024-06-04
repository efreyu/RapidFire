// Rapid Fire Game. All Rights Reserved.

#include "Weapons/RFBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

ARFBaseWeapon::ARFBaseWeapon()
    : SkeletalMeshComponent(CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComponent"))
    , MuzzleSocketName(RapidFire::Constants::Socket::MuzzleSocket)
    , DamageAmount(10.f)
{
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
    auto const PlayerController = GetPlayerController();
    if (!PlayerController)
        return false;
    PlayerController->GetPlayerViewPoint(ViewLocation, ViewRotation);
    return true;
}

bool ARFBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
    FVector ViewLocation;
    FRotator ViewRotation;
    if (!GetPlayerViewPoint(ViewLocation, ViewRotation))
        return false;

    TraceStart = ViewLocation;
    TraceEnd = TraceStart + ViewRotation.Vector() * 10000.0f;
    return true;
}

void ARFBaseWeapon::MakeDamage(FHitResult const& HitResult)
{
    if (!HitResult.GetActor())
        return;

    HitResult.GetActor()->TakeDamage(DamageAmount, FDamageEvent{}, GetPlayerController(), this);
}

void ARFBaseWeapon::MakeHit(FHitResult& HitResult, FVector const& TraceStart, FVector const& TraceEnd) const
{
    FCollisionQueryParams CollisionQueryParams;
    CollisionQueryParams.AddIgnoredActor(GetOwner());
    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionQueryParams);
}
