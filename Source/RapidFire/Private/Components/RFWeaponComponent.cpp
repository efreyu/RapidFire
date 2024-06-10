// Rapid Fire Game. All Rights Reserved.

#include "Components/RFWeaponComponent.h"

#include "GameFramework/Character.h"
#include "RFBaseCharacter.h"
#include "Weapons/RFBaseWeapon.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All);

URFWeaponComponent::URFWeaponComponent()
    : WeaponClasses({})
    , WeaponHandSocketName(RapidFire::Socket::WeaponHandSocketName)
    , WeaponArmorySocketName(RapidFire::Socket::WeaponArmorySocketName)
    , CurrentWeapon(nullptr)
    , CurrentWeaponIndex(0)
    , Weapons({})
{
    PrimaryComponentTick.bCanEverTick = false;
}

void URFWeaponComponent::BeginPlay()
{
    Super::BeginPlay();
    check(WeaponClasses.Num() > 0);
    check(Weapons.Num() == 0);
    SpawnWeapons();
    EquipWeapon(CurrentWeaponIndex);
}

void URFWeaponComponent::EndPlay(EEndPlayReason::Type const EndPlayReason)
{
    CurrentWeapon = nullptr;
    for (auto const Weapon : Weapons)
    {
        if (Weapon)
        {
            Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
            Weapon->Destroy();
        }
    }
    Weapons.Empty();
    Super::EndPlay(EndPlayReason);
}

void URFWeaponComponent::SpawnWeapons()
{
    auto const Character = Cast<ACharacter>(GetOwner());
    if (!Character || !GetWorld() || WeaponClasses.IsEmpty())
        return;

    for (auto const& WeaponClass : WeaponClasses)
    {
        auto const Weapon = GetWorld()->SpawnActor<ARFBaseWeapon>(WeaponClass);
        if (!Weapon)
        {
            UE_LOG(LogWeaponComponent, Error, TEXT("Actor: '%s', Can't initialize weapon actor"), *GetName());
            return;
        }
        Weapon->SetOwner(GetOwner());
        Weapons.Add(Weapon);
        AttachWeaponToSocket(Weapon, WeaponArmorySocketName);
    }
}

void URFWeaponComponent::AttachWeaponToSocket(ARFBaseWeapon* Weapon, FName const& WeaponSocketName)
{
    auto const Character = Cast<ACharacter>(GetOwner());
    if (!Character || !Weapon)
    {
        UE_LOG(LogWeaponComponent, Error, TEXT("Can't attach weapon to socket"));
        return;
    }
    auto const AttachmentRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
    Weapon->AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponSocketName);
}

void URFWeaponComponent::EquipWeapon(int32 Index)
{
    auto const Character = Cast<ACharacter>(GetOwner());
    if (!Character)
    {
        UE_LOG(LogWeaponComponent, Error, TEXT("Can't attach weapon to socket"));
        return;
    }
    if (CurrentWeapon)
    {
        CurrentWeapon->StopFire();
        AttachWeaponToSocket(CurrentWeapon, WeaponArmorySocketName);
    }
    CurrentWeaponIndex = Index;
    CurrentWeapon = Weapons.IsValidIndex(CurrentWeaponIndex) ? Weapons[CurrentWeaponIndex] : nullptr;
    if (CurrentWeapon)
    {
        AttachWeaponToSocket(CurrentWeapon, WeaponHandSocketName);
    }
}

void URFWeaponComponent::StartFire()
{
    if (!CurrentWeapon)
        return;
    CurrentWeapon->StartFire();
}

void URFWeaponComponent::StopFire()
{
    if (!CurrentWeapon)
        return;
    CurrentWeapon->StopFire();
}

void URFWeaponComponent::SetNextWeapon()
{
    CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
    EquipWeapon(CurrentWeaponIndex);
}
