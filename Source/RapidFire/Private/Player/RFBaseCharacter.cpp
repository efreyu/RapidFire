// Rapid Fire Game. All Rights Reserved.

#include "Player/RFBaseCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/RFCharacterMovementComponent.h"
#include "Components/RFHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Weapons/RFBaseWeapon.h"

ARFBaseCharacter::ARFBaseCharacter(FObjectInitializer const& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<URFCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
    , CameraComponent(nullptr)
    , SpringArmComponent(nullptr)
    , HealthComponent(nullptr)
    , TextRenderComponent(nullptr)
    , DeathAnimMontage(nullptr)
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
        SpringArmComponent->SocketOffset = FVector(0.0f, 100.0f, 80.0f);
    }

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    if (CameraComponent)
    {
        CameraComponent->SetupAttachment(SpringArmComponent);
    }

    HealthComponent = CreateDefaultSubobject<URFHealthComponent>(RapidFire::Components::HealthComponentName);
    TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>("TextRenderComponent");
    if (TextRenderComponent)
    {
        TextRenderComponent->SetupAttachment(GetRootComponent());
        TextRenderComponent->SetOwnerNoSee(true);
    }
}

void ARFBaseCharacter::BeginPlay()
{
    Super::BeginPlay();
    // prevent blueprint overrides
    check(GetCharacterMovement());
    check(SpringArmComponent);
    check(CameraComponent);
    check(HealthComponent);
    check(TextRenderComponent);
    check(WeaponClass);

    OnHealthChanged(HealthComponent->GetHealth());
    HealthComponent->OnDeath.AddUObject(this, &ARFBaseCharacter::OnDeath);
    HealthComponent->OnHealthChanged.AddUObject(this, &ARFBaseCharacter::OnHealthChanged);
    SpawnWeapon();
}

void ARFBaseCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ARFBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    check(PlayerInputComponent);

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

void ARFBaseCharacter::OnDeath()
{
    if (DeathAnimMontage)
    {
        PlayAnimMontage(DeathAnimMontage);
        GetCharacterMovement()->DisableMovement();
        SetLifeSpan(5.f);
        if (Controller)
        {
            Controller->ChangeState(NAME_Spectating);
        }
    }
}

void ARFBaseCharacter::OnHealthChanged(float Health)
{
    if (!TextRenderComponent)
    {
        return;
    }
    TextRenderComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
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

void ARFBaseCharacter::SpawnWeapon() const
{
    if (!GetWorld())
        return;
    auto const Weapon = GetWorld()->SpawnActor<ARFBaseWeapon>(WeaponClass);
    auto const AttachmentRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
    Weapon->AttachToComponent(GetMesh(), AttachmentRules, RapidFire::Socket::WeaponSocket);
}
