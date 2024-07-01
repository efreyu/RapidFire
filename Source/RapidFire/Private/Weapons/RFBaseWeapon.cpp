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
    check(SkeletalMeshComponent)
    CurrentAmmo = BaseWeaponAmmoData;
    CurrentAmmo.Reload();
}

void ARFBaseWeapon::StartFire()
{
    FireInProgress = true;
}

void ARFBaseWeapon::StopFire()
{
    FireInProgress = false;
}

void ARFBaseWeapon::MakeShot()
{
    checkNoEntry()
}

bool ARFBaseWeapon::CanFire() const
{
    return CurrentAmmo.CanShot();
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

bool ARFBaseWeapon::CanReload() const
{
    return CurrentAmmo.CanReload();
}

void ARFBaseWeapon::ReloadClip()
{
    CurrentAmmo.Reload();
}

UAnimMontage* ARFBaseWeapon::GetCurrentReloadAnimMontage() const
{
    return CurrentAmmo.ReloadAnimMontage;
}

FWeaponAmmoData const& ARFBaseWeapon::GetAmmoData() const
{
    return CurrentAmmo;
}

FWeaponUIData const& ARFBaseWeapon::GetUIData() const
{
    return UIData;
}

bool ARFBaseWeapon::IsFiring() const
{
    return FireInProgress;
}
