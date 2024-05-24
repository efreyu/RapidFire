// Rapid Fire Game. All Rights Reserved.

#include "Player/RFBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"

// Sets default values
ARFBaseCharacter::ARFBaseCharacter()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    check(CameraComponent);
    if (CameraComponent)
    {
        CameraComponent->SetupAttachment(GetRootComponent());
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
    PlayerInputComponent->BindAxis(RapidFire::Input::MoveForward, this, &ARFBaseCharacter::MoveForward);
    PlayerInputComponent->BindAxis(RapidFire::Input::MoveRight, this, &ARFBaseCharacter::MoveRight);
    PlayerInputComponent->BindAxis(RapidFire::Input::LookUp, this, &ARFBaseCharacter::LookUp);
    PlayerInputComponent->BindAxis(RapidFire::Input::TurnAround, this, &ARFBaseCharacter::TurnAround);
}

void ARFBaseCharacter::MoveForward(float Amount)
{
    AddMovementInput(GetActorForwardVector(), Amount);
}

void ARFBaseCharacter::MoveRight(float Amount)
{
    AddMovementInput(GetActorRightVector(), Amount);
}

void ARFBaseCharacter::LookUp(float Amount)
{
    AddControllerPitchInput(Amount);
}

void ARFBaseCharacter::TurnAround(float Amount)
{
    AddControllerYawInput(-Amount);
}
