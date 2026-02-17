#include "UI/Enemy/EnemyClashWidget.h"

#include "GameActor/Controller/BaseCharacterController.h"

void UEnemyClashWidget::HideQ_Widet()
{
	if (WBP_Clash_Q)
	{
		WBP_Clash_Q->SetVisibility(ESlateVisibility::Collapsed);
		bIsHideQ_Widget = true;
		CheckClashCompletion();
	}
}

void UEnemyClashWidget::HideW_Widget()
{
	if (WBP_Clash_W)
	{
		WBP_Clash_W->SetVisibility(ESlateVisibility::Collapsed);
		bIsHideW_Widget = true;
		CheckClashCompletion();
	}
}

void UEnemyClashWidget::CheckClashCompletion()
{
	if (bIsHideQ_Widget && bIsHideW_Widget)
	{
		if (auto* PC = Cast<ABaseCharacterController>(GetOwningPlayer()))
		{
			PC->ResumeEnemyAnimation();
		}
	}
}

