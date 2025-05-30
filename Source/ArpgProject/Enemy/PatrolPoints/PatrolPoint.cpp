// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolPoint.h"

#include "Components/SphereComponent.h"


APatrolPoint::APatrolPoint()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SetRootComponent(SphereCollision);
	SphereCollision->SetSphereRadius(50.f);
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
	SphereMesh->SetupAttachment(RootComponent);
	SphereMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshAsset(
	   TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if (SphereMeshAsset.Succeeded())
	{
		SphereMesh->SetStaticMesh(SphereMeshAsset.Object);
		SphereMesh->SetRelativeScale3D(FVector(1.0f));
	}
}

void APatrolPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

void APatrolPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APatrolPoint::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

