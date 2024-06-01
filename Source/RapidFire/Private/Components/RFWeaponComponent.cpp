// Rapid Fire Game. All Rights Reserved.

#include "Components/RFWeaponComponent.h"

#include "GameFramework/Character.h"
#include "RFBaseCharacter.h"
#include "Weapons/RFBaseWeapon.h"

URFWeaponComponent::URFWeaponComponent()
    : WeaponClass(nullptr)
    , WeaponAttachSocketName(RapidFire::Socket::WeaponSocket)
{
    PrimaryComponentTick.bCanEverTick = false;
}

void URFWeaponComponent::BeginPlay()
{
    Super::BeginPlay();
    check(WeaponClass);
    SpawnWeapon();
}

void URFWeaponComponent::SpawnWeapon() const
{
    if (!GetWorld())
        return;
    auto const Character = Cast<ACharacter>(GetOwner());
    if (!Character)
        return;
    auto const Weapon = GetWorld()->SpawnActor<ARFBaseWeapon>(WeaponClass);
    auto const AttachmentRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
    Weapon->AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponAttachSocketName);
}
