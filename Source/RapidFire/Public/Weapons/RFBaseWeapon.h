// Rapid Fire Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RFBaseWeaponData.h"
#include "RFBaseWeapon.generated.h"

class USkeletalMeshComponent;
class APlayerController;
struct FHitResult;

DECLARE_MULTICAST_DELEGATE(FOnClipEmptySignature);

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
    virtual bool CanFire() const;
    virtual bool CanReload() const;
    virtual void ReloadClip();
    virtual UAnimMontage* GetCurrentReloadAnimMontage() const;
    virtual FWeaponAmmoData const& GetAmmoData() const;
    virtual FWeaponUIData const& GetUIData() const;

    FOnClipEmptySignature OnClipEmpty;

protected:
    virtual void BeginPlay() override;
    virtual void MakeShot();
    virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;
    APlayerController* GetPlayerController() const;
    bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
    void MakeHit(FHitResult& HitResult, FVector const& TraceStart, FVector const& TraceEnd) const;
    FVector GetMuzzleLocation() const;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent* SkeletalMeshComponent{ nullptr };

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
    FName MuzzleSocketName{ RapidFire::Constants::Socket::MuzzleSocket };

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float ShootDirectionRange{ 10000.f };

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FWeaponAmmoData BaseWeaponAmmoData;

    FWeaponAmmoData CurrentAmmo;

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    FWeaponUIData UIData;
};
