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
	float Reach = 100.f; 
	UPhysicsHandleComponent* PhysicsHandle;
	UInputComponent* Pinput;	
	
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
	void Grab();						//reads the keys input and defines coe to pick up
	FHitResult RayCast() const;
	void Release();
};
