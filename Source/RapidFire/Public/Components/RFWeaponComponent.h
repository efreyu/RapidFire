// Rapid Fire Game. All Rights Reserved.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "RFWeaponComponent.generated.h"

class ARFBaseWeapon;

namespace RapidFire::inline Constants
{
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

protected:
    virtual void BeginPlay() override;

private:
    void SpawnWeapon() const;

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TSubclassOf<ARFBaseWeapon> WeaponClass;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponAttachSocketName;
};
