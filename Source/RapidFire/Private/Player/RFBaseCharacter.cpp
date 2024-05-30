// Rapid Fire Game. All Rights Reserved.

#include "Player/RFBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/RFCharacterMovementComponent.h"
#include "Components/RFHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/SpringArmComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseCharacter, All, All);

ARFBaseCharacter::ARFBaseCharacter(FObjectInitializer const& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<URFCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
    , CameraComponent(nullptr)
    , SpringArmComponent(nullptr)
    , HealthComponent(nullptr)
    , TextRenderComponent(nullptr)
    , bIsGoingToSprint(false)
    , bIsMovingForward(false)
{
    PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    if (SpringArmComponent)
    {
        SpringArmComponent->SetupAttachment(GetRootComponent());
        SpringArmComponent->TargetArmLength = 300.0f;
        SpringArmComponent->bUsePawnControlRotation = true;
    }

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    if (CameraComponent)
    {
        CameraComponent->SetupAttachment(SpringArmComponent);
    }

    HealthComponent = CreateDefaultSubobject<URFHealthComponent>(RapidFire::HealthComponentName);
    TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>("TextRenderComponent");
    if (TextRenderComponent)
    {
        TextRenderComponent->SetupAttachment(GetRootComponent());
        TextRenderComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 120.0f));
        TextRenderComponent->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
        TextRenderComponent->SetHorizontalAlignment(EHTA_Center);
        TextRenderComponent->SetVerticalAlignment(EVRTA_TextCenter);
        TextRenderComponent->SetTextRenderColor(FColor::Cyan);
        TextRenderComponent->SetText(FText::FromString(TEXT("0")));
    }
}

void ARFBaseCharacter::BeginPlay()
{
    Super::BeginPlay();
    // prevent blueprint overrides
    check(SpringArmComponent);
    check(CameraComponent);
    check(HealthComponent);
    check(TextRenderComponent);
}

void ARFBaseCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (HealthComponent && TextRenderComponent)
    {
        auto const Health = HealthComponent->GetHealth();
        TextRenderComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
    }
}

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

float ARFBaseCharacter::GetMovementDirection() const
{
    if (GetVelocity().IsZero())
        return 0.f;
    auto const Velocity = GetVelocity().GetSafeNormal();
    auto const AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), Velocity));
    auto const CrossProduct = FVector::CrossProduct(GetActorForwardVector(), Velocity);
    auto const Radians = FMath::RadiansToDegrees(AngleBetween);
    return static_cast<float>(FMath::Abs(CrossProduct.Z) == 0.0 ? Radians : Radians * FMath::Sign(CrossProduct.Z));
}
