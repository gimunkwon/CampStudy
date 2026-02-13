#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NPCWidget.generated.h"

class UTextBlock;

UCLASS()
class CAMPMINIPROJECT_API UNPCWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetNPCText();
	
protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> NPCText;
};
