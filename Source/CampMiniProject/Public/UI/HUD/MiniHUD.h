#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MiniHUD.generated.h"


class UNPCWidget;

UCLASS()
class CAMPMINIPROJECT_API AMiniHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	void ShowNPCWidget();
	
protected:
	UPROPERTY(EditAnywhere,Category="Widget|NPC")
	TSubclassOf<UUserWidget> NPCWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UNPCWidget> NPCWidget;
};
