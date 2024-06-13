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
    CurrentAmmo = BaseWeaponAmmoData;
}

void ARFBaseWeapon::BeginPlay()
{
    Super::BeginPlay();
    check(SkeletalMeshComponent)
    CurrentAmmo.Reload(true);
}

void ARFBaseWeapon::StartFire()
{
    checkNoEntry()
}

void ARFBaseWeapon::StopFire()
{
    checkNoEntry()
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

void ARFBaseWeapon::ReloadClip()
{
    CurrentAmmo.Reload();
}

bool FWeaponAmmoData::IsEmpty() const
{
    if (bIsInfinity)
        return false;
    return TotalAmmo == 0 && IsClipEmpty();
}

bool FWeaponAmmoData::IsClipEmpty() const
{
    if (bIsInfinity)
        return false;
    return ClipAmmo - ShotCost < 0;
}

bool FWeaponAmmoData::Reload(bool bSkipAnim)
{
    // todo add reload time and animation event
    LogAmmo();
    if (IsEmpty())
        return false;
    TotalAmmo += ClipAmmo;
    ClipAmmo = 0;
    auto const Amount = FMath::Min(TotalAmmo, ReloadClipMax);
    ClipAmmo = Amount;
    TotalAmmo -= Amount;
    return true;
}

bool FWeaponAmmoData::CanShot() const
{
    return bIsInfinity || ClipAmmo - ShotCost >= 0;
}

bool FWeaponAmmoData::MakeShot()
{
    LogAmmo();
    if (CanShot())
    {
        ClipAmmo -= ShotCost;
        return true;
    }
    return false;
}

void FWeaponAmmoData::LogAmmo()
{
    UE_LOG(LogTemp, Warning, TEXT("TotalAmmo: '%d', ClipAmmo: '%d'"), TotalAmmo, ClipAmmo);
}
