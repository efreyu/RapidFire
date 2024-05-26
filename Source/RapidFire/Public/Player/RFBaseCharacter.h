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
        constexpr inline auto MoveForwardAxis{ "MoveForward" };
        constexpr inline auto MoveRightAxis{ "MoveRight" };
        constexpr inline auto LookUpAxis{ "LookUp" };
        constexpr inline auto TurnAroundAxis{ "TurnAround" };
        constexpr inline auto JumpAction{ "Jump" };
        constexpr inline auto SprintAction{ "Sprint" };
    } // namespace Input
} // namespace RapidFire::inline Constants

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnJumpStarted);

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

    UFUNCTION(BlueprintCallable, Category = "Movement")
    bool IsRunning() const;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

private:
    void OnMoveForwardAxis(float Amount);
    void OnMoveRightAxis(float Amount);
    void OnSprintAction(bool Pressed);

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* CameraComponent = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    USpringArmComponent* SpringArmComponent = nullptr;

    UPROPERTY(BlueprintAssignable, Category = "Movement|Events")
    FOnJumpStarted OnJumpStarted;

private:
    bool bIsGoingToSprint = false;
    bool bIsMovingForward = false;
};
