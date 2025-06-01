// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_EnemyAIController.h"
#include "ArpgProject/PlayerCharacter/PlayerCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "PatrolPoints/PatrolPoint.h"
#include "CPP_EnemyBase.generated.h"

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	EES_Idle UMETA(DisplayName = "Idle"),
	EES_Patrol UMETA(DisplayName = "Patrol"),
	EES_Chase UMETA(DisplayName = "Chase"),
	EES_Attack UMETA(DisplayName = "Attack"),
	EES_Dead UMETA(DisplayName = "Dead"),

	EES_Max UMETA(DisplayName = "DefaultMax"),
};

UCLASS()
class ARPGPROJECT_API ACPP_EnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	ACPP_EnemyBase();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	APlayerCharacter* PlayerCharacter;
	
	UPROPERTY(VisibleAnywhere)
	EEnemyState EnemyState;

	UPROPERTY(EditInstanceOnly, Category="AI Patrol")
	TArray<APatrolPoint*> PatrolPoint;

	UFUNCTION(BlueprintCallable, Category="AI Patrol")
	const TArray<APatrolPoint*>& GetPatrolSpheres() const { return PatrolPoint; }
	
private:
	friend class UEnemyPawnSensingComponent;

	UPROPERTY(EditAnywhere,Category="EnemyAttackCollision")
	TObjectPtr<UBoxComponent> AttackCollisionComponent;

	UPROPERTY(EditAnywhere,Category="EnemyAttackCollision")
	float AttackCollisionX = 150.f;
	UPROPERTY(EditAnywhere,Category="EnemyAttackCollision")
	float AttackCollisionY = 150.f;
	UPROPERTY(EditAnywhere,Category="EnemyAttackCollision")
	float AttackCollisionZ = 88.f;

	UPROPERTY(EditAnywhere,Category="Widget")
	TObjectPtr<UWidgetComponent> WidgetComponent;

	UPROPERTY(visibleAnywhere)
	TObjectPtr<UEnemyPawnSensingComponent> PawnSensingComponent;

	UPROPERTY()
	TObjectPtr<ACPP_EnemyAIController> CPP_EnemyAIController;

	UPROPERTY(EditAnywhere,Category="Attribute")
	float HP;

	UPROPERTY(EditAnywhere,Category="Attribute")
	float MaxHP = 100.f;

	UPROPERTY(VisibleAnywhere,Category="Attack")
	bool CanAttack = false;

	UPROPERTY(VisibleAnywhere,Category="Attack")
	bool bAttacking = false;
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	

	
	
};
