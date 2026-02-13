#include "UI/NPC/Widget/NPCWidget.h"

#include "Components/TextBlock.h"

void UNPCWidget::SetNPCText()
{
	if (NPCText)
	{
		NPCText->SetText(FText::FromString(FString::Printf(TEXT("내가 던전 문을 열어 주도록 하지"))));
	}
}
