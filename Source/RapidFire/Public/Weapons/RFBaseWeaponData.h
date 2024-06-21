// Rapid Fire Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

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
