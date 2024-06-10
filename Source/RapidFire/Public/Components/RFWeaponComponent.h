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
        constexpr inline auto WeaponSocket{ TEXT("WeaponSocket") };
        constexpr inline auto WeaponBackSlot{ TEXT("WeaponBackSlot") };
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

protected:
    virtual void BeginPlay() override;

private:
    void SpawnWeapons();
    void AttachWeaponToSocket(ARFBaseWeapon* Weapon, FName const& WeaponSocketName);
    void EquipWeapon(int32 Index);

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    TArray<TSubclassOf<ARFBaseWeapon>> WeaponClasses;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    FName WeaponHandSocketName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    FName WeaponArmorySocketName;

private:
    UPROPERTY()
    ARFBaseWeapon* CurrentWeapon;

    int32 CurrentWeaponIndex;

    UPROPERTY()
    TArray<ARFBaseWeapon*> Weapons;
};
