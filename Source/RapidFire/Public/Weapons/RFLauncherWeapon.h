// Rapid Fire Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/RFBaseWeapon.h"
#include "RFLauncherWeapon.generated.h"

class ARFLauncherProjectile;

UCLASS()
class RAPIDFIRE_API ARFLauncherWeapon : public ARFBaseWeapon
{
    GENERATED_BODY()

public:
    ARFLauncherWeapon();
    virtual void StartFire() override;
    virtual void StopFire() override;

protected:
    virtual void MakeShot() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<ARFLauncherProjectile> ProjectileClass;
};
