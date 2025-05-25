// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_Enemy.h"
#include "Components/ActorComponent.h"
#include "EnemyPawnSensingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARPGPROJECT_API UEnemyPawnSensingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UEnemyPawnSensingComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	friend class UCPP_Enemy;

private:
	ACPP_Enemy* Enemy;

	UPROPERTY(EditAnywhere,Category="PawnSensingComponent")
	class UPawnSensingComponent* PawnSensingComponent;

	UPROPERTY(EditAnywhere,Category="PawnSensingComponent")
	float EnemyVisionAngle = 45.f;

	UPROPERTY(EditAnywhere,Category="PawnSensingComponent")
	float EnemySightRadius = 2000.f;

	UPROPERTY(EditAnywhere,Category="PawnSensingComponent")
	float EnemyHearingThreshold = 600.f;

	UPROPERTY(EditAnywhere,Category="PawnSensingComponent")
	float EnemyLoSHearingThreshold = 1200.f;
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnSeePawn(APawn* Pawn);

	UFUNCTION()
	virtual void OnHearNoise(APawn* Pawn, const FVector& Location, float Volume);
public:	
	
	
};
