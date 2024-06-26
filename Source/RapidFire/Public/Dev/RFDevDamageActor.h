// Rapid Fire Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RFDevDamageActor.generated.h"

UCLASS()
class RAPIDFIRE_API ARFDevDamageActor : public AActor
{
    GENERATED_BODY()

public:
    ARFDevDamageActor();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "DevDamageActor")
    USceneComponent* SceneComponent{ nullptr };

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DevDamageActor", Meta = (ClampMin = 0.0f, ClampMax = 1000.0f))
    float Radius{ 300.0f };

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DevDamageActor")
    FColor Color{ FColor::Red };

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DevDamageActor")
    float Damage{ 10.f };

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DevDamageActor")
    bool DoFullDamage{ false };

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DevDamageActor")
    TSubclassOf<UDamageType> DamageType{};
};
