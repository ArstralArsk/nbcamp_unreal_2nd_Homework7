#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EnhancedInputComponent.h"
#include "CustomPawn.generated.h"

UCLASS()
class SPARTA_API ACustomPawn : public APawn
{
    GENERATED_BODY()

public:
    ACustomPawn();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
    void Move(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);

    UPROPERTY(EditAnywhere, Category = "Components")
    class UCapsuleComponent* CapsuleComponent;

    UPROPERTY(EditAnywhere, Category = "Components")
    class USkeletalMeshComponent* MeshComponent;

    UPROPERTY(EditAnywhere, Category = "Components")
    class USpringArmComponent* SpringArmComponent;

    UPROPERTY(EditAnywhere, Category = "Components")
    class UCameraComponent* CameraComponent;

    UPROPERTY(EditAnywhere, Category = "Input")
    class UInputMappingContext* InputMappingContext;

    UPROPERTY(EditAnywhere, Category = "Input")
    class UInputAction* MoveAction;

    UPROPERTY(EditAnywhere, Category = "Input")
    class UInputAction* LookAction;

    UPROPERTY(EditAnywhere, Category = "Movement")
    float MoveSpeed = 600.0f;

    UPROPERTY(EditAnywhere, Category = "Movement")
    float LookSensitivity = 1.0f;
};
