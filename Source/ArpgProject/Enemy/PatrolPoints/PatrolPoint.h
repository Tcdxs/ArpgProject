// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Pawn.h"
#include "PatrolPoint.generated.h"

UCLASS()
class ARPGPROJECT_API APatrolPoint : public APawn
{
	GENERATED_BODY()

public:
	APatrolPoint();
	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	UPROPERTY(EditAnywhere, Category="Components")
	TObjectPtr<USphereComponent> SphereCollision;

	UPROPERTY(EditAnywhere, Category="Components")
	TObjectPtr<UStaticMeshComponent> SphereMesh;
protected:
	virtual void BeginPlay() override;

public:	
	

	
	
};
