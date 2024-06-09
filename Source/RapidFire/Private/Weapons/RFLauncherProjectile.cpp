// Rapid Fire Game. All Rights Reserved.

#include "Weapons/RFLauncherProjectile.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ARFLauncherProjectile::ARFLauncherProjectile()
    : SphereComponent(nullptr)
    , ProjectileMovementComponent(nullptr)
    , ShotDirection(FVector::ZeroVector)
    , DamageRadius(300.f)
    , MaxDamageAmount(100.f)
{
    PrimaryActorTick.bCanEverTick = false;
    SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    SphereComponent->InitSphereRadius(5.f);
    SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    SphereComponent->SetCollisionResponseToAllChannels(ECR_Block);
    SetRootComponent(SphereComponent);

    ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
    ProjectileMovementComponent->InitialSpeed = 2000.f;
    ProjectileMovementComponent->ProjectileGravityScale = 0.f;
}

void ARFLauncherProjectile::BeginPlay()
{
    Super::BeginPlay();

    check(ProjectileMovementComponent);
    check(SphereComponent);
    ProjectileMovementComponent->Velocity = ShotDirection * ProjectileMovementComponent->InitialSpeed;
    SetLifeSpan(5.f);
    SphereComponent->OnComponentHit.AddDynamic(this, &ARFLauncherProjectile::OnHit);
}

void ARFLauncherProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, FHitResult const& Hit)
{
    if (!GetWorld())
        return;
    ProjectileMovementComponent->StopMovementImmediately();
    // todo make damage
    Destroy();
}
