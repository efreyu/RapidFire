// Rapid Fire Game. All Rights Reserved.

#pragma once

#include "Animation/AnimNotifies/AnimNotify.h"
#include "CoreMinimal.h"
#include "RFEquipFinishedAnimNotify.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnNotifySignature);

UCLASS()
class RAPIDFIRE_API URFEquipFinishedAnimNotify : public UAnimNotify
{
    GENERATED_BODY()

public:
    void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

    FOnNotifySignature OnNotified;
};
