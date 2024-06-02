// Rapid Fire Game. All Rights Reserved.

#include "Weapons/RFBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

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
    auto const Player = Cast<ACharacter>(GetOwner());
    if (!Player)
        return;
    auto const PlayerController = Player->GetController<APlayerController>();
    if (!PlayerController)
        return;
    FVector ViewLocation;
    FRotator ViewRotation;
    PlayerController->GetPlayerViewPoint(ViewLocation, ViewRotation);

    FTransform const SocketTransform = SkeletalMeshComponent->GetSocketTransform(MuzzleSocketName);
    FVector const TraceStart = ViewLocation;                         // SocketTransform.GetLocation();
    FVector TraceEnd = TraceStart + ViewRotation.Vector() * 10000.f; // SocketTransform.GetRotation().GetForwardVector() * 10000.0f;

    FHitResult HitResult;
    FCollisionQueryParams CollisionQueryParams;
    CollisionQueryParams.AddIgnoredActor(Player);
    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionQueryParams);
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
    DrawDebugLine(GetWorld(), SocketTransform.GetLocation(), TraceEnd, FColor::Red, false, 1.0f, 0, 1.0f);
}
