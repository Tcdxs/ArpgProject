// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_EnemyAIController.h"


void ACPP_EnemyAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ACPP_EnemyAIController::ChasePlayer(APawn* PlayerPawn)
{
	if (PlayerPawn)
	{
		MoveToActor(PlayerPawn, 10.0f);
	}
}
