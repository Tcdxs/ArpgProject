// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_EnemyBase.h"

#include "CPP_EnemyAIController.h"
#include "EnemyPawnSensingComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


ACPP_EnemyBase::ACPP_EnemyBase()
{
 	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	
	ToAttackCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("ToAttackCollisionComponent"));
	check(ToAttackCollisionComponent); //攻击范围判定碰撞体
	ToAttackCollisionComponent->SetupAttachment(RootComponent);
	ToAttackCollisionComponent->SetCollisionResponseToChannels(ECR_Ignore);
	ToAttackCollisionComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	ToAttackCollisionComponent->SetBoxExtent(FVector(AttackCollisionX, AttackCollisionY, AttackCollisionZ));

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	check(WeaponMesh);
	//if (GetMesh()->DoesSocketExist(TEXT("WeaponSocket")))
	WeaponMesh->SetupAttachment(GetMesh(),FName(TEXT("WeaponSocket")));

	AttackCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackCollisionComponent"));
	check(AttackCollisionComponent);
	AttackCollisionComponent->SetupAttachment(WeaponMesh);
	AttackCollisionComponent->SetCollisionResponseToChannels(ECR_Ignore);
	AttackCollisionComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	check(WidgetComponent); //UI
	WidgetComponent->SetupAttachment(RootComponent);

	PawnSensingComponent = CreateDefaultSubobject<UEnemyPawnSensingComponent>(TEXT("EnemyPawnSensingComponent"));
	check(PawnSensingComponent); //Pawn的感知组件

	AIControllerClass = ACPP_EnemyAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	GetCharacterMovement()->MaxWalkSpeed = 230.f;
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
	if (ToAttackCollisionComponent)
	{
		ToAttackCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ACPP_EnemyBase::OnToAttackBoxBeginOverlap);
		ToAttackCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ACPP_EnemyBase::OnToAttackBoxEndOverlap);
	}
	if (AttackCollisionComponent)
	{
		AttackCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ACPP_EnemyBase::OnAttackBoxBeginOverlap);
		AttackCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ACPP_EnemyBase::OnAttackBoxEndOverlap);
	}
}

void ACPP_EnemyBase::OnToAttackBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	if (PlayerCharacter && OtherComp)
	{
		CanAttack = true;
		CPP_EnemyAIController = Cast<ACPP_EnemyAIController>(GetController());
		if (CPP_EnemyAIController)
		CPP_EnemyAIController->GetBlackboardComponent()->SetValueAsBool("CanAttack", CanAttack);
	}
}

void ACPP_EnemyBase::OnToAttackBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	if (PlayerCharacter && OtherComp)
	{
		CanAttack = false;
		CPP_EnemyAIController = Cast<ACPP_EnemyAIController>(GetController());
		if (CPP_EnemyAIController)
		CPP_EnemyAIController->GetBlackboardComponent()->SetValueAsBool("CanAttack", CanAttack);
	}
}

void ACPP_EnemyBase::OnAttackBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

void ACPP_EnemyBase::OnAttackBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

void ACPP_EnemyBase::HandleDeath()
{
	
}

void ACPP_EnemyBase::PerformAttack()
{
	
}

void ACPP_EnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPP_EnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

