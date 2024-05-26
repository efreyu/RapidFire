// Rapid Fire Game. All Rights Reserved.

#include "Player/RFBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/RFCharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ARFBaseCharacter::ARFBaseCharacter(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<URFCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
    PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    check(SpringArmComponent);
    if (SpringArmComponent)
    {
        SpringArmComponent->SetupAttachment(GetRootComponent());
        SpringArmComponent->TargetArmLength = 300.0f;
        SpringArmComponent->bUsePawnControlRotation = true;
    }

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    check(CameraComponent);
    if (CameraComponent)
    {
        CameraComponent->SetupAttachment(SpringArmComponent);
    }
}

// Called when the game starts or when spawned
void ARFBaseCharacter::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ARFBaseCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ARFBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(RapidFire::Input::MoveForwardAxis, this, &ARFBaseCharacter::OnMoveForwardAxis);
    PlayerInputComponent->BindAxis(RapidFire::Input::MoveRightAxis, this, &ARFBaseCharacter::OnMoveRightAxis);
    PlayerInputComponent->BindAxis(RapidFire::Input::LookUpAxis, this, &ARFBaseCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis(RapidFire::Input::TurnAroundAxis, this, &ARFBaseCharacter::AddControllerYawInput);

    FInputActionBinding JumpPressedBinding(RapidFire::Input::JumpAction, IE_Pressed);
    JumpPressedBinding.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() {
        Jump();
        OnJumpStarted.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Actor: '%s', Debug info %s"), *GetName(), *FString::Printf(TEXT("Jump Pressed")));
    });
    PlayerInputComponent->AddActionBinding(JumpPressedBinding);

    FInputActionBinding SprintPressedBinding(RapidFire::Input::SprintAction, IE_Pressed);
    SprintPressedBinding.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() {
        OnSprintAction(true);
    });
    PlayerInputComponent->AddActionBinding(SprintPressedBinding);
    FInputActionBinding SprintReleasedBinding(RapidFire::Input::SprintAction, IE_Released);
    SprintReleasedBinding.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() {
        OnSprintAction(false);
    });
    PlayerInputComponent->AddActionBinding(SprintReleasedBinding);
}

void ARFBaseCharacter::OnMoveForwardAxis(float Amount)
{
    bIsMovingForward = Amount > 0.0f;
    AddMovementInput(GetActorForwardVector(), Amount);
}

void ARFBaseCharacter::OnMoveRightAxis(float Amount)
{
    AddMovementInput(GetActorRightVector(), Amount);
}

void ARFBaseCharacter::OnSprintAction(bool Pressed)
{
    bIsGoingToSprint = Pressed;
}

bool ARFBaseCharacter::IsRunning() const
{
    return bIsMovingForward && bIsGoingToSprint && !GetVelocity().IsZero();
}
