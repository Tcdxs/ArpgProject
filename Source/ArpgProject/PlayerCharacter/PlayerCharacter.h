// Fill out your copyright notice in the Description page of Project Settings.
#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "ArpgProject/Interface/I_DataTransfer.h"
#include "PlayerComponent/PlayerActionComponent.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class ARPGPROJECT_API APlayerCharacter : public ACharacter, public II_DataTransfer
{
	GENERATED_BODY()

/*			接口相关			*/
	
	virtual bool GetBoolValue_Implementation(const FString& Key) const override;
	
	virtual void ToTriggerAction_Jump_Implementation() override;

	
/*			 基础设置			*/
public:
	APlayerCharacter();
	virtual void Tick(float DeltaTime) override;


	
protected:
	virtual void BeginPlay() override;

private:

	
	/*						Action组件							*/

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ActionComponents")
	UPlayerActionComponent* PlayerActionComponent;

	
	/*			数据资产库		*/
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataAsset")
	UPrimaryActionData* Test;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataAsset")
	UPrimaryActionData* NoAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataAsset")
	UPrimaryActionData* CanCombo;
protected:

	
private:
	
	
	/*						增强输入组件							*/
	
public:
	
protected:
	// 增强输入组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UEnhancedInputComponent* EnhancedInputComponent;

	// 增强输入映射上下文
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* InputMappingContext;

	// 输入动作
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* AttackAction;
	
	// 移动属性
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float WalkSpeed = 600.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float SprintSpeed = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float LookSensitivity = 1.0f;		//视角灵敏度

	
	//计时器【13】
	bool bPressingW = false;      
	float WPressTimer = 0.0f;
	float MaxSpeedDelay = 5.0f;
	
	//动画传入的变量【13】
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Movement")
	bool bCanJump_Test = false;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Movement")
	bool bCanMove_Test = false;

	//输入处理函数
	void A_Move(const FInputActionValue& Value);
	void A_StopMove(const FInputActionValue& Value);
	void A_Look(const FInputActionValue& Value);
	void A_JumpPressedStart(const FInputActionValue& Value);
	void A_JumpPressedEnd(const FInputActionValue& Value);
	void A_Attack (const FInputActionValue& Value);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void SetJumpingRotationRate(float ZRotationRate = 1500.0f);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void ResetRotationRate();
	
private:
	// 存储默认旋转速率
	FRotator DefaultRotationRate;
	bool bSpacePressed = false;
	bool JumpPressed = false;
	
	/*					摄像机相关				*/
public:
	

protected:
	
	
private:
	//弹簧手臂
	UPROPERTY(VisibleAnywhere , Category= Camera)
	class USpringArmComponent* CameraBoom;

	//运动相机
	UPROPERTY(VisibleAnywhere , Category= Camera)
	class UCameraComponent* FollowCamera;

	
};
