#include "UI/HUD/MiniHUD.h"

#include "Blueprint/UserWidget.h"


void AMiniHUD::OpenClashWidet()
{
	if (ClashWidgetClass)
	{
		ClashWidget = CreateWidget<UUserWidget>(GetWorld(),ClashWidgetClass);
		if (ClashWidget)
		{
			ClashWidget->AddToViewport();
		}
	}
}
