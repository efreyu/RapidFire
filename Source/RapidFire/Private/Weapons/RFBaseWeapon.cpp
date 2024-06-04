// Rapid Fire Game. All Rights Reserved.

#include "Weapons/RFBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

ARFBaseWeapon::ARFBaseWeapon()
    : SkeletalMeshComponent(CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComponent"))
    , MuzzleSocketName(RapidFire::Constants::Socket::MuzzleSocket)
    , DamageAmount(10.f)
    , ShotRate(0.1f)
    , BulletSpread(2.0f)
{
    PrimaryActorTick.bCanEverTick = false;
    SetRootComponent(SkeletalMeshComponent);
}

void ARFBaseWeapon::BeginPlay()
{
    Super::BeginPlay();
    check(SkeletalMeshComponent);
}

void ARFBaseWeapon::StartFire()
{
    GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ARFBaseWeapon::MakeShot, ShotRate, true);
}

void ARFBaseWeapon::StopFire()
{
    if (ShotTimerHandle.IsValid())
    {
        GetWorldTimerManager().ClearTimer(ShotTimerHandle);
    }
}

void ARFBaseWeapon::MakeShot()
{
    if (!GetWorld())
        return;

    FVector TraceStart;
    FVector TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd))
        return;
    FTransform const SocketTransform = SkeletalMeshComponent->GetSocketTransform(MuzzleSocketName);

    FHitResult HitResult;
    FCollisionQueryParams CollisionQueryParams;
    CollisionQueryParams.AddIgnoredActor(GetOwner());
    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionQueryParams);
    if (HitResult.bBlockingHit)
    {
        DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 12, FColor::Red, false, 1.0f, 0, 1.0f);
        TraceEnd = HitResult.ImpactPoint;
        MakeDamage(HitResult);
    }
    DrawDebugLine(GetWorld(), SocketTransform.GetLocation(), TraceEnd, FColor::Red, false, 1.0f, 0, 1.0f);
}

APlayerController* ARFBaseWeapon::GetPlayerController() const
{
    auto const Player = Cast<ACharacter>(GetOwner());
    if (!Player)
        return nullptr;
    return Player->GetController<APlayerController>();
}

bool ARFBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
    auto const PlayerController = GetPlayerController();
    if (!PlayerController)
        return false;
    PlayerController->GetPlayerViewPoint(ViewLocation, ViewRotation);
    return true;
}

bool ARFBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
    FVector ViewLocation;
    FRotator ViewRotation;
    if (!GetPlayerViewPoint(ViewLocation, ViewRotation))
        return false;

    TraceStart = ViewLocation;
    auto const HalfRad = FMath::DegreesToRadians(BulletSpread);
    TraceEnd = TraceStart + FMath::VRandCone(ViewRotation.Vector(), HalfRad) * 10000.0f;
    return true;
}

void ARFBaseWeapon::MakeDamage(FHitResult const& HitResult)
{
    if (!HitResult.GetActor())
        return;

    HitResult.GetActor()->TakeDamage(DamageAmount, FDamageEvent{}, GetPlayerController(), this);
}
