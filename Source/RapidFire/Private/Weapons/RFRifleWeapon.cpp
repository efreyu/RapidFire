// Rapid Fire Game. All Rights Reserved.

#include "Weapons/RFRifleWeapon.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"

ARFRifleWeapon::ARFRifleWeapon()
    : ShotRate(0.1f)
    , BulletSpread(1.5f)
{
    Super::ARFBaseWeapon();
}

void ARFRifleWeapon::StartFire()
{
    MakeShot();
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

    FVector TraceStart;
    FVector TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd))
        return;
    FTransform const SocketTransform = SkeletalMeshComponent->GetSocketTransform(MuzzleSocketName);

    FHitResult HitResult;
    MakeHit(HitResult, SocketTransform.GetLocation(), TraceEnd);
    if (HitResult.bBlockingHit)
    {
        DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 12, FColor::Red, false, 1.0f, 0, 1.0f);
        TraceEnd = HitResult.ImpactPoint;
        MakeDamage(HitResult);
    }
    DrawDebugLine(GetWorld(), SocketTransform.GetLocation(), TraceEnd, FColor::Red, false, 1.0f, 0, 1.0f);
}

bool ARFRifleWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
    FVector ViewLocation;
    FRotator ViewRotation;
    if (!GetPlayerViewPoint(ViewLocation, ViewRotation))
        return false;

    TraceStart = ViewLocation;
    auto const HalfRad = FMath::DegreesToRadians(BulletSpread);
    // TraceEnd = TraceStart + FMath::VRandCone(ViewRotation.Vector(), HalfRad);
    TraceEnd = TraceStart + ViewRotation.Vector();
    return true;
}
