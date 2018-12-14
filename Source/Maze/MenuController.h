// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MenuController.generated.h"

/**
 * 
 */
UCLASS()
class MAZE_API AMenuController : public APlayerController
{
	GENERATED_BODY()
	
public:
	// Reference UMG Asset in the Editor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		TSubclassOf<class UUserWidget> wMainMenu;
	// Variable to hold the widget After Creating it.
	UUserWidget* MyMenu;
	// Override BeginPlay()
	virtual void BeginPlay() override;
	
	
};
