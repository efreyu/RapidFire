// Rapid Fire Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "RFBaseWeaponData.generated.h"

USTRUCT(BlueprintType)
struct FWeaponAmmoData
{
    GENERATED_BODY()

    bool IsEmpty() const;
    bool IsClipEmpty() const;
    bool Reload();
    bool CanShot() const;
    bool MakeShot();
    bool CanReload() const;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo", Meta = (EditCondition = "!bIsInfinity"))
    int32 TotalAmmo{ 55 };

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo", Meta = (EditCondition = "!bIsInfinity"))
    int32 ShotCost{ 1 };

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo", Meta = (EditCondition = "!bIsInfinity"))
    int32 ReloadClipMax{ 15 };

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo")
    bool bIsInfinity{ false };

    UPROPERTY(EditDefaultsOnly, Category = "Ammo|Animation")
    UAnimMontage* ReloadAnimMontage{ nullptr };

private:
    void LogAmmo();

    int32 ClipAmmo{ 0 };
};

USTRUCT(BlueprintType)
struct FWeaponUIData
{
    GENERATED_BODY()

    UTexture2D* GetIconTex() const;
    UTexture2D* GetCrosshairTex() const;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
    UTexture2D* IconTex{ nullptr };

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
    UTexture2D* CrosshairTex{ nullptr };
};
