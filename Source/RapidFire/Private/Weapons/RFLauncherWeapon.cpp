// Rapid Fire Game. All Rights Reserved.

#include "Weapons/RFLauncherWeapon.h"
#include "Weapons/RFLauncherProjectile.h"

ARFLauncherWeapon::ARFLauncherWeapon()
    : ProjectileClass(ARFLauncherProjectile::StaticClass()) {}

void ARFLauncherWeapon::StartFire()
{
    MakeShot();
}

void ARFLauncherWeapon::StopFire()
{
    //
}

void ARFLauncherWeapon::MakeShot()
{
    if (!GetWorld())
        return;

    FVector TraceStart, TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd))
        return;

    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);

    FVector const EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
    FVector const Direction = (EndPoint - GetMuzzleLocation()).GetSafeNormal();

    FTransform const SpawnTransform(FRotator::ZeroRotator, GetMuzzleLocation());
    auto const Projectile = GetWorld()->SpawnActorDeferred<ARFLauncherProjectile>(ProjectileClass, SpawnTransform);
    if (Projectile)
    {
        Projectile->SetShotDirection(Direction);
        Projectile->FinishSpawning(SpawnTransform);
    }
}
