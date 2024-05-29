// Rapid Fire Game. All Rights Reserved.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "RFHealthComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class RAPIDFIRE_API URFHealthComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    URFHealthComponent();

protected:
    virtual void BeginPlay() override;

public:
    UFUNCTION(BlueprintCallable, Category = "Health")
    float GetHealth() const { return Health; }

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", Meta = (ClampMin = 1.0f, ClampMax = 100.0f))
    float MaxHealth = 100.0f;

private:
    float Health = 0.0f;

public:
    static FName HealthComponentName;
};
