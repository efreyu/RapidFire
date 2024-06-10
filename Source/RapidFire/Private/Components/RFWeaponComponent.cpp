// Rapid Fire Game. All Rights Reserved.

#include "Components/RFWeaponComponent.h"

#include "GameFramework/Character.h"
#include "RFBaseCharacter.h"
#include "Weapons/RFBaseWeapon.h"

URFWeaponComponent::URFWeaponComponent()
    : WeaponClasses({})
    , WeaponHandSocketName(RapidFire::Socket::WeaponSocket)
    , WeaponArmorySocketName(RapidFire::Socket::WeaponSocket)
    , CurrentWeapon(nullptr)
{
    PrimaryComponentTick.bCanEverTick = false;
}

void URFWeaponComponent::BeginPlay()
{
    Super::BeginPlay();
    SpawnWeapon();
}

void URFWeaponComponent::SpawnWeapon()
{
    if (!GetWorld() || !WeaponClasses.IsEmpty())
        return;
    auto const Character = Cast<ACharacter>(GetOwner());
    if (!Character)
        return;
    CurrentWeapon = GetWorld()->SpawnActor<ARFBaseWeapon>(WeaponClass);
    auto const AttachmentRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
    CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponHandSocketName);
    CurrentWeapon->SetOwner(GetOwner());
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
