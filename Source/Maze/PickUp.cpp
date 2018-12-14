// Fill out your copyright notice in the Description page of Project Settings.

/* For collison dection there are collsion dection volumes on nearly all objects in the game to deterine how the interaction with another object should be handled. Making the area of 
dection for an object like a simple rectangle the same as the obejct is easy but to make a detection that follows the exact lines of the player character it would be too complex to use realistically
in a game. For the player character and the pickups they have collision volumes that surround they and are enabled to decect when another object overlaps them. 

These overlap events can by cast to see what it was that overlapped them and determine game logic based on that. See below where the pick ups are only distroyed if the player character overlaps them

For object like walls and floors the mesh that determins what they look like is not set to control if it can be walked through. the added collison mesh that is set to block all is what controlls the
physics of if the player character can walk through it.*/

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

	//create audio subobject
	PickUpCue = CreateDefaultSubobject<UAudioComponent>(TEXT("AUDIO"));

	//if the audio cue exists
	if(PickUpCue)
	{
		PickUpCue->bAutoActivate = false; //sound doesent play on start up
		PickUpCue->bStopWhenOwnerDestroyed = false; //cue will keep playing after object is distroyed
	}
	
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
	APlayerMaze* Player = Cast<APlayerMaze>(OtherActor);
	if (Player)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Red, TEXT("Cast worked")); //display a message that they have picked it up
		if (CanBeDistroyed)
		{
			//make sure the sound cue is actually set
			if (PickUpCue)
			{	
				PickUpCue->Activate(true); //activate it
				PickUpCue->Play(0.0f); //play the cue
			}

			Destroy();
			//GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Red, TEXT("You Got Me!")); //display a message that they have picked it up
			
			//increment how many pickups the player has
			Player->AddPickup();

		}
	}
}

