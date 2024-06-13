// Rapid Fire Game. All Rights Reserved.

#include "Animations/RFReloadFinishedAnimNotify.h"

void URFReloadFinishedAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, FAnimNotifyEventReference const& EventReference)
{
    OnNotified.Broadcast(MeshComp);
    Super::Notify(MeshComp, Animation, EventReference);
}
