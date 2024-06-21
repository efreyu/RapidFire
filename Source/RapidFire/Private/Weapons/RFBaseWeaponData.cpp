// Rapid Fire Game. All Rights Reserved.

#include "RFBaseWeaponData.h"

bool FWeaponAmmoData::IsEmpty() const
{
    if (bIsInfinity)
        return false;
    return TotalAmmo == 0 && IsClipEmpty();
}

bool FWeaponAmmoData::IsClipEmpty() const
{
    if (bIsInfinity)
        return false;
    return ClipAmmo - ShotCost < 0;
}

bool FWeaponAmmoData::Reload()
{
    UE_LOG(LogTemp, Warning, TEXT("Reload"));
    if (IsEmpty())
        return false;
    TotalAmmo += ClipAmmo;
    ClipAmmo = 0;
    auto const Amount = FMath::Min(TotalAmmo, ReloadClipMax);
    ClipAmmo = Amount;
    TotalAmmo -= Amount;
    LogAmmo();
    return true;
}

bool FWeaponAmmoData::CanShot() const
{
    return bIsInfinity || ClipAmmo - ShotCost >= 0;
}

bool FWeaponAmmoData::MakeShot()
{
    LogAmmo();
    if (CanShot())
    {
        ClipAmmo -= ShotCost;
        return true;
    }
    return false;
}

bool FWeaponAmmoData::CanReload() const
{
    return ClipAmmo < ReloadClipMax && TotalAmmo > 0;
}

void FWeaponAmmoData::LogAmmo()
{
    UE_LOG(LogTemp, Warning, TEXT("TotalAmmo: '%d', ClipAmmo: '%d'"), TotalAmmo, ClipAmmo);
}

UTexture2D* FWeaponUIData::GetIconTex() const
{
    return IconTex;
}

UTexture2D* FWeaponUIData::GetCrosshairTex() const
{
    return CrosshairTex;
}
