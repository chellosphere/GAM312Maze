// Fill out your copyright notice in the Description page of Project Settings.

/*For drawing and creating a HUD and other widgets they need to be created and then added to the view port. For HUD's this is often done at the start of the game or level
but I added the success screent that appears on a win condition. The HUD has access to variables that are blueprint viewable so that there is a visual indiatior of goals  and player statics

User interfaces are created in the blueprint editor and assinged to differen blueprints to load them as a part of beign play or another function*/

#include "MenuController.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"


void AMenuController::BeginPlay()
{
	Super::BeginPlay();
	if (wMainMenu) // Check if the Asset is assigned in the blueprint.
	{
		// Create the widget and store it.
		MyMenu = CreateWidget<UUserWidget>(this, wMainMenu);
		// now you can use the widget directly since you have a referance for it.
		// Extra check to make sure the pointer holds the widget.
		if (MyMenu)
		{
			//let add it to the view port
			MyMenu->AddToViewport();
		}
		//Show the Cursor.
		bShowMouseCursor = true;
	}
}
