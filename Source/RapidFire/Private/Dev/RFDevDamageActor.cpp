// Rapid Fire Game. All Rights Reserved.

#include "Dev/RFDevDamageActor.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

ARFDevDamageActor::ARFDevDamageActor()
    : SceneComponent(nullptr)
    , Radius(300.0f)
    , Color(FColor::Red)
    , Damage(10.f)
    , DoFullDamage(false)
{
    PrimaryActorTick.bCanEverTick = true;
    SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
    SetRootComponent(SceneComponent);
}

void ARFDevDamageActor::BeginPlay()
{
    Super::BeginPlay();
}

void ARFDevDamageActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 24, Color, false, -1.0f, 0, 1.0f);
    UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), Radius, DamageType, TArray<AActor*>(), this, nullptr, DoFullDamage, ECollisionChannel::ECC_Visibility);
}
