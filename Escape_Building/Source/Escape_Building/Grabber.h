// Copyright Jako September 2017 

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include"PhysicsEngine/PhysicsHandleComponent.h"
#include"Components/InputComponent.h"
#include "Grabber.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ESCAPE_BUILDING_API UGrabber : public UActorComponent
{
	GENERATED_BODY()
private:
	float Reach = 200.f;							//Defines Value for the hand length ie the maximum length Pawn can reach upto
	UPhysicsHandleComponent* PhysicsHandle=nullptr;			//Is set to the Physics Handle of the Pawn once Game starts
	UInputComponent* Pinput;						//Input Component of the pawn once the game starts
	
public:	
	// Sets default values for this component's properties
	UGrabber();	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void PhysicsComponentHandle();		//Finds Physics Handle and sets it to the data member PhysicsHandle
	void InputComponentHandle();		//Finds Input Component and sets it to the UInputComponent data member
	void Grab();						//reads the keys input and defines object to grab once key is pressed
	void POVSet();						//Sets the POV And POVR
	FHitResult RayCast() const;			//returns the Actor Hit
	void Release();						//Checks release of the key 
};