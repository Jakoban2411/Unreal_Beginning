// Copyright Jako September 2017 

#include "OpenDoor.h"
#include"GameFramework/Actor.h"
#include"Engine/World.h"
#include"Components/PrimitiveComponent.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UOpenDoor::OpenDoor()
{
	OpenDoorRequest.Broadcast();
}

void UOpenDoor::CloseDoor()
{
	GetOwner()->SetActorRotation(FRotator(0.f,90.f,0.f));
}

float UOpenDoor::GetTotalMass()
{	
	float Tmass = 0.f;
	//Array of Objects that are going to trigger the pressure plate
	TArray<AActor*> TrigObjs;
	if (PressurePlate==nullptr) { UE_LOG(LogTemp, Error, TEXT("Pressure Plate NOT FOUND FOR %s"), *GetOwner()->GetName());
	return Tmass;
	}
	PressurePlate->GetOverlappingActors(OUT TrigObjs);
	for (const auto* Obj : TrigObjs)
	{
		Tmass += Obj->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		float *TMass1 = &Tmass;
		UE_LOG(LogTemp, Warning, TEXT("%s Found Mass: %f"), *Obj->GetName(), *TMass1);
	}
	return Tmass;
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	

}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (GetTotalMass()>Masstrigger)
	{
		OpenDoor();
		Dooropentime = GetWorld()->TimeSeconds;
	}
	else
	{
		if (GetWorld()->TimeSince(Dooropentime) > Doorclosetime)
			CloseDoor();
	}
}

