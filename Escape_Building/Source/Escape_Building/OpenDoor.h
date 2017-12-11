// Copyright Jako September 2017 

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include"GameFramework/Actor.h"
#include"Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOpenRequest);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_BUILDING_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();
	void OpenDoor();
	void CloseDoor();
	float GetTotalMass();
	UPROPERTY(BlueprintAssignable)
		FOpenRequest OpenDoorRequest;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	UPROPERTY(EditAnywhere)
		float Openby = 90.f;
	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate=nullptr;
	UPROPERTY(EditAnywhere)
		float Masstrigger=70.f;
	float Dooropentime;
	UPROPERTY(EditAnywhere)
		float Doorclosetime = 1.f;
};
