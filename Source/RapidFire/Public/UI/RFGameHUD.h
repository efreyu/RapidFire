// Rapid Fire Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RFGameHUD.generated.h"

class UUserWidget;

UCLASS()
class RAPIDFIRE_API ARFGameHUD : public AHUD
{
    GENERATED_BODY()

public:
    virtual void DrawHUD() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
    TSubclassOf<UUserWidget> PlayerHudWidgetClass;

    virtual void BeginPlay() override;

private:
    void DrawCrosshair();
};
