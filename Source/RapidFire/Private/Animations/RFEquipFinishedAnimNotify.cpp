// Rapid Fire Game. All Rights Reserved.

#include "Animations/RFEquipFinishedAnimNotify.h"

void URFEquipFinishedAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    OnNotified.Broadcast(MeshComp);
    Super::Notify(MeshComp, Animation);
}
