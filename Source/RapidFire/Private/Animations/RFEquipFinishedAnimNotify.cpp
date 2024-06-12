// Rapid Fire Game. All Rights Reserved.

#include "Animations/RFEquipFinishedAnimNotify.h"

void URFEquipFinishedAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, FAnimNotifyEventReference const& EventReference)
{
    OnNotified.Broadcast(MeshComp);
    Super::Notify(MeshComp, Animation, EventReference);
}
