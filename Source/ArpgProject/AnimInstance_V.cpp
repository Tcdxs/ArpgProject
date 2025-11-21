// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance_V.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"






void UAnimInstance_V::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OwnerPawn = TryGetPawnOwner();

	if (OwnerPawn)
	{
		PreviousActorYaw = OwnerPawn->GetActorRotation().Yaw;
	}
	LeanAngle = 0.0f;
}


void UAnimInstance_V::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (OwnerPawn == nullptr)
	{
		OwnerPawn = TryGetPawnOwner();
		if (OwnerPawn == nullptr) return;
	}
	GetRotation(DeltaTime);
	GetAccelerationAndVelocity(DeltaTime);
	UpdateOrientData(DeltaTime);
	ChangeMoveStyle(DeltaTime);
}


void UAnimInstance_V::GetRotation(float DeltaTimes)
{
	const float ActorYaw = OwnerPawn->GetActorRotation().Yaw;
	float ActorDeltaYaw = ActorYaw - PreviousActorYaw;
	ActorDeltaYaw = FMath::UnwindDegrees(ActorDeltaYaw);
	LeanAngle = SafeDivideAndClamp(DeltaTimes,ActorDeltaYaw);
	PreviousActorYaw = ActorYaw;
}


float UAnimInstance_V::SafeDivideAndClamp(float DeltaTime, float ActorYawDelta)
{
	float YawRate = 0.0f;

	if (FMath::Abs(DeltaTime) > KINDA_SMALL_NUMBER)
	{
		YawRate = ActorYawDelta / (DeltaTime * 4.0f);
	}
	
	return FMath::Clamp(YawRate, -100.0f, 100.0f);
}


void UAnimInstance_V::GetAccelerationAndVelocity(float DeltaTime)
{
	ACharacter* Character = Cast<ACharacter>(OwnerPawn);
	if (!Character) return;

	UCharacterMovementComponent* MoveComp = Character->GetCharacterMovement();
	if (!MoveComp) return;

	
	Velocity = Character->GetVelocity();
	Velocity2D = FVector(Velocity.X, Velocity.Y, 0.f);

	Acceleration = MoveComp->GetCurrentAcceleration();
	Acceleration2D = FVector(Acceleration.X, Acceleration.Y, 0.f);

	bIsAccelerating = !Acceleration2D.IsNearlyZero(0.1f);

	LocomotionDirectionAccel = CalculateDirectionCustom(Acceleration2D, OwnerPawn->GetActorRotation());

	MaxWalkSpeed = MoveComp->GetMaxSpeed();
	bInAir = MoveComp->IsFalling();
	bIsJumping = false;
	bIsFalling = false;

	if (MoveComp->MovementMode == MOVE_Falling)
	{
		if (Velocity.Z > 0.f)
		{
			bIsJumping = true;
		}
		else if (Velocity.Z < 0.f)
		{
			bIsFalling = true;
		}
	}
}



float UAnimInstance_V::CalculateDirectionCustom(const FVector& InVelocity, const FRotator& BaseRotation)
{
	if (InVelocity.IsNearlyZero()) return 0.f;

	// 角色朝向
	FVector Forward = BaseRotation.Vector();
	Forward.Z = 0.f;
	Forward.Normalize();

	// 速度方向二维化
	FVector Vel2D = InVelocity;
	Vel2D.Z = 0.f;
	Vel2D.Normalize();

	// 角色右向量
	FVector Right = FVector::CrossProduct(FVector::UpVector, Forward);

	// 计算前向和右向分量
	float ForwardCos = FVector::DotProduct(Forward, Vel2D);
	float RightCos = FVector::DotProduct(Right, Vel2D);

	// 计算方向角度
	return FMath::RadiansToDegrees(FMath::Atan2(RightCos, ForwardCos));
}



void UAnimInstance_V::UpdateOrientData(float DeltaSeconds)
{
	if (!OwnerPawn) return;
	
	VelocityDirection = CalculateDirectionCustom(FVector(Velocity.X, Velocity.Y, 0.f), OwnerPawn->GetActorRotation());
	
	FVector Accel2D = FVector(Acceleration.X, Acceleration.Y, 0.f);

	float AngleForEnum = 0.f;
	if (!Accel2D.IsNearlyZero(0.01f))
	{
		LocomotionDirectionAccel = CalculateDirectionCustom(Accel2D, OwnerPawn->GetActorRotation());
		AngleForEnum = LocomotionDirectionAccel;
	}
	else
	{
		AngleForEnum = VelocityDirection;
	}
	
	CalculateVelocityDirection(AngleForEnum, LocomotionDirection);
	
	float NormalizedAccelAngle = FMath::UnwindDegrees(LocomotionDirectionAccel); 
	if (NormalizedAccelAngle >= -180.f && NormalizedAccelAngle <= -100.f)
	{
		bTurnLeft = true;
	}
	else if (NormalizedAccelAngle >= 100.f && NormalizedAccelAngle <= 180.f)
	{
		bTurnLeft = false;
	}
	else
	{
		bTurnLeft = false;
	}
}



void UAnimInstance_V::CalculateVelocityDirection(float Angle, ELocomotionDirection& OutDirection)
{
	float A = FMath::UnwindDegrees(Angle);
	
	if (A >= -22.5f && A <= 22.5f)
	{
		OutDirection = ELocomotionDirection::Forward;
		return;
	}
	if (A > 22.5f && A <= 67.5f)
	{
		OutDirection = ELocomotionDirection::RightForward;
		return;
	}
	if (A > 67.5f && A <= 112.5f)
	{
		OutDirection = ELocomotionDirection::Right;
		return;
	}
	if (A > 112.5f && A <= 157.5f)
	{
		OutDirection = ELocomotionDirection::RightBackward;
		return;
	}
	if (A > 157.5f || A <= -157.5f)
	{
		OutDirection = ELocomotionDirection::Backward;
		return;
	}
	if (A > -157.5f && A <= -112.5f)
	{
		OutDirection = ELocomotionDirection::LeftBackward;
		return;
	}
	if (A > -112.5f && A <= -67.5f)
	{
		OutDirection = ELocomotionDirection::Left;
		return;
	}
	if (A > -67.5f && A <= -22.5f)
	{
		OutDirection = ELocomotionDirection::LeftForward;
		return;
	}

	
	OutDirection = ELocomotionDirection::Forward;
	

}

void UAnimInstance_V::ChangeMoveStyle(float DeltaTime)
{
	if (!OwnerPawn) return;
	
	bool bAtMaxSpeed = Velocity2D.Size()>= MaxWalkSpeed - 5.f;
	if (bAtMaxSpeed)
	{
		SprintTimer += DeltaTime;
	}
	else
	{
		SprintTimer = 0.f;
		MoveStyle = EMoveStyle::Walk;
		MaxWalkSpeed = 800.f;
		
	}
	if (SprintTimer >= 2.f)
	{
		MoveStyle = EMoveStyle::Sprint;
		MaxWalkSpeed = 1000.f;
	}
	else
	{
		MoveStyle = EMoveStyle::Run;
		MaxWalkSpeed = 800.f;
	}
}






