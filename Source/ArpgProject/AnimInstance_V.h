

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AnimInstance_V.generated.h"

UENUM(BlueprintType)
enum  class ELocomotionDirection:uint8
{
	Forward,
	Backward,
	Left,
	Right,
	LeftForward,
	RightForward,
	LeftBackward,
	RightBackward
};

UENUM(BlueprintType)
enum  class EMoveStyle:uint8
{
	Walk,
	Run,
	Sprint,
};
/**
 * 
 */
UCLASS()
class ARPGPROJECT_API UAnimInstance_V : public UAnimInstance
{
	GENERATED_BODY()
	
	public:
    //初始化+帧更新
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	
	public:
	

	
	//倾斜角度
    UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Rotation")
	float LeanAngle;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Movement")
	FVector Velocity;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Movement")
	FVector Velocity2D;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Movement")
	FVector Acceleration;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Movement")
	FVector Acceleration2D;
	
    UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Movement")
	float MaxWalkSpeed;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Movement")
	bool bIsAccelerating = false;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Movement")
	bool bInAir = false;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Movement")
	bool bIsJumping = false;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Movement")
	bool bIsFalling = false;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Movement")
	float LocomotionDirectionAccel = 0.0f;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Movement")
	float VelocityDirection = 0.0f;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Movement")
	ELocomotionDirection LocomotionDirection = ELocomotionDirection::Forward;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Movement")
	EMoveStyle MoveStyle = EMoveStyle::Walk;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Movement")
	bool bTurnLeft = false;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Movement")
	bool bLockOn;


	private:
	UPROPERTY(Transient)
	APawn* OwnerPawn;

	float PreviousActorYaw;

	private:
	float SafeDivideAndClamp(float DeltaTimes , float ActorYawDelta);
	void GetRotation(float DeltaTimes);
    void GetAccelerationAndVelocity(float DeltaTimes);
	float CalculateDirectionCustom(const FVector& InVelocity, const FRotator& BaseRotation);
	void UpdateOrientData(float DeltaSeconds);
	void CalculateVelocityDirection(float Angle, ELocomotionDirection& OutDirection);
	
	
};
