// Rapid Fire Game. All Rights Reserved.

#include "Components/RFCharacterMovementComponent.h"
#include "Player/RFBaseCharacter.h"

URFCharacterMovementComponent::URFCharacterMovementComponent(FObjectInitializer const& ObjectInitializer)
    : Super(ObjectInitializer) {}

float URFCharacterMovementComponent::GetMaxSpeed() const
{
    ARFBaseCharacter const* ActorOwner = Cast<ARFBaseCharacter>(GetPawnOwner());
    return ActorOwner && ActorOwner->IsRunning() ? Super::GetMaxSpeed() * RunSpeedModifier : Super::GetMaxSpeed();
}
