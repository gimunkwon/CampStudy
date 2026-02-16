#include "UI/Object/Portal/PortalWidget.h"

#include "Kismet/GameplayStatics.h"

void UPortalWidget::OnEnterButton()
{
	if (Enter_Btn)
	{
		UE_LOG(LogTemp,Warning,TEXT("EnterButton ON"));
		
		if (KamenRaidLevelName.IsNone())
		{
			UE_LOG(LogTemp,Warning,TEXT("Level Name Is Not set"));
			return;
		}
		
		UGameplayStatics::OpenLevel(this, KamenRaidLevelName);
		RemoveFromParent();
	}
}

void UPortalWidget::OnCloseButton()
{
	if (Close_Btn)
	{
		RemoveFromParent();
	}
}
