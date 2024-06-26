// Rapid Fire Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RFBaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class URFHealthComponent;
class UTextRenderComponent;
class URFWeaponComponent;

namespace RapidFire::inline Constants
{
    namespace Input
    {
        constexpr inline auto MoveForwardAxis{ TEXT("MoveForward") };
        constexpr inline auto MoveRightAxis{ TEXT("MoveRight") };
        constexpr inline auto LookUpAxis{ TEXT("LookUp") };
        constexpr inline auto TurnAroundAxis{ TEXT("TurnAround") };
        constexpr inline auto JumpAction{ TEXT("Jump") };
        constexpr inline auto SprintAction{ TEXT("Sprint") };
        constexpr inline auto FireAction{ TEXT("Fire") };
        constexpr inline auto NextWeaponAction{ TEXT("NextWeapon") };
        constexpr inline auto ReloadAction{ TEXT("Reload") };
    } // namespace Input
} // namespace RapidFire::inline Constants

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnJumpStartedSignature);

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
    void OnDeath();
    void OnHealthChanged(float Health);

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* CameraComponent{ nullptr };

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    USpringArmComponent* SpringArmComponent{ nullptr };

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    URFHealthComponent* HealthComponent{ nullptr };

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    UTextRenderComponent* TextRenderComponent{ nullptr };

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    URFWeaponComponent* WeaponComponent{ nullptr };

    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    UAnimMontage* DeathAnimMontage{ nullptr };

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnJumpStartedSignature OnJumpStarted;

private:
    bool bIsGoingToSprint{ false };
    bool bIsMovingForward{ false };
};
