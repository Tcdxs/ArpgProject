// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPawnSensingComponent.h"

#include "CPP_EnemyAIController.h"
#include "ArpgProject/PlayerCharacter/PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/PawnSensingComponent.h"


UEnemyPawnSensingComponent::UEnemyPawnSensingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	Enemy = Cast<ACPP_EnemyBase>(GetOwner());
	
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
	FindingCharacter = nullptr;
	CPP_EnemyAIController = Cast<ACPP_EnemyAIController>(Enemy->GetController());
	CPP_EnemyAIController->GetBlackboardComponent()->SetValueAsObject("PlayerCharacter", FindingCharacter);
}

void UEnemyPawnSensingComponent::OnSeePawn(APawn* Pawn)
{
	if (Enemy == nullptr || Enemy->GetController() == nullptr) return;
	UE_LOG(LogTemp, Warning, TEXT("敌人看见了玩家：%s"), *Pawn->GetName());
	FindingCharacter = Cast<APlayerCharacter>(Pawn);
	CPP_EnemyAIController->GetBlackboardComponent()->SetValueAsObject("PlayerCharacter", FindingCharacter);
	GetWorld()->GetTimerManager().SetTimer(
	   SightLostTimerHandle, 
	   this, 
	   &UEnemyPawnSensingComponent::HandleSightLost,
	   5.0f,
	   false
   );
}


void UEnemyPawnSensingComponent::OnHearNoise(APawn* Pawn, const FVector& Location, float Volume)
{
	if (Enemy == nullptr || Enemy->GetController() == nullptr) return;
	UE_LOG(LogTemp, Warning, TEXT("敌人听见了玩家：%s"), *Pawn->GetName());
}



void UEnemyPawnSensingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

void UEnemyPawnSensingComponent::HandleSightLost()
{
	UE_LOG(LogTemp, Warning, TEXT("Lost sight of pawn"));
	FindingCharacter = nullptr;
	CPP_EnemyAIController->GetBlackboardComponent()->SetValueAsObject("PlayerCharacter", nullptr);
}

