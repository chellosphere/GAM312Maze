// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerMaze.h"
#include "Components/InputComponent.h" //aded so the InputComponent would work
#include "GameFramework/CharacterMovementComponent.h" //get character movement components


// Sets default values
APlayerMaze::APlayerMaze()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	

	//set up spring arm component - values can be changed in the editor
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 150.0f;
	SpringArm->SocketOffset=FVector(0.0f, 0.f, 50.0f); //these values where changed in the editor to place the camera better
	SpringArm->RelativeRotation = FRotator(0.f, -20.0f, 0.f); //these where changed in the editor to place the camera better


	//set up follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera-> SetupAttachment(SpringArm, USpringArmComponent::SocketName);


	

	//do not move the pawn with the controller rotataions
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;



	//set the max walking speed to the custom walking speed
	GetCharacterMovement()->MaxWalkSpeed = WalkS;

}

// Called when the game starts or when spawned
void APlayerMaze::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerMaze::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerMaze::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	check(InputComponent);
	InputComponent->BindAxis("Foward", this, &APlayerMaze::Lateral); //bind the foward and back controls to the player character
	InputComponent->BindAxis("Right", this, &APlayerMaze::SidetoSide); //binds the side to side controls for the chacters
	InputComponent->BindAxis("MousePitch", this, &APlayerMaze::LookUp);//turn the camera
    InputComponent->BindAxis("MouseYaw", this, &APlayerMaze::LookRight);//turn the camera

	InputComponent->BindAction("Sprint", IE_Pressed, this, &APlayerMaze::StartSprint); //bind pressing the key to start sprint
	InputComponent->BindAction("Sprint", IE_Released, this, &APlayerMaze::EndSprint); //bind pressing the key to end sprint
	InputComponent->BindAction("SwitchCam", IE_Released, this, &APlayerMaze::SwitchCams); //bind pressing the key to end sprint
}

void APlayerMaze::LookUp(float value)
{
	//look up by taking the pitch input valuse and multiple it by the time the and turn rate
	AddControllerPitchInput(value*BaseLookUpRate*GetWorld()->GetDeltaSeconds());
}

void APlayerMaze::LookRight(float value)
{
	//look left or right by getting the turn rate and multiplying it by the time and turn rate
	AddControllerYawInput(value*BaseTurnRate*GetWorld()->GetDeltaSeconds());
}

//move forward/backward by getting the current foward movement vector and adding the key value
void APlayerMaze::Lateral(float Value)
{
	if (Controller&&Value)
	{
		FVector Foward = GetActorForwardVector();
		AddMovementInput(Foward, Value);
	}
}

//move side to side by adding the value of the key press to the current right movement vector
void APlayerMaze::SidetoSide(float Value)
{
	if (Controller&&Value)
	{
		FVector Right = GetActorRightVector();
		AddMovementInput(Right, Value);
	}
}

//start springting

void APlayerMaze::StartSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = SprintS; //set the max walking speed to the sprint speed
}


//end springintg
void APlayerMaze::EndSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkS;
}

//switch cameras
void APlayerMaze::SwitchCams()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("pressed space")); //debug message
	TActorIterator<ACameraControl>CamAct(GetWorld()); //get an actor of the Scence Camera Controller
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Created Camera Controller reference")); //debug message
	CamAct->SwitchCam(GetWorld()->GetFirstPlayerController(), FollowCamera, this);
}