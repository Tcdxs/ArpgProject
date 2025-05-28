
#pragma once

#include "CoreMinimal.h"
#include "CPP_EnemyAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Pawn.h"
#include "Perception/PawnSensingComponent.h"
#include "ArpgProject/PlayerCharacter/PlayerCharacter.h"
#include "CPP_Enemy.generated.h"

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
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;

	UPROPERTY(EditAnywhere,Category="EnemyMesh")
	TObjectPtr<UCapsuleComponent> CollisionComponent;

	UPROPERTY(EditAnywhere,Category="Widget")
	TObjectPtr<UWidgetComponent> WidgetComponent;

	UPROPERTY(visibleAnywhere)
	TObjectPtr<UEnemyPawnSensingComponent> PawnSensingComponent;

	UPROPERTY(EditAnywhere, Category="AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
	TObjectPtr<ACPP_EnemyAIController> CPP_EnemyAIController;

	UPROPERTY(VisibleAnywhere)
	EEnemyState EnemyState;

	UPROPERTY(EditAnywhere,Category="Attribute")
	float HP;

	UPROPERTY(EditAnywhere,Category="Attribute")
	float MaxHP = 100.f;
		
	UPROPERTY(EditAnywhere, Category = "Attribute")
	class APlayerCharacter* TargetPlayer;

	UPROPERTY(EditAnywhere, Category = "Attribute")
	TSubclassOf<APlayerCharacter> InsPlayer;
	
protected:
	virtual void BeginPlay() override;

	virtual void FindTargetPlayer();
public:	


	
	
};


