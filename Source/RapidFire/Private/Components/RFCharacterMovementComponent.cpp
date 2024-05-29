// Rapid Fire Game. All Rights Reserved.

#include "Components/RFCharacterMovementComponent.h"
#include "Player/RFBaseCharacter.h"

URFCharacterMovementComponent::URFCharacterMovementComponent(FObjectInitializer const& ObjectInitializer)
    : Super(ObjectInitializer)
    , RunSpeedModifier(1.5f) {}

float URFCharacterMovementComponent::GetMaxSpeed() const
{
    ARFBaseCharacter const* CharacterOwner = Cast<ARFBaseCharacter>(GetPawnOwner());
    return CharacterOwner && CharacterOwner->IsRunning() ? Super::GetMaxSpeed() * RunSpeedModifier : Super::GetMaxSpeed();
}
