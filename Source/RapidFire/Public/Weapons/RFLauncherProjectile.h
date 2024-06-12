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

    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, FHitResult const& Hit);

    UFUNCTION()
    void OnDestroy(AActor* DestroyedActor);

    void ApplyDamage();

    AController* GetController() const;

    UPROPERTY(VisibleAnywhere, Category = "Weapon")
    USphereComponent* SphereComponent{ nullptr };

    UPROPERTY(VisibleAnywhere, Category = "Weapon")
    UProjectileMovementComponent* ProjectileMovementComponent{ nullptr };

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float DamageRadius{ 300.f };

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float MaxDamageAmount{ 100.f };

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    bool DoFullDamage{ false };

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float TimeBeforeDestroy{ 5.f };

private:
    FVector ShotDirection{ FVector::ZeroVector };
    bool IsDestroyed{ false };
};
