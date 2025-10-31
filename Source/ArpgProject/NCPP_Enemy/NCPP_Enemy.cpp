// Fill out your copyright notice in the Description page of Project Settings.


#include "NCPP_Enemy.h"

#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "Perception/AIPerceptionComponent.h"

ANCPP_Enemy::ANCPP_Enemy()
{
	PrimaryActorTick.bCanEverTick = false;

	BehaviorTree = CreateDefaultSubobject<UBehaviorTree>(TEXT("UBehaviorTree"));

	Blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));

	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));

	SetupPerceptionSystem();
}

void ANCPP_Enemy::BeginPlay()
{
	Super::BeginPlay();
	if (BehaviorTree)
	{
		AAIController* AIController = Cast<AAIController>(GetController());
		if (AIController)
		{
			AIController->RunBehaviorTree(BehaviorTree);
			Blackboard = AIController->GetBlackboardComponent();
			if (Blackboard)
			{
				Blackboard->SetValueAsBool("CanAttack", false);
			}
		}
	}
}

void ANCPP_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANCPP_Enemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ANCPP_Enemy::SetupPerceptionSystem()
{
	if (!AIPerceptionComponent) return;
	SenseConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AI_Sight"));
	if (SenseConfig_Sight)
	{
		SenseConfig_Sight->DetectionByAffiliation.bDetectEnemies = true;
		SenseConfig_Sight->DetectionByAffiliation.bDetectFriendlies = true;
		SenseConfig_Sight->DetectionByAffiliation.bDetectNeutrals = true;
	
		SenseConfig_Sight->SightRadius =SightRadius;
		SenseConfig_Sight->LoseSightRadius=LoseSightRadius;
		SenseConfig_Sight->PeripheralVisionAngleDegrees =SightAngleDegress;
		
		AIPerceptionComponent->ConfigureSense(*SenseConfig_Sight);
	}
	SenseConfig_Hearing = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("AI_Hear"));
	if (SenseConfig_Hearing)
	{
		SenseConfig_Hearing->DetectionByAffiliation.bDetectEnemies = true;
		SenseConfig_Hearing->DetectionByAffiliation.bDetectFriendlies = true;
		SenseConfig_Hearing->DetectionByAffiliation.bDetectNeutrals = true;

		SenseConfig_Hearing->HearingRange=HearingRange;
		//SenseConfig_Hearing->LoSHearingRange=LoSHearingRange;
		SenseConfig_Hearing->SetMaxAge(MaxAgeTime);
		
		
		AIPerceptionComponent->ConfigureSense(*SenseConfig_Hearing);
	}
	AIPerceptionComponent->SetDominantSense(SenseConfig_Sight->GetSenseImplementation());
}




