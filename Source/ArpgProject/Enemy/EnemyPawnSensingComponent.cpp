// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPawnSensingComponent.h"

#include "CPP_EnemyAIController.h"
#include "Perception/PawnSensingComponent.h"


UEnemyPawnSensingComponent::UEnemyPawnSensingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	Enemy = Cast<ACPP_Enemy>(GetOwner());
	
	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
	check(PawnSensingComponent);
	PawnSensingComponent->SetPeripheralVisionAngle(EnemyVisionAngle);
	PawnSensingComponent->SightRadius = EnemySightRadius;
	PawnSensingComponent->HearingThreshold = EnemyHearingThreshold;
	PawnSensingComponent->LOSHearingThreshold = EnemyLoSHearingThreshold;
	
}

void UEnemyPawnSensingComponent::BeginPlay()
{
	Super::BeginPlay();

	if (PawnSensingComponent)
	{
		PawnSensingComponent->OnSeePawn.AddDynamic(this, &UEnemyPawnSensingComponent::OnSeePawn);
		PawnSensingComponent->OnHearNoise.AddDynamic(this, &UEnemyPawnSensingComponent::OnHearNoise);
	}
}

void UEnemyPawnSensingComponent::OnSeePawn(APawn* Pawn)
{
	if (Enemy == nullptr || Enemy->GetController() == nullptr) return;
	UE_LOG(LogTemp, Warning, TEXT("敌人发现了玩家：%s"), *Pawn->GetName());
}


void UEnemyPawnSensingComponent::OnHearNoise(APawn* Pawn, const FVector& Location, float Volume)
{
	if (Enemy == nullptr || Enemy->GetController() == nullptr) return;
	UE_LOG(LogTemp, Warning, TEXT("敌人发现了玩家：%s"), *Pawn->GetName());
}



void UEnemyPawnSensingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

