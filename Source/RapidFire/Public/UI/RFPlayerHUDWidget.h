// Rapid Fire Game. All Rights Reserved.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "RFPlayerHUDWidget.generated.h"

/**
 *
 */
UCLASS()
class RAPIDFIRE_API URFPlayerHUDWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    float GetHealthPercent() const;

};
