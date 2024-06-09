// Rapid Fire Game. All Rights Reserved.

#include "Weapons/RFRifleWeapon.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"
#include "Engine/World.h"

ARFRifleWeapon::ARFRifleWeapon()
    : ARFBaseWeapon()
    , ShotRate(0.1f)
    , BulletSpread(1.5f)
    , DamageAmount(10.f)
{
    //
}

void ARFRifleWeapon::StartFire()
{
    GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ARFRifleWeapon::MakeShot, ShotRate, true);
}

void ARFRifleWeapon::StopFire()
{
    if (ShotTimerHandle.IsValid())
    {
        GetWorldTimerManager().ClearTimer(ShotTimerHandle);
    }
}

void ARFRifleWeapon::MakeShot()
{
    if (!GetWorld())
        return;

    FVector TraceStart, TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd))
        return;

    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);
    if (HitResult.bBlockingHit)
    {
        DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 12, FColor::Red, false, 1.0f, 0, 1.0f);
        TraceEnd = HitResult.ImpactPoint;
        MakeDamage(HitResult);
    }
    DrawDebugLine(GetWorld(), GetMuzzleLocation(), TraceEnd, FColor::Red, false, 1.0f, 0, 1.0f);
}

bool ARFRifleWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
    FVector ViewLocation;
    FRotator ViewRotation;
    if (!GetPlayerViewPoint(ViewLocation, ViewRotation))
        return false;

    TraceStart = ViewLocation;
    auto const HalfRad = FMath::DegreesToRadians(BulletSpread);
    TraceEnd = TraceStart + FMath::VRandCone(ViewRotation.Vector(), HalfRad) * ShootDirectionRange;
    return true;
}

void ARFRifleWeapon::MakeDamage(FHitResult const& HitResult)
{
    if (!HitResult.GetActor())
        return;

    HitResult.GetActor()->TakeDamage(DamageAmount, FDamageEvent{}, GetPlayerController(), this);
}
