// Rapid Fire Game. All Rights Reserved.

#include "UI/RFGameHUD.h"

#include "Blueprint/UserWidget.h"
#include "Engine/Canvas.h"
#include "UI/RFPlayerHUDWidget.h"

void ARFGameHUD::DrawHUD()
{
    Super::DrawHUD();
    // DrawCrosshair();
}

void ARFGameHUD::BeginPlay()
{
    Super::BeginPlay();
    check(PlayerHudWidgetClass);
    auto PlayerHUDWidget = CreateWidget<URFPlayerHUDWidget>(GetWorld(), PlayerHudWidgetClass);
    if (PlayerHUDWidget)
    {
        PlayerHUDWidget->AddToViewport();
    }
}

// void ARFGameHUD::DrawCrosshair()
// {
// TInterval<float> Center(Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f);
// auto const LineSize = 10.f;
// auto const LineThickness = 2.f;
// auto const Color = FLinearColor::White;
// DrawLine(Center.Min - LineSize, Center.Max, Center.Min + LineSize, Center.Max, Color, LineThickness);
// DrawLine(Center.Min, Center.Max - LineSize, Center.Min, Center.Max + LineSize, Color, LineThickness);
// }
