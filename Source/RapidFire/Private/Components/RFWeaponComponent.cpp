// Rapid Fire Game. All Rights Reserved.

#include "Components/RFWeaponComponent.h"

#include "Animation/AnimMontage.h"
#include "Animations/RFEquipFinishedAnimNotify.h"
#include "Animations/RFReloadFinishedAnimNotify.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
#include "RFBaseCharacter.h"
#include "Weapons/RFBaseWeapon.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All);

URFWeaponComponent::URFWeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void URFWeaponComponent::BeginPlay()
{
    Super::BeginPlay();
    check(WeaponClasses.Num() > 0)
    check(Weapons.Num() == 0)
    SpawnWeapons();
    EquipWeapon(CurrentWeaponIndex);

    InitAnimations();
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
    if (EquipAnimMontage)
    {
        if (PlayAnimMontage(EquipAnimMontage))
            bIsWeaponAnimPlaying = true;
    }
}

bool URFWeaponComponent::PlayAnimMontage(UAnimMontage* AnimMontage) const
{
    auto const Character = Cast<ACharacter>(GetOwner());
    if (!Character)
        return false;
    Character->PlayAnimMontage(AnimMontage);
    return true;
}

void URFWeaponComponent::InitAnimations()
{
    if (auto const EquipFinishNotify = FindNotifyByClass<URFEquipFinishedAnimNotify>(EquipAnimMontage))
    {
        EquipFinishNotify->OnNotified.AddUObject(this, &URFWeaponComponent::OnEquipFinished);
    }
    for (auto const Weapon : Weapons)
    {
        if (Weapon)
        {
            Weapon->OnClipEmpty.AddUObject(this, &URFWeaponComponent::ReloadClip);
        }
        if (!Weapon || !Weapon->GetCurrentReloadAnimMontage())
            continue;
        if (auto const ReloadFinishNotify = FindNotifyByClass<URFReloadFinishedAnimNotify>(Weapon->GetCurrentReloadAnimMontage()))
        {
            ReloadFinishNotify->OnNotified.AddUObject(this, &URFWeaponComponent::OnReloadFinished);
        }
    }
}

void URFWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComp)
{
    auto const Character = Cast<ACharacter>(GetOwner());
    if (!Character || MeshComp != Character->GetMesh())
        return;
    bIsWeaponAnimPlaying = false;
}

void URFWeaponComponent::OnReloadFinished(USkeletalMeshComponent* MeshComp)
{
    auto const Character = Cast<ACharacter>(GetOwner());
    if (!Character || !CurrentWeapon || MeshComp != Character->GetMesh())
        return;
    CurrentWeapon->ReloadClip();
    bIsWeaponAnimPlaying = false;
}

void URFWeaponComponent::StartFire()
{
    if (!CanFire())
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
    if (!CanEquip())
        return;
    CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
    EquipWeapon(CurrentWeaponIndex);
}

bool URFWeaponComponent::CanFire() const
{
    return CurrentWeapon && !bIsWeaponAnimPlaying && CurrentWeapon->CanFire();
}

bool URFWeaponComponent::CanEquip() const
{
    return !bIsWeaponAnimPlaying;
}

void URFWeaponComponent::ReloadClip()
{
    if (CurrentWeapon && CurrentWeapon->CanReload() && CurrentWeapon->GetCurrentReloadAnimMontage())
    {
        if (PlayAnimMontage(CurrentWeapon->GetCurrentReloadAnimMontage()))
            bIsWeaponAnimPlaying = true;
    }
}
