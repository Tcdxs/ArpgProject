// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Enemy.h"

#include "CPP_EnemyAIController.h"
#include "EnemyPawnSensingComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"


ACPP_Enemy::ACPP_Enemy()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionComponent"));
	check(CollisionComponent); //伤害判定碰撞体
	SetRootComponent(CollisionComponent);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToChannels(ECR_Ignore);
	CollisionComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	check(SkeletalMeshComponent); //骨骼
	SkeletalMeshComponent->SetupAttachment(RootComponent);
	SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	check(WidgetComponent); //UI
	WidgetComponent->SetupAttachment(RootComponent);

	PawnSensingComponent = CreateDefaultSubobject<UEnemyPawnSensingComponent>(TEXT("EnemyPawnSensingComponent"));
	check(PawnSensingComponent); //Pawn的感知组件

	AIControllerClass = ACPP_EnemyAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	EnemyState = EEnemyState::EES_Idle;
	HP = MaxHP;
	TargetPlayer = nullptr;
}

void ACPP_Enemy::BeginPlay()
{
	Super::BeginPlay();

	if (WidgetComponent)
	{
		WidgetComponent->SetVisibility(false);
	}

	if (TargetPlayer == nullptr)
	{
		FindTargetPlayer();
	}
}

inline void ACPP_Enemy::FindTargetPlayer()
{
	AActor* FindActor = UGameplayStatics::GetActorOfClass(GetWorld(), InsPlayer);
	if (FindActor)
	{
		TargetPlayer = Cast<APlayerCharacter>(FindActor);
		if (TargetPlayer)
		{
			CPP_EnemyAIController = Cast<ACPP_EnemyAIController>(GetController());
			CPP_EnemyAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
			CPP_EnemyAIController->GetBlackboardComponent()->SetValueAsObject("PlayerCharacter", TargetPlayer);
			CPP_EnemyAIController->RunBehaviorTree(BehaviorTree);
		}
	}
}

void ACPP_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACPP_Enemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
