#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BaseCharacterController.generated.h"

class UInputMappingContext;
class UInputAction;


UCLASS()
class CAMPMINIPROJECT_API ABaseCharacterController : public APlayerController
{
	GENERATED_BODY()
public:
	ABaseCharacterController();
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
#pragma region InputMapping,Action
	/*InputAction,InputMapping*/
	UPROPERTY(EditAnywhere,Category="Input| InputMapping")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	
	UPROPERTY(EditAnywhere,Category="Input| InputAction")
	TObjectPtr<UInputAction> IA_ClickToMove;
	
	/*-------Functions-------*/
	void OnInputClickToMove();
	
#pragma endregion 
};
