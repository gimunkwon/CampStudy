#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BaseCharacterController.generated.h"

struct FInputActionInstance;
DECLARE_MULTICAST_DELEGATE(FInteractiveDelegate);


class UInputMappingContext;
class UInputAction;


UCLASS()
class CAMPMINIPROJECT_API ABaseCharacterController : public APlayerController
{
	GENERATED_BODY()
public:
	ABaseCharacterController();
	
	void ResumeEnemyAnimation();
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
#pragma region InputMapping,Action
	/*InputAction,InputMapping*/
	UPROPERTY(EditAnywhere,Category="Input| InputMapping")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	UPROPERTY(EditAnywhere,Category="Input| InputMapping")
	TObjectPtr<UInputMappingContext> ClashMappingContext;
	
	UPROPERTY(EditAnywhere,Category="Input| InputAction")
	TObjectPtr<UInputAction> IA_ClickToMove;
	
	UPROPERTY(EditAnywhere,Category="Input| InputAction")
	TObjectPtr<UInputAction> IA_Interactive;
	
	UPROPERTY(EditAnywhere,Category="Input| InputAction")
	TObjectPtr<UInputAction> IA_Clash_Q;
	UPROPERTY(EditAnywhere,Category="Input| InputAction")
	TObjectPtr<UInputAction> IA_Clash_W;
	
	/*-------Functions-------*/
	void OnInputClickToMove();
	void OnInputInteractive();
	
	void OnInputClashKey(const FInputActionInstance& Instance);
	
#pragma endregion 
};

