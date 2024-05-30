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
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float);

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

    FOnDeath         OnDeath;
    FOnHealthChanged OnHealthChanged;

protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(EEndPlayReason::Type const EndPlayReason) override;

private:
    UFUNCTION(BlueprintCallable, Category = "Damage")
    void OnTakeAnyDamage(AActor* DamagedActor, float Damage, UDamageType const* DamageType, AController* InstigatedBy, AActor* DamageCauser);

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", Meta = (ClampMin = 1.0f, ClampMax = 100.0f))
    float MaxHealth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health|Auto Heal")
    bool IsAutoHeal;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health|Auto Heal", Meta = (ClampMin = 0.0f, ClampMax = 120.0f))
    float AutoHealDelay;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health|Auto Heal", Meta = (ClampMin = 0.0f, ClampMax = 100.0f))
    float AutoHealTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health|Auto Heal", Meta = (ClampMin = 0.0f, ClampMax = 100.0f))
    float AutoHealHealth;

    FTimerHandle AutoHealTimerHandle;

private:
    float  Health;
    double LastHitTime;
};
