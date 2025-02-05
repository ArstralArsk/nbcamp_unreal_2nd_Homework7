
#include "CustomPawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/PlayerController.h"

// Sets default values
ACustomPawn::ACustomPawn()
{
    PrimaryActorTick.bCanEverTick = true;

    CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
    CapsuleComponent->SetCapsuleSize(42.0f, 96.0f);
    CapsuleComponent->SetSimulatePhysics(false);
    RootComponent = CapsuleComponent;

    MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
    MeshComponent->SetupAttachment(RootComponent);
    MeshComponent->SetSimulatePhysics(false);

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArmComponent->SetupAttachment(RootComponent);
    SpringArmComponent->TargetArmLength = 300.0f;
    SpringArmComponent->bUsePawnControlRotation = true;

    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
    CameraComponent->SetupAttachment(SpringArmComponent);
}

void ACustomPawn::BeginPlay()
{
    Super::BeginPlay();

    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController)
    {
        PlayerController->Possess(this);
        
        UEnhancedInputLocalPlayerSubsystem* Subsystem =
            ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

        if (Subsystem && InputMappingContext)
        {
            Subsystem->AddMappingContext(InputMappingContext, 0);
        }
    }
}

void ACustomPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ACustomPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACustomPawn::Move);
        EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACustomPawn::Look);
    }
}

void ACustomPawn::Move(const FInputActionValue& Value)
{
    FVector2D MoveInput = Value.Get<FVector2D>();
    if (MoveInput.IsNearlyZero()) return;

    FVector Forward = MoveInput.Y * UKismetMathLibrary::GetForwardVector(FRotator(0, GetControlRotation().Yaw, 0));
    FVector Right = MoveInput.X * UKismetMathLibrary::GetRightVector(FRotator(0, GetControlRotation().Yaw, GetControlRotation().Roll));
    FVector Movement = (Forward + Right).GetSafeNormal() * MoveSpeed * GetWorld()->GetDeltaSeconds();
    Movement.Z = 0.0f;
    AddActorLocalOffset(Movement,true);
}

void ACustomPawn::Look(const FInputActionValue& Value)
{
    FVector2D LookInput = Value.Get<FVector2D>();
    FRotator NewRotation = GetActorRotation();
    NewRotation.Yaw += LookInput.X * LookSensitivity;
    NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + LookInput.Y * LookSensitivity, -80.0f, 80.0f);
    SetActorRotation(NewRotation);
}
