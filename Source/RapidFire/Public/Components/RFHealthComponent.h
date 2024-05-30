// Rapid Fire Game. All Rights Reserved.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "RFHealthComponent.generated.h"

namespace RapidFire::inline Constants
{
    namespace Components
    {
        constexpr inline auto HealthComponentName{ TEXT("HealthComponent") };
    } // namespace Components
} // namespace RapidFire::inline Constants

DECLARE_MULTICAST_DELEGATE(FOnDeath);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class RAPIDFIRE_API URFHealthComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    URFHealthComponent();

    UFUNCTION(BlueprintCallable, Category = "Health")
    float GetHealth() const { return Health; }

    UFUNCTION(BlueprintCallable, Category = "Health")
    bool IsDead() const { return Health <= 0.0f; }

    FOnDeath OnDeath;

protected:
    virtual void BeginPlay() override;

private:
    UFUNCTION(BlueprintCallable, Category = "Damage")
    void OnTakeAnyDamage(AActor* DamagedActor, float Damage, UDamageType const* DamageType, AController* InstigatedBy, AActor* DamageCauser);

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", Meta = (ClampMin = 1.0f, ClampMax = 100.0f))
    float MaxHealth;

private:
    float Health;
};
