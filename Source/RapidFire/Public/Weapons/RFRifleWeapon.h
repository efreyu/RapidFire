// Rapid Fire Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/RFBaseWeapon.h"
#include "RFRifleWeapon.generated.h"

UCLASS()
class RAPIDFIRE_API ARFRifleWeapon : public ARFBaseWeapon
{
    GENERATED_BODY()

public:
    ARFRifleWeapon();
    virtual void StartFire() override;
    virtual void StopFire() override;

protected:
    virtual void MakeShot() override;
    virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;
    void MakeDamage(FHitResult const& HitResult);

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float ShotRate{ 0.1f };

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "RifleWeapon")
    float BulletSpread{ 1.5f };

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float DamageAmount{ 10.f };

private:
    FTimerHandle ShotTimerHandle;
};
