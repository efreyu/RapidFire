// Rapid Fire Game. All Rights Reserved.

#include "Components/RFCharacterMovementComponent.h"
#include "Player/RFBaseCharacter.h"

float URFCharacterMovementComponent::GetMaxSpeed() const
{
    const ARFBaseCharacter* CharacterOwner = Cast<ARFBaseCharacter>(GetPawnOwner());
    return CharacterOwner && CharacterOwner->IsRunning() ? Super::GetMaxSpeed() * RunSpeedModifier : Super::GetMaxSpeed();
}
