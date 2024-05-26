// Rapid Fire Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "RFCharacterMovementComponent.generated.h"

/**
 *
 */
UCLASS()
class RAPIDFIRE_API URFCharacterMovementComponent : public UCharacterMovementComponent
{
    GENERATED_BODY()

public:
    virtual float GetMaxSpeed() const override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement", Meta = (ClampMin = 1.5f, ClampMax = 3.0f))
    float RunSpeedModifier = 1.5f;
};
