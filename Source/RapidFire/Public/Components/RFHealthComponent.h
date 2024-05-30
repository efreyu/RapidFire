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

DECLARE_MULTICAST_DELEGATE(FOnDeathSignature);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class RAPIDFIRE_API URFHealthComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    URFHealthComponent();

    UFUNCTION(BlueprintCallable, Category = "Health")
    float GetHealth() const { return Health; }

    UFUNCTION(BlueprintCallable, Category = "Health")
    bool IsDead() const { return FMath::IsNearlyZero(Health); }

    FOnDeathSignature         OnDeath;
    FOnHealthChangedSignature OnHealthChanged;

protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(EEndPlayReason::Type const EndPlayReason) override;

private:
    UFUNCTION(BlueprintCallable, Category = "Damage")
    void OnTakeAnyDamage(AActor* DamagedActor, float Damage, UDamageType const* DamageType, AController* InstigatedBy, AActor* DamageCauser);

    UFUNCTION(BlueprintCallable, Category = "Damage")
    void OnGroundLanded(FHitResult const& Hit);

    void SetHealth(float const NewHealth);

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", Meta = (ClampMin = 1.0f, ClampMax = 100.0f))
    float MaxHealth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health|Auto Heal")
    bool IsAutoHeal;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health|Auto Heal", Meta = (EditCondition = "IsAutoHeal", ClampMin = 0.0f, ClampMax = 120.0f))
    float AutoHealDelay;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health|Auto Heal", Meta = (EditCondition = "IsAutoHeal", ClampMin = 0.0f, ClampMax = 100.0f))
    float AutoHealTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health|Auto Heal", Meta = (EditCondition = "IsAutoHeal", ClampMin = 0.0f, ClampMax = 100.0f))
    float AutoHealHealth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fall Damage")
    FVector2D LandedDamageVelocity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fall Damage")
    FVector2D LandedDamage;

    FTimerHandle AutoHealTimerHandle;

private:
    float Health;
};
