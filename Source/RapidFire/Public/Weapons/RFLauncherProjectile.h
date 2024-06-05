// Rapid Fire Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RFLauncherProjectile.generated.h"

class USphereComponent;

UCLASS()
class RAPIDFIRE_API ARFLauncherProjectile : public AActor
{
    GENERATED_BODY()

public:
    ARFLauncherProjectile();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
    USphereComponent* SphereComponent;
};
