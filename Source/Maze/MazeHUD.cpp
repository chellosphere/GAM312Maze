// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeHUD.h"



void AMazeHUD::BeginPlay()
{
	Super::BeginPlay();
	if (Overlay) // Check if the Asset is assigned in the blueprint.
	{
		// Create the widget using the current world and the overlay form the blueprint
		HudOverlay = CreateWidget<UUserWidget>(GetWorld(), Overlay);
		
		//if the overlay creatation was successfull add the it to the view port
		if (HudOverlay)
		{
			//let add it to the view port
			HudOverlay->AddToViewport();
		}
		
	}
}