// Rapid Fire Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RFBaseCharacter.generated.h"

// forward declaration
class UCameraComponent;
class USpringArmComponent;

namespace RapidFire::inline Constants
{
    namespace Input
    {
        constexpr inline auto MoveForwardAxis = "MoveForward";
        constexpr inline auto MoveRightAxis = "MoveRight";
        constexpr inline auto LookUpAxis = "LookUp";
        constexpr inline auto TurnAroundAxis = "TurnAround";
        constexpr inline auto JumpAction = "Jump";
    } // namespace Input
} // namespace RapidFire::inline Constants

UCLASS()
class RAPIDFIRE_API ARFBaseCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    ARFBaseCharacter();
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

private:
    void OnMoveForwardAxis(float Amount);
    void OnMoveRightAxis(float Amount);

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* CameraComponent = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    USpringArmComponent* SpringArmComponent = nullptr;
};
