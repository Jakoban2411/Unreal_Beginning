// Copyright Jako September 2017 

#include "Grabber.h"
#include"Engine/World.h"
#include"GameFramework/Actor.h"

#define OUT				//OUT does absolutely nothing here as Ben pointed out.The only thing it's here for is reminding us about the variables called by reference

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Warning,TEXT("ITS ON LIKE THE FOURTH OF JULY ON"));
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FVector POV;
	FRotator POVR;
	// ...
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT POV,OUT POVR);		//OUT here just shows that POV and POVR ae going to be changed ffrom within the function
	UE_LOG(LogTemp, Warning, TEXT("Stupid Pawn looking at:%s from %s"), *POVR.ToString(), *POV.ToString());
}

