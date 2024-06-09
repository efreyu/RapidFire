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

    UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
    USphereComponent* SphereComponent;

    UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
    UProjectileMovementComponent* ProjectileMovementComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float DamageRadius;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float MaxDamageAmount;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    bool DoFullDamage;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float TimeBeforeDestroy;

private:
    FVector ShotDirection;
    bool IsDestroyed;
};
