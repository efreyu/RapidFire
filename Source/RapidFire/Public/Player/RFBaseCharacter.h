// Rapid Fire Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RFBaseCharacter.generated.h"

// forward declaration
class UCameraComponent;
class USpringArmComponent;
class URFHealthComponent;
class UTextRenderComponent;

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
    ARFBaseCharacter(FObjectInitializer const& ObjectInitializer);
    virtual void Tick(float DeltaTime) override;

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UFUNCTION(BlueprintCallable, Category = "Movement")
    bool IsRunning() const;
    UFUNCTION(BlueprintCallable, Category = "Movement")
    float GetMovementDirection() const;

protected:
    virtual void BeginPlay() override;

private:
    void OnMoveForwardAxis(float Amount);
    void OnMoveRightAxis(float Amount);
    void OnSprintAction(bool Pressed);

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* CameraComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    USpringArmComponent* SpringArmComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    URFHealthComponent* HealthComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    UTextRenderComponent* TextRenderComponent;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnJumpStarted OnJumpStarted;

private:
    bool bIsGoingToSprint;
    bool bIsMovingForward;
};
