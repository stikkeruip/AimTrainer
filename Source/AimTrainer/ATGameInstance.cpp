// Fill out your copyright notice in the Description page of Project Settings.


#include "ATGameInstance.h"

#include "Blueprint/UserWidget.h"
#include "ATGameWidget.h"

void UATGameInstance::DisplayCountdown()
{
	if(!GameWidgetClass)
		return;

	for(FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; It++)
	{
		APlayerController* PC = It->Get();
		if(PC && PC->PlayerState && !MustSpectate(PC))
		{
			UATGameWidget* GameWidget = CreateWidget<UATGameWidget>(PC, GameWidgetClass);
			if(GameWidget)
			{
				GameWidget->AddToPlayerScreen();
				GameWidget->StartCountdown(WaitTime, this);
				GameWidgets.Add(PC, GameWidget);
			}
		}
	}
}
