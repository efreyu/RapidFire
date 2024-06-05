// Rapid Fire Game. All Rights Reserved.

#include "Weapons/RFLauncherWeapon.h"
#include "Kismet/GameplayStatics.h"
#include "Weapons/RFLauncherProjectile.h"

ARFLauncherWeapon::ARFLauncherWeapon()
    : ProjectileClass(ARFLauncherProjectile::StaticClass()) {}

void ARFLauncherWeapon::StartFire()
{
    //
}

void ARFLauncherWeapon::StopFire()
{
    MakeShot();
}

void ARFLauncherWeapon::MakeShot()
{
    FTransform const SpawnTransform(FRotator::ZeroRotator, GetMuzzleLocation());
    auto const Projectile = Cast<ARFLauncherProjectile>(UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), ProjectileClass, SpawnTransform));

    UGameplayStatics::FinishSpawningActor(Projectile, SpawnTransform);
}
