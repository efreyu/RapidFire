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
    static FName HealthComponentName;
    URFHealthComponent();

    UFUNCTION(BlueprintCallable, Category = "Health")
    float GetHealth() const { return Health; }

protected:
    virtual void BeginPlay() override;

private:
    UFUNCTION(BlueprintCallable, Category = "Damage")
    void OnTakeAnyDamage(AActor* DamagedActor, float Damage, UDamageType const* DamageType, AController* InstigatedBy, AActor* DamageCauser);

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", Meta = (ClampMin = 1.0f, ClampMax = 100.0f))
    float MaxHealth;

private:
    float Health;
};
