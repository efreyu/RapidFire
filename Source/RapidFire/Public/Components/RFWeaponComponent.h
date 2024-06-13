// Rapid Fire Game. All Rights Reserved.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "RFWeaponComponent.generated.h"

class ARFBaseWeapon;

namespace RapidFire::inline Constants
{
    namespace Components
    {
        constexpr inline auto WeaponComponentName{ TEXT("WeaponComponent") };
    } // namespace Components
    namespace Socket
    {
        constexpr inline auto WeaponHandSocketName{ TEXT("WeaponHandSocket") };
        constexpr inline auto WeaponArmorySocketName{ TEXT("WeaponArmorySocket") };
    } // namespace Socket
} // namespace RapidFire::inline Constants

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class RAPIDFIRE_API URFWeaponComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    URFWeaponComponent();

    void StartFire();
    void StopFire();
    void SetNextWeapon();
    void ReloadClip();

protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(EEndPlayReason::Type const EndPlayReason) override;

private:
    void SpawnWeapons();
    void AttachWeaponToSocket(ARFBaseWeapon* Weapon, FName const& WeaponSocketName);
    void EquipWeapon(int32 Index);
    void PlayAnimMontage(UAnimMontage* AnimMontage);
    void InitAnimations();
    void OnEquipFinished(USkeletalMeshComponent* MeshComp);
    bool CanFire() const;
    bool CanEquip() const;

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TArray<TSubclassOf<ARFBaseWeapon>> WeaponClasses{ {} };

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponHandSocketName{ RapidFire::Socket::WeaponHandSocketName };

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponArmorySocketName{ RapidFire::Socket::WeaponArmorySocketName };

    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    UAnimMontage* EquipAnimMontage{ nullptr };

private:
    UPROPERTY()
    ARFBaseWeapon* CurrentWeapon{ nullptr };

    int32 CurrentWeaponIndex{ 0 };

    UPROPERTY()
    TArray<ARFBaseWeapon*> Weapons;

    bool bIsEquipAnimPlaying{ false };
};
