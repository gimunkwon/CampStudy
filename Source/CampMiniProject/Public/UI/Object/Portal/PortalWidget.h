#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PortalWidget.generated.h"


class UButton;

UCLASS()
class CAMPMINIPROJECT_API UPortalWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere,Category="Level")
	FName KamenRaidLevelName;
	
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> Enter_Btn;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> Close_Btn;
	
	// BlueprintCallable Function
	UFUNCTION(BlueprintCallable,Category="Button|Enter")
	void OnEnterButton();
	UFUNCTION(BlueprintCallable,Category="Button|Close")
	void OnCloseButton();
};
