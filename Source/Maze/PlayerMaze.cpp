// Fill out your copyright notice in the Description page of Project Settings.

/* For displaying a character by using the character class we dont need to create a skeletal mesh and assign it because 
the character class by default. The sketal mesh is a specific type of visible mesh that can be animated using the animation starter pack
the starter pack 

The linear algebra behind moving the character in a 3d space assings a either a +1 or -1 to a key press and when the player moves the character either foward the x value
of the foward vector is added to or subtracted from accordingly. Same with the left and right movements using the y axis. For the sprinting vs walking the speed at which a character moves
is controlled by vector multiplation of the directional vector and the rate of movement.*/

#include "PlayerMaze.h"
#include "Components/InputComponent.h" //aded so the InputComponent would work
#include "GameFramework/CharacterMovementComponent.h" //get character movement components
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"


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
	//get playercontroller
	MazeController = Cast<APlayerController>(GetController());
	MazeController->bShowMouseCursor = false;
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
	//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("pressed space")); //debug message
	TActorIterator<ACameraControl>CamAct(GetWorld()); //get an actor of the Scence Camera Controller
	//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Created Camera Controller reference")); //debug message
	CamAct->SwitchCam(GetWorld()->GetFirstPlayerController(), FollowCamera, this);
}

void APlayerMaze::AddPickup()
{
	//add one to the current pickups
	CurrentPickups = CurrentPickups + 1;
	
	//output current number of pickups
	//FString output = FString::FromInt(CurrentPickups);
	//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, output);

	if (CurrentPickups == TotalPickups)
	{
		DrawSuccess();
	}
}

void APlayerMaze::DrawSuccess()
{

	if (Success) // Check if the Asset is assigned in the blueprint.
	{
		// Create the widget using the current world and the overlay form the blueprint
		SuccessView = CreateWidget<UUserWidget>(GetWorld(), Success);

		//if the overlay creatation was successfull add the it to the view port
		if (SuccessView)
		{
			//let add it to the view port
			SuccessView->AddToViewport();
		}
		MazeController->bShowMouseCursor = true;
		
	}
}