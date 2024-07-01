// Rapid Fire Game. All Rights Reserved.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "RFWeaponComponent.generated.h"

class ARFBaseWeapon;
struct FWeaponAmmoData;
struct FWeaponUIData;

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
    bool GetAmmoData(FWeaponAmmoData& Data) const;
    bool GetUIData(FWeaponUIData& Data) const;
    bool IsFiring() const;

protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(EEndPlayReason::Type const EndPlayReason) override;

private:
    void SpawnWeapons();
    void AttachWeaponToSocket(ARFBaseWeapon* Weapon, FName const& WeaponSocketName);
    void EquipWeapon(int32 Index);
    bool PlayAnimMontage(UAnimMontage* AnimMontage) const;
    void InitAnimations();
    void OnEquipFinished(USkeletalMeshComponent* MeshComp);
    void OnReloadFinished(USkeletalMeshComponent* MeshComp);
    bool CanFire() const;
    bool CanEquip() const;

    template <typename T>
    T* FindNotifyByClass(UAnimSequenceBase* AnimationBase) const
    {
        if (!AnimationBase)
            return nullptr;
        for (auto const NotifyEvent : AnimationBase->Notifies)
        {
            if (auto EquipFinishNotify = Cast<T>(NotifyEvent.Notify))
            {
                return EquipFinishNotify;
            }
        }
        return nullptr;
    }

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

    bool bIsWeaponAnimPlaying{ false };
};
