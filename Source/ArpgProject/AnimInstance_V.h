

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AnimInstance_V.generated.h"

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

	//旋转角度
	public:
    UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Rotation")
	float LeanAngle;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Movement")
	FVector Velocity;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Movement")
	FVector Acceleration;
	
    UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Movement")
	float MaxWalkSpeed;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Movement")
	bool bIsAccelerating;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Movement")
	bool bInAir;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Movement")
	bool bIsJumping;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Movement")
	bool bIsFalling;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Movement")
	float LocomotionDirectionAccel;


	private:
	UPROPERTY(Transient)
	APawn* OwnerPawn;

	float PreviousActorYaw;

	private:
	float SafeDivideAndClamp(float DeltaTimes , float ActorYawDelta);
	void GetRotation(float DeltaTimes);
    void GetAccelerationAndVelocity(float DeltaTimes);
	float CalculateDirectionCustom(const FVector& InVelocity, const FRotator& BaseRotation);
	
	
};
