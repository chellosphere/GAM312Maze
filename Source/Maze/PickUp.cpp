// Fill out your copyright notice in the Description page of Project Settings.

#include "PickUp.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "Runtime/CoreUObject/Public/UObject/UObjectGlobals.h"
#include "Runtime/Engine/Public/Engine.h"



// Sets default values
APickUp::APickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//root scene component
	PickUpRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	//static mesh component - not set to any shape yet
	PickUpMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pick Up Mesh"));

	//the root component of the actor set to the PickUpRoot
	RootComponent = PickUpRoot; 

	//attatch to the root object but ignor scale so the tranformation doesn't change the size of the object
	PickUpMesh->AttachToComponent(PickUpRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	//the box that surrounds the skeletal mesh indicating where the collisions are
	PickUpBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Pick Up Box")); 
	PickUpBox->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));  //make the box one by one by one

	//allows the box to generate overlap events otherwise the box will fuction as a collision sensor
	PickUpBox->bGenerateOverlapEvents = true;

	//attach to the root object but ignore scale so the tranformation doesn't change the size of the object
	PickUpBox->AttachToComponent(PickUpRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale); 
}

// Called when the game starts or when spawned
void APickUp::BeginPlay()
{
	Super::BeginPlay();
	PickUpBox->OnComponentBeginOverlap.AddDynamic(this, &APickUp::BeginOverlap); //when being play starts begin checking for overlap events

	
}

// Called every frame
void APickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickUp::BeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//if the object can be distroyed - this variable can be set for each blueprint
	if (CanBeDistroyed)
	{
		Destroy();
		GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Red, TEXT("You Got Me!")); //display a message that they have picked it up
	}

}

