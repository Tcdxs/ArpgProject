// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_EnemyAnim.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


void UCPP_EnemyAnim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Enemy = Cast<ACPP_EnemyBase>(TryGetPawnOwner());
}

void UCPP_EnemyAnim::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
	Enemy = Cast<ACPP_EnemyBase>(TryGetPawnOwner());
	if (Enemy == nullptr) return;
	
	FVector Velocity = Enemy->GetVelocity();
	Velocity.Z=0.f;
	Speed = Velocity.Size();
	
	bIsAir = Enemy->GetCharacterMovement()->IsFalling();

	//Blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
	//if (Blackboard != nullptr) bIsAttacking = Blackboard->GetValueAsBool("bAttacking");
	
}
