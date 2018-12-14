// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "MazeHUD.generated.h"

/**
 * 
 */
UCLASS()
class MAZE_API AMazeHUD : public AHUD
{
	GENERATED_BODY()

public:
	
	//set the umg asset in the editor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		TSubclassOf<UUserWidget> Overlay;
	// hold the widget after making it
	UUserWidget* HudOverlay;
	// Override BeginPlay()
	virtual void BeginPlay() override;

	
};
