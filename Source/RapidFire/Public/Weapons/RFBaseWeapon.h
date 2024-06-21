// Rapid Fire Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapons/RFBaseWeapon.h"
#include "RFBaseWeapon.generated.h"

class USkeletalMeshComponent;
class APlayerController;
struct FHitResult;

DECLARE_MULTICAST_DELEGATE(FOnClipEmptySignature);

namespace RapidFire::inline Constants::Socket
{
    constexpr inline auto MuzzleSocket{ TEXT("MuzzleSocket") };
} // namespace RapidFire::inline Constants::Socket

USTRUCT(BlueprintType)
struct FWeaponAmmoData
{
    GENERATED_BODY()

    bool IsEmpty() const;
    bool IsClipEmpty() const;
    bool Reload();
    bool CanShot() const;
    bool MakeShot();
    bool CanReload() const;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo", Meta = (EditCondition = "!bIsInfinity"))
    int32 TotalAmmo{ 55 };

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo", Meta = (EditCondition = "!bIsInfinity"))
    int32 ShotCost{ 1 };

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo", Meta = (EditCondition = "!bIsInfinity"))
    int32 ReloadClipMax{ 15 };

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo")
    bool bIsInfinity{ false };

    UPROPERTY(EditDefaultsOnly, Category = "Ammo|Animation")
    UAnimMontage* ReloadAnimMontage{ nullptr };

private:
    void LogAmmo();

    int32 ClipAmmo{ 0 };
};

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
