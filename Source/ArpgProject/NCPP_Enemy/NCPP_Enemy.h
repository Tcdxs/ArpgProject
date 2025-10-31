// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NCPP_EnemyBase.h"
#include "ArpgProject/Enemy/PatrolPoints/PatrolPoint.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BehaviorTree.h"
#include "NCPP_Enemy.generated.h"

class UAISenseConfig;
class UAIPerceptionComponent;
/**
 * 
 */
UCLASS()
class ARPGPROJECT_API ANCPP_Enemy : public ANCPP_EnemyBase
{
	GENERATED_BODY()

public:
	ANCPP_Enemy();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/*  行为树  */
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	UBehaviorTree* BehaviorTree;

	/*  黑板  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	UBlackboardComponent* Blackboard;
	
	/*  AI组件  */
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	UAIPerceptionComponent* AIPerceptionComponent;

	/*  AI视觉内容  */
	
	UPROPERTY()
	UAISenseConfig_Sight* SenseConfig_Sight; //AI视觉

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	float SightRadius= 2000.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	float LoseSightRadius= 2200.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	float SightAngleDegress= 180.f;

	/*  AI听觉内容  */
	
	UPROPERTY()
	UAISenseConfig_Hearing* SenseConfig_Hearing; //AI听觉

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	float HearingRange= 1500.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	float LoSHearingRange= 1000.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	float MaxAgeTime= 5.f;
	
	/*  巡逻  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PatrolPoint")
	TArray<APatrolPoint*> N_PatrolPoint;

	UFUNCTION(BlueprintCallable, Category="PatrolPoint")
	const TArray<APatrolPoint*>& N_GetPatrolSpheres() const { return N_PatrolPoint; }
	
	void SetupPerceptionSystem();

protected:
	virtual void BeginPlay() override;

private:
	
	
	
};
