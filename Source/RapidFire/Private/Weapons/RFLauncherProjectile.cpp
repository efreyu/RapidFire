// Rapid Fire Game. All Rights Reserved.

#include "Weapons/RFLauncherProjectile.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ARFLauncherProjectile::ARFLauncherProjectile()
    : SphereComponent(nullptr)
    , ProjectileMovementComponent(nullptr)
    , DamageRadius(300.f)
    , MaxDamageAmount(100.f)
    , DoFullDamage(false)
    , TimeBeforeDestroy(5.f)
    , ShotDirection(FVector::ZeroVector)
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
    SphereComponent->OnComponentHit.AddDynamic(this, &ARFLauncherProjectile::OnHit);
    SphereComponent->IgnoreActorWhenMoving(GetOwner(), true);
    SetLifeSpan(TimeBeforeDestroy);
}

void ARFLauncherProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, FHitResult const& Hit)
{
    if (!GetWorld())
        return;
    ProjectileMovementComponent->StopMovementImmediately();

    DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadius, 24, FColor::Red, false, -1.0f, 0, 1.0f);
    UGameplayStatics::ApplyRadialDamage(GetWorld(), //
        MaxDamageAmount,                            //
        GetActorLocation(),                         //
        DamageRadius,                               //
        UDamageType::StaticClass(),                 //
        TArray<AActor*>({ GetOwner() }),            //
        this,                                       //
        GetController(),                            //
        DoFullDamage,                               //
        ECollisionChannel::ECC_Visibility);

    Destroy();
}

AController* ARFLauncherProjectile::GetController() const
{
    auto const Pawn = Cast<Pawn>(GetOwner());
    return Pawn ? Pawn->GetController() : nullptr;
}
