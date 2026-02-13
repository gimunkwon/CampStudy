#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class CAMPMINIPROJECT_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter();
	
#pragma region Movement
	void MoveToLocation(FVector& TargetLocation);
#pragma endregion
	
protected:
	virtual void BeginPlay() override;
	
#pragma region Camera,SpringArm
	UPROPERTY(VisibleAnywhere, Category="Camera")
	TObjectPtr<UCameraComponent> TopDownCamera;
	UPROPERTY(VisibleAnywhere, Category="Camera|SpringArm")
	TObjectPtr<USpringArmComponent> SpringArmComp;
#pragma endregion
	
};
