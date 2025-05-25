// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Enemy.h"

#include "CPP_EnemyAIController.h"
#include "EnemyPawnSensingComponent.h"
#include "Components/WidgetComponent.h"


ACPP_Enemy::ACPP_Enemy()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionComponent"));
	SetRootComponent(CollisionComponent);
	
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetupAttachment(RootComponent);
    SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetupAttachment(RootComponent);

	PawnSensingComponent = CreateDefaultSubobject<UEnemyPawnSensingComponent>(TEXT("EnemyPawnSensingComponent"));
	
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ACPP_EnemyAIController::StaticClass();
}

void ACPP_Enemy::BeginPlay()
{
	Super::BeginPlay();
	
	if (WidgetComponent)
	{
		WidgetComponent->SetVisibility(false);
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

