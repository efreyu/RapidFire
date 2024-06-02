// Rapid Fire Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RFBaseWeapon.generated.h"

class USkeletalMeshComponent;

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

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent* SkeletalMeshComponent;
    // todo remove me, first argument:
    // - EditAnywhere Both the default value set in the Blueprint editor and per-instance values can be edited in the property windows.
    // - VisibleAnywhere The value can be seen, but not edited, both in the Blueprint editor and per-instance in the Level Editor.
    // - EditDefaultsOnly The default value can be edited in the Blueprint editor, but not on instances.
    // - VisibleDefaultOnly The default value is visible in the Blueprint editor, but not on instances.
    // - EditInstanceOnly The value can be edited on instances, but the default value is locked.
    // - VisibleInstanceOnly Instance values can be seen, but not edited.
    // second argument
    // - BlueprintReadOnly Blueprint Visual Scripts can read, but not write, the property.
    // - BlueprintReadWrite Blueprint Visual Scripts can both read and write the property.
    // - EditFixedSize Only for arrays. The elements can be edited, but the number of elements if fixed.
    // - EditInline Only for pointers. The properties of the pointed-to object is shown instead of the pointer. See more below.
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
    FName MuzzleSocketName;
};
