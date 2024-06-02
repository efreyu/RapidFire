// Rapid Fire Game. All Rights Reserved.

#include "Components/RFWeaponComponent.h"

#include "GameFramework/Character.h"
#include "RFBaseCharacter.h"
#include "Weapons/RFBaseWeapon.h"

URFWeaponComponent::URFWeaponComponent()
    : WeaponClass(nullptr)
    , WeaponAttachSocketName(RapidFire::Socket::WeaponSocket)
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
    if (!GetWorld() || !WeaponClass)
        return;
    auto const Character = Cast<ACharacter>(GetOwner());
    if (!Character)
        return;
    CurrentWeapon = GetWorld()->SpawnActor<ARFBaseWeapon>(WeaponClass);
    auto const AttachmentRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
    CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponAttachSocketName);
    CurrentWeapon->SetOwner(GetOwner());
}

void URFWeaponComponent::Fire()
{
    if (!CurrentWeapon)
        return;
    CurrentWeapon->Fire();
}
