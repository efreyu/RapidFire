// Rapid Fire Game. All Rights Reserved.

#include "Weapons/RFLauncherWeapon.h"
#include "Weapons/RFLauncherProjectile.h"

ARFLauncherWeapon::ARFLauncherWeapon()
{
    ProjectileClass = ARFLauncherProjectile::StaticClass();
}

void ARFLauncherWeapon::StartFire()
{
    if (CurrentAmmo.CanShot())
        MakeShot();
}

void ARFLauncherWeapon::StopFire()
{
    //
}

void ARFLauncherWeapon::MakeShot()
{
    if (!GetWorld() || !CurrentAmmo.MakeShot())
        return;

    FVector TraceStart, TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd))
        return;

    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);

    FVector const EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
    FVector const Direction = (EndPoint - GetMuzzleLocation()).GetSafeNormal();

    FTransform const SpawnTransform(FRotator::ZeroRotator, GetMuzzleLocation());
    if (auto const Projectile = GetWorld()->SpawnActorDeferred<ARFLauncherProjectile>(ProjectileClass, SpawnTransform))
    {
        Projectile->SetShotDirection(Direction);
        Projectile->SetOwner(GetOwner());
        Projectile->FinishSpawning(SpawnTransform);
    }
}
