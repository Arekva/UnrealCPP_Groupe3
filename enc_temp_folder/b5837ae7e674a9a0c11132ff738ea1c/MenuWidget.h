// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Engine/Level.h"

#include "MenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class GC_UE4CPP_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		ULevel* Level;

	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* StartButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* QuitButton;

private:
	UFUNCTION()
	void OnMenuClick();
	UFUNCTION()
	void OnQuitClick();
};
