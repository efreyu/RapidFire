// Rapid Fire Game. All Rights Reserved.

#include "Weapons/RFLauncherProjectile.h"
#include "Components/SphereComponent.h"

ARFLauncherProjectile::ARFLauncherProjectile()
{
    PrimaryActorTick.bCanEverTick = false;
    SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    SphereComponent->InitSphereRadius(5.f);
    SetRootComponent(SphereComponent);
}

void ARFLauncherProjectile::BeginPlay()
{
    Super::BeginPlay();
}
