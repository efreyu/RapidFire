// Rapid Fire Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RFBaseWeapon.generated.h"

class USkeletalMeshComponent;
class APlayerController;
struct FHitResult;

namespace RapidFire::inline Constants::Socket
{
    constexpr inline auto MuzzleSocket{ TEXT("MuzzleSocket") };
} // namespace RapidFire::inline Constants::Socket

UCLASS()
class RAPIDFIRE_API ARFBaseWeapon : public AActor
{
    GENERATED_BODY()

public:
    ARFBaseWeapon();
    virtual void StartFire();
    virtual void StopFire();

protected:
    virtual void BeginPlay() override;
    virtual void MakeShot();
    virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;
    APlayerController* GetPlayerController() const;
    bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
    void MakeDamage(FHitResult const& HitResult);
    void MakeHit(FHitResult& HitResult, FVector const& TraceStart, FVector const& TraceEnd) const;
    FVector GetMuzzleLocation() const;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent* SkeletalMeshComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
    FName MuzzleSocketName;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float DamageAmount;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float ShootDirectionRange;
};
