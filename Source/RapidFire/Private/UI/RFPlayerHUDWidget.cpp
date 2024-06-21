// Rapid Fire Game. All Rights Reserved.

#include "UI/RFPlayerHUDWidget.h"
#include "Components/RFHealthComponent.h"
#include "Components/RFWeaponComponent.h"
#include "Weapons/RFBaseWeaponData.h"

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

bool URFPlayerHUDWidget::GetAmmoData(FWeaponAmmoData& Data) const
{
    if (auto WeaponComponent = GetWeaponComponent())
    {
        return WeaponComponent->GetAmmoData(Data);
    }
    return false;
}

bool URFPlayerHUDWidget::GetUIData(FWeaponUIData& Data) const
{
    if (auto WeaponComponent = GetWeaponComponent())
    {
        return WeaponComponent->GetUIData(Data);
    }
    return false;
}

URFWeaponComponent* URFPlayerHUDWidget::GetWeaponComponent() const
{
    auto const Player = GetOwningPlayerPawn();
    if (!Player)
        return nullptr;
    if (auto const WeaponComponent = Player->GetComponentByClass<URFWeaponComponent>())
    {
        return WeaponComponent;
    }

    return nullptr;
}
