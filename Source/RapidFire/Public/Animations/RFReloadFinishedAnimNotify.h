// Rapid Fire Game. All Rights Reserved.

#pragma once

#include "Animation/AnimNotifies/AnimNotify.h"
#include "CoreMinimal.h"
#include "RFReloadFinishedAnimNotify.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnReloadFinishedNotifySignature, USkeletalMeshComponent*);

UCLASS()
class RAPIDFIRE_API URFReloadFinishedAnimNotify : public UAnimNotify
{
    GENERATED_BODY()

public:
    void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, FAnimNotifyEventReference const& EventReference) override;

    FOnReloadFinishedNotifySignature OnNotified;
};
