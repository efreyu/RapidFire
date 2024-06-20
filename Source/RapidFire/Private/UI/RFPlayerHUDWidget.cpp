// Rapid Fire Game. All Rights Reserved.

#include "UI/RFPlayerHUDWidget.h"
#include "Components/RFHealthComponent.h"

float URFPlayerHUDWidget::GetHealthPercent() const
{
    auto const Player = GetOwningPlayerPawn();
    if (!Player)
        return 0.f;
    if (auto const HealthComponent = Player->GetComponentByClass<URFHealthComponent>())
    {
        if (HealthComponent)
        {
            return HealthComponent->GetHealthPercent();
        }
    }

    return 0.f;
}
