#include "UI/HUD/MiniHUD.h"

#include "Blueprint/UserWidget.h"
#include "GameActor/Character/Player/BaseCharacter.h"
#include "UI/NPC/Widget/NPCWidget.h"


void AMiniHUD::ShowNPCWidget()
{
	if (NPCWidgetClass)
	{
		NPCWidget = CreateWidget<UNPCWidget>(GetWorld(),NPCWidgetClass);
		NPCWidget->SetNPCText();
		NPCWidget->AddToViewport();
		
		if (ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(GetOwningPlayerController()->GetPawn()))
		{
			BaseCharacter->SetIsConnectedNPC(false);
		}
		
		
		FTimerHandle WidgetTimerHandle;
		
		GetWorld()->GetTimerManager().SetTimer(WidgetTimerHandle, [this]()
		{
			if (NPCWidget->IsInViewport()) NPCWidget->RemoveFromParent();
		},3.f, false);
	}
}
