

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "CPP_EnemyAIController.generated.h"

class ACPP_EnemyBase;
/**
 * 
 */
UCLASS()
class ARPGPROJECT_API ACPP_EnemyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ACPP_EnemyAIController();
	
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UBehaviorTree> BehaviorTreeComponent;
private:
	friend class ACPP_Enemy;

	UPROPERTY()
	TObjectPtr<ACPP_EnemyBase> Enemy;
public:	
};
