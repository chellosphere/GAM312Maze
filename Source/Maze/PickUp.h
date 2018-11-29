// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Components/ShapeComponent.h"
#include "PickUp.generated.h"




UCLASS()
class MAZE_API APickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//root scene component to build everything else off of 
	UPROPERTY(EditAnywhere)
		USceneComponent* PickUpRoot;

	//the static mesh that can be changed in the editor
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* PickUpMesh;


	//the pick up box that is a box for now but can be changed in the editor
	UPROPERTY(EditAnywhere)
		UShapeComponent* PickUpBox;

	//if the pick up is one the player can distroy or not
	UPROPERTY(EditAnywhere)
		bool CanBeDistroyed = true;

	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
