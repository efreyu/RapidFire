// Rapid Fire Game. All Rights Reserved.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "RFPlayerHUDWidget.generated.h"

struct FWeaponAmmoData;
struct FWeaponUIData;
class URFWeaponComponent;

UCLASS()
class RAPIDFIRE_API URFPlayerHUDWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    float GetHealthPercent() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetCurrentClipAmmo(int32& Ammo) const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetTotalAmmo(int32& Ammo) const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetUIData(FWeaponUIData& Data) const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetAmmoData(FWeaponAmmoData& Data) const;

private:
    URFWeaponComponent* GetWeaponComponent() const;
};
