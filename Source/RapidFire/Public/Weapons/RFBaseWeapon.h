// Rapid Fire Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RFBaseWeapon.generated.h"

class USkeletalMeshComponent;
class APlayerController;

namespace RapidFire::inline Constants::Socket
{
    constexpr inline auto MuzzleSocket{ TEXT("MuzzleSocket") };
} // namespace RapidFire::inline Constants::Socket

UCLASS()
class RAPIDFIRE_API ARFBaseWeapon : public AActor
{
    GENERATED_BODY()

public:
    ARFBaseWeapon();
    virtual void Fire();

protected:
    virtual void BeginPlay() override;

private:
    void MakeShot();
    APlayerController* GetPlayerController() const;
    bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
    bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent* SkeletalMeshComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
    FName MuzzleSocketName;
};
