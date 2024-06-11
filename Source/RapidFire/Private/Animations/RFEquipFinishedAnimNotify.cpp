// Rapid Fire Game. All Rights Reserved.

#include "Animations/RFEquipFinishedAnimNotify.h"

void URFEquipFinishedAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    OnNotified.Broadcast();
    Super::Notify(MeshComp, Animation);
}
