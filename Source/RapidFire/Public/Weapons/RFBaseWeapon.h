// Rapid Fire Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RFBaseWeapon.generated.h"

class USkeletalMeshComponent;

UCLASS()
class RAPIDFIRE_API ARFBaseWeapon : public AActor
{
    GENERATED_BODY()

public:
    ARFBaseWeapon();

protected:
    virtual void BeginPlay() override;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent* SkeletalMeshComponent;
};
