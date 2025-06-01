// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_EnemyBase.h"

#include "CPP_EnemyAIController.h"
#include "EnemyPawnSensingComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"


ACPP_EnemyBase::ACPP_EnemyBase()
{
 	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	
	
	AttackCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackCollisionComponent"));
	check(AttackCollisionComponent); //伤害判定碰撞体
	AttackCollisionComponent->SetupAttachment(RootComponent);
	AttackCollisionComponent->SetCollisionResponseToChannels(ECR_Ignore);
	AttackCollisionComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	AttackCollisionComponent->SetBoxExtent(FVector(AttackCollisionX, AttackCollisionY, AttackCollisionZ));

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
	
	AttackCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ACPP_EnemyBase::OnBoxBeginOverlap);
	AttackCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ACPP_EnemyBase::OnBoxEndOverlap);
}

void ACPP_EnemyBase::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	if (PlayerCharacter && OtherComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("1"));
		CanAttack = true;
		CPP_EnemyAIController = Cast<ACPP_EnemyAIController>(GetController());
		CPP_EnemyAIController->GetBlackboardComponent()->SetValueAsBool("CanAttack", CanAttack);
	}
}

void ACPP_EnemyBase::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	if (PlayerCharacter && OtherComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("2"));
		CanAttack = false;
		CPP_EnemyAIController = Cast<ACPP_EnemyAIController>(GetController());
		CPP_EnemyAIController->GetBlackboardComponent()->SetValueAsBool("CanAttack", CanAttack);
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

