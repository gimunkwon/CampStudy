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
	void OpenClashWidet();
	FORCEINLINE UUserWidget* GetClashWidget() const{return ClashWidget;}
	
protected:
#pragma region Widget
	UPROPERTY(EditAnywhere,Category="Widget|Clash")
	TSubclassOf<UUserWidget> ClashWidgetClass;
	UPROPERTY()
	TObjectPtr<UUserWidget> ClashWidget;
#pragma endregion
};
