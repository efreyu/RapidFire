// Rapid Fire Game. All Rights Reserved.

#include "Weapons/Components/RFWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"

URFWeaponFXComponent::URFWeaponFXComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void URFWeaponFXComponent::PlayVFX(FHitResult const& HitData)
{
    // Check if the Effect is valid
    if (Effect)
    {
        // Spawn the Effect at the Hit Location
        UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Effect, HitData.ImpactPoint, HitData.ImpactNormal.Rotation());
    }
}
