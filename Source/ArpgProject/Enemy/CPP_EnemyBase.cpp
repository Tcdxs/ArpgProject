// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_EnemyBase.h"

#include "CPP_EnemyAIController.h"
#include "EnemyPawnSensingComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"


ACPP_EnemyBase::ACPP_EnemyBase()
{
 	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	
	
	CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionComponent"));
	check(CollisionComponent); //伤害判定碰撞体
	CollisionComponent->SetupAttachment(RootComponent);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToChannels(ECR_Ignore);
	CollisionComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	check(WidgetComponent); //UI
	WidgetComponent->SetupAttachment(RootComponent);

	PawnSensingComponent = CreateDefaultSubobject<UEnemyPawnSensingComponent>(TEXT("EnemyPawnSensingComponent"));
	check(PawnSensingComponent); //Pawn的感知组件

	AIControllerClass = ACPP_EnemyAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	EnemyState = EEnemyState::EES_Idle;
	HP = MaxHP;
}

void ACPP_EnemyBase::BeginPlay()
{
	Super::BeginPlay();

	if (WidgetComponent)
	{
		WidgetComponent->SetVisibility(false);
	}
	
}

void ACPP_EnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPP_EnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

