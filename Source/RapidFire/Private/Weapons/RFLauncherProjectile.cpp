// Rapid Fire Game. All Rights Reserved.

#include "Weapons/RFLauncherProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ARFLauncherProjectile::ARFLauncherProjectile()
    : SphereComponent(nullptr)
    , ProjectileMovementComponent(nullptr)
    , ShotDirection(FVector::ZeroVector)
{
    PrimaryActorTick.bCanEverTick = false;
    SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    SphereComponent->InitSphereRadius(5.f);
    SetRootComponent(SphereComponent);

    ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
}

void ARFLauncherProjectile::BeginPlay()
{
    Super::BeginPlay();

    check(ProjectileMovementComponent);
    ProjectileMovementComponent->Velocity = ShotDirection * ProjectileMovementComponent->InitialSpeed;
}
