// Copyright Jako September 2017 

#include "Grabber.h"
#include"Engine/World.h"
#include"GameFramework/Actor.h"
#define OUT				//OUT does absolutely nothing here as Ben pointed out.The only thing it's here for is reminding us about the variables called by reference
FVector POV;
FRotator POVR;
FVector LineViewEnd;

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PhysicsHandle = nullptr;
	Pinput = nullptr;
}

void UGrabber::Grab()
{	
	FHitResult Hit = RayCast();
	auto GrabComponent = Hit.GetComponent();
	if (Hit.GetActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("HIT ACTOR: %s "), *(Hit.GetActor()->GetName()))
			PhysicsHandle->GrabComponentAtLocationWithRotation(GrabComponent, EName::NAME_None, Hit.GetActor()->GetActorLocation(),FRotator(0));
	}

}
FHitResult UGrabber::RayCast() const
{	

	UE_LOG(LogTemp, Warning, TEXT("YES! YOU ARE GRABBING SOMETHING!Jerking off maybe?:P"))
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT POV, OUT POVR);
	FVector PlayerGrabReach = POVR.Vector()*Reach;
	LineViewEnd = POV + PlayerGrabReach;
	FHitResult Hit;
	FCollisionQueryParams Pawn(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(Hit, POV, LineViewEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), Pawn);
	return Hit;
}
void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("KEY RELEASED!"));
	PhysicsHandle->ReleaseComponent();
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
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("NO INPUT COMPONENT FOUND *Insert sad smiley face*"))
	}
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT POV, OUT POVR);
	FVector PlayerGrabReach = POVR.Vector()*Reach;
	LineViewEnd = POV + PlayerGrabReach;
	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(LineViewEnd);
	}
}


