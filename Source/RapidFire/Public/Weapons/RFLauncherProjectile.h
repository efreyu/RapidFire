// Rapid Fire Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RFLauncherProjectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class RAPIDFIRE_API ARFLauncherProjectile : public AActor
{
    GENERATED_BODY()

public:
    ARFLauncherProjectile();
    void SetShotDirection(FVector const& Direction) { ShotDirection = Direction; }

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
    USphereComponent* SphereComponent;

    UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
    UProjectileMovementComponent* ProjectileMovementComponent;

private:
    FVector ShotDirection;
};
