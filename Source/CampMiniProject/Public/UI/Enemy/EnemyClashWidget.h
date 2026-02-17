#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnemyClashWidget.generated.h"

UCLASS()
class CAMPMINIPROJECT_API UEnemyClashWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void HideQ_Widet();
	void HideW_Widget();
	
	void ShowW_Widget();
	
protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UUserWidget> WBP_Clash_Q;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UUserWidget> WBP_Clash_W;
	
private:
	void CheckClashCompletion();
	
	bool bIsHideQ_Widget = false;
	bool bIsHideW_Widget = false;
};
