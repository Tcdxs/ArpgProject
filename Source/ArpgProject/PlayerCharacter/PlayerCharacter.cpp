
#include "PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include  "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"

/*				接口实现				*/

bool APlayerCharacter::GetBoolValue_Implementation(const FString& Key) const
{
	if (Key == "JumpPressed") return JumpPressed;
	
	return false;
}

void APlayerCharacter::ToTriggerAction_Jump_Implementation()
{
	SetJumpingRotationRate(1000.f);
	Jump();
	WPressTimer = 0.0f;
}

void APlayerCharacter::Jump_End_Implementation()
{
	JumpPressed = false;
	ResetRotationRate();
	StopJumping();
}


APlayerCharacter::APlayerCharacter()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	/*			移动相关设置			*/
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.f, 0.0f); 
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->AirControl = 0.2f;
	
	DefaultRotationRate = GetCharacterMovement()->RotationRate;

	/*			摄像机相关设置			*/
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 600.f;
	CameraBoom->bUsePawnControlRotation = true;
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	/*			Action组件相关设置			*/
	PlayerActionComponent = CreateDefaultSubobject<UPlayerActionComponent>(TEXT("PlayerActionComponent"));
	if (PlayerActionComponent) PlayerActionComponent->SetComponentTickEnabled(true);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	/*				增强输入组件设置				*/
	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController)
	{
		// 获取EnhancedInput子系统
		UEnhancedInputLocalPlayerSubsystem* Subsystem = 
		  ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem && InputMappingContext)
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}

	
}

void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &APlayerCharacter::A_StopMove);

	if (!EnhancedInputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("EnhancedInputComponent is nullptr"));
		return;
	}

	if (MoveAction)
	{
		EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&APlayerCharacter::A_Move);
	}
	
	if (LookAction)
	{
		EnhancedInputComponent->BindAction(LookAction,ETriggerEvent::Triggered,this,&APlayerCharacter::A_Look);
	}

	if (JumpAction)
	{
		EnhancedInputComponent->BindAction(JumpAction,ETriggerEvent::Started,this,&APlayerCharacter::A_JumpPressedStart);
		EnhancedInputComponent->BindAction(JumpAction,ETriggerEvent::Completed,this,&APlayerCharacter::A_JumpPressedEnd);
	}
	if (AttackAction)
	{
		EnhancedInputComponent->BindAction(AttackAction,ETriggerEvent::Started,this,&APlayerCharacter::A_Attack);
	}
}


void APlayerCharacter::A_Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	
	//检测W是否按下
	if (MovementVector.Y > 0.1f)
	{
		if (!bPressingW)
		{
			bPressingW = true;
			WPressTimer = 0.0f;  
		}
	}
	else
	{
		bPressingW = false;
		WPressTimer = 0.0f;  
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed; 
	}
	
	if (Controller != nullptr)
	{
		//获取控制器的旋转
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0,Rotation.Yaw,0);

		//获取向前和向右变量
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		//应用移动输入
		AddMovementInput(ForwardDirection,MovementVector.Y);
		AddMovementInput(RightDirection,MovementVector.X);
	}
}
void APlayerCharacter::A_StopMove(const FInputActionValue& Value)
{
	bPressingW = false;
	WPressTimer = 0.0f;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void APlayerCharacter::A_Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// 应用视角旋转
		AddControllerYawInput(LookAxisVector.X * LookSensitivity);
		AddControllerPitchInput(LookAxisVector.Y * LookSensitivity);
	}
}

void APlayerCharacter::A_JumpPressedStart(const FInputActionValue& Value)
{
	bSpacePressed = true;
	JumpPressed = true;
	UAnimMontage* CurrentMontage = GetMesh()->GetAnimInstance()->GetCurrentActiveMontage();
	if (CurrentMontage) StopAnimMontage(CurrentMontage);
	II_DataTransfer::Execute_ToTriggerAction(PlayerActionComponent, NoAction, EActionPriorityType::Max);
}

void APlayerCharacter::A_JumpPressedEnd(const FInputActionValue& Value)
{
	bSpacePressed = false;
}

void APlayerCharacter::A_Attack(const FInputActionValue& Value)
{
	if (Test != nullptr)
	{
		II_DataTransfer::Execute_ToTriggerAction(PlayerActionComponent, Test, EActionPriorityType::Max);
	}
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bPressingW)
	{
		WPressTimer += DeltaTime;

		if (WPressTimer >= MaxSpeedDelay)
		{
			GetCharacterMovement()->MaxWalkSpeed = SprintSpeed; 
		}
		else
		{
			GetCharacterMovement()->MaxWalkSpeed = WalkSpeed; 
		}
	}

}


void APlayerCharacter::SetJumpingRotationRate(float ZRotationRate)
{
	GetCharacterMovement()->RotationRate = FRotator(0.f, ZRotationRate, 0.f);
}

void APlayerCharacter::ResetRotationRate()
{
	GetCharacterMovement()->RotationRate = DefaultRotationRate;
}

