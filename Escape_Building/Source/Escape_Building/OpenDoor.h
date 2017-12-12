// Copyright Jako September 2017 

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include"GameFramework/Actor.h"
#include"Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOpenRequest);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCloseRequest);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_BUILDING_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();
	float GetTotalMass();
	UPROPERTY(BlueprintAssignable)
		FOpenRequest OpenDoorRequest;
	UPROPERTY(BlueprintAssignable)
		FCloseRequest CloseDoorRequest;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate=nullptr;
	UPROPERTY(EditAnywhere)
		float Masstrigger=70.f;
	
};
