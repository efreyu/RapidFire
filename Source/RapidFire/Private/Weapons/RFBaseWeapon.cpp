// Rapid Fire Game. All Rights Reserved.

#include "Weapons/RFBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"

ARFBaseWeapon::ARFBaseWeapon()
    : SkeletalMeshComponent(CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComponent"))
    , MuzzleSocketName(RapidFire::Constants::Socket::MuzzleSocket)
{
    PrimaryActorTick.bCanEverTick = false;
    SetRootComponent(SkeletalMeshComponent);
}

void ARFBaseWeapon::BeginPlay()
{
    Super::BeginPlay();
    check(SkeletalMeshComponent);
}

void ARFBaseWeapon::Fire()
{
    UE_LOG(LogTemp, Warning, TEXT("Actor: '%s', Debug info FIRE"), *GetName());
    MakeShot();
}

void ARFBaseWeapon::MakeShot()
{
    if (!GetWorld())
        return;
    FTransform const SocketTransform = SkeletalMeshComponent->GetSocketTransform(MuzzleSocketName);
    FVector const TraceStart = SocketTransform.GetLocation();
    FVector TraceEnd = TraceStart + SocketTransform.GetRotation().GetForwardVector() * 10000.0f;
    FHitResult HitResult;
    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility);
    if (HitResult.bBlockingHit)
    {
        DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 12, FColor::Red, false, 1.0f, 0, 1.0f);
        TraceEnd = HitResult.ImpactPoint;
        UE_LOG(LogTemp, Warning, TEXT("Hit: '%s'"), *HitResult.GetActor()->GetName());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Hit: None"));
    }
    DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 1.0f, 0, 1.0f);
}
