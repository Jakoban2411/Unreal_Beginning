// Copyright Jako September 2017 

#include "Grabber.h"
#include"Engine/World.h"
#include"GameFramework/Actor.h"
#define OUT				//OUT does absolutely nothing here as Ben pointed out.The only thing it's here for is reminding us about the variables called by reference
FVector POV;			//Location of the Pawn	 
FRotator POVR;			//Direction of the Pawn
FVector LineViewEnd;	//Decides the grab end of the Pawn 

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PhysicsHandle = nullptr;
	Pinput = nullptr;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	PhysicsComponentHandle();
	InputComponentHandle();
}


void UGrabber::PhysicsComponentHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();		//Look for attached Physics handler in Runtime
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("%s is missing a physics handle component!"), *(GetOwner()->GetName()))
			return;
	}
}
void UGrabber::InputComponentHandle()
{

	Pinput = GetOwner()->FindComponentByClass<UInputComponent>();						//Look for Input component generated in Runtime
	if (Pinput)
	{
		UE_LOG(LogTemp, Error, TEXT("Input Component Found"))
		Pinput->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		Pinput->BindAction("Grab", IE_Released, this, &UGrabber::Release);
		Pinput->BindAction("Throw", IE_Pressed, this, &UGrabber::Throw);
		Pinput->BindAction("Throw", IE_Released, this, &UGrabber::TRelease);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("NO INPUT COMPONENT FOUND *Insert sad smiley face*"))
			return;
	}
}

FHitResult UGrabber::RayCast() const
{

	FHitResult Hit;
	FCollisionQueryParams Pawn(FName(TEXT("")), false, GetOwner());			//Creates a Trace Channel For Pawn i.e GetOwner
	GetWorld()->LineTraceSingleByObjectType(OUT Hit, POV, LineViewEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), Pawn);		//Raycast 
	return Hit;
}
void UGrabber::Grab()
{
	FHitResult Hit = RayCast();						//Hit is set to the object if hit
	GrabbedComponent = Hit.GetComponent();
	if (Hit.GetActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("HIT ACTOR: %s "), *(Hit.GetActor()->GetName()))
		if (!PhysicsHandle) 
		{ 
		UE_LOG(LogTemp, Error, TEXT("PHYSICS HANDLE NOT FOUND FOR %s"), *GetOwner()->GetName());
		return;
		}
		PhysicsHandle->GrabComponentAtLocationWithRotation(GrabbedComponent, EName::NAME_None, Hit.GetActor()->GetActorLocation(), FRotator(0));		//Component to be grabbed is picked up
	}

}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("KEY RELEASED!"));
	if (!PhysicsHandle) 
	{
		UE_LOG(LogTemp, Error, TEXT("PHYSICS HANDLE NOT FOUND FOR %s"), *GetOwner()->GetName());
		return;
	}
	PhysicsHandle->ReleaseComponent();					
}

void UGrabber::Throw()
{
	FHitResult Hit = RayCast();
	if (Hit.GetActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("GOT IT?"));
		PhysicsHandle->GrabComponentAtLocationWithRotation(Hit.GetComponent(), EName::NAME_None, Hit.GetActor()->GetActorLocation(), FRotator(0));		//Component to be grabbed is picked up
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Not an actor!"));
		return;
	}

}

void UGrabber::TRelease()
{

	GrabbedComponent = PhysicsHandle->GetGrabbedComponent();
	if(!PhysicsHandle->GrabbedComponent)
	{
		return;
	}
	TReq.Broadcast();

}


void UGrabber::POVSet()
{
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT POV, OUT POVR);
	FVector PlayerGrabReach = POVR.Vector()*Reach;
	LineViewEnd = POV + PlayerGrabReach;
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{	

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	POVSet();
	if (!PhysicsHandle) 
	{
		UE_LOG(LogTemp, Error, TEXT("PHYSICS HANDLE NOT FOUND FOR %s"), *GetOwner()->GetName());
		return;
	}
	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(LineViewEnd);
	}
}


