// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"

#include "Components/Button.h"

void UMenuWidget::OnMenuClick()
{
	
}
void UMenuWidget::OnQuitClick()
{
	FGenericPlatformMisc::RequestExit(false);
}

void UMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// ItemTitle can be nullptr if we haven't created it in the
	// Blueprint subclass
	/*if (ItemTitle)
	{
		ItemTitle->SetText(FText::FromString(TEXT("Hello world!")));
	}*/

	StartButton->OnClicked.AddDynamic(this, &UMenuWidget::OnMenuClick);
	QuitButton->OnClicked.AddDynamic(this, &UMenuWidget::OnQuitClick);
}

