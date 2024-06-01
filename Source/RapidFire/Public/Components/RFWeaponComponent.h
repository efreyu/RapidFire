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
    }
} // namespace RapidFire::inline Constants

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class RAPIDFIRE_API URFWeaponComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    URFWeaponComponent();

    void Fire();

protected:
    virtual void BeginPlay() override;

private:
    void SpawnWeapon();

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TSubclassOf<ARFBaseWeapon> WeaponClass;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponAttachSocketName;

private:
    UPROPERTY()
    ARFBaseWeapon* CurrentWeapon;
};
