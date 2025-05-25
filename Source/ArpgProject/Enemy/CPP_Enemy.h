// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Pawn.h"
#include "Perception/PawnSensingComponent.h"
#include "CPP_Enemy.generated.h"

class UWidgetComponent;

UCLASS()
class ARPGPROJECT_API ACPP_Enemy : public APawn
{
	GENERATED_BODY()

public:
	ACPP_Enemy();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	friend class UEnemyPawnSensingComponent;
	
	UPROPERTY(EditAnywhere,Category="EnemyMesh")
	USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(EditAnywhere,Category="EnemyMesh")
	UCapsuleComponent* CollisionComponent;

	UPROPERTY(EditAnywhere,Category="Widget")
	UWidgetComponent* WidgetComponent;

	UPROPERTY(visibleAnywhere)
	class UEnemyPawnSensingComponent* PawnSensingComponent;
		
protected:
	virtual void BeginPlay() override;

public:	


	
	
};
