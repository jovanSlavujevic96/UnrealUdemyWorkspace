// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldPosition.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UWorldPosition::UWorldPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();

	const auto& actorRef = GetOwner();
	UE_LOG(LogTemp, Warning, TEXT("Object's name: %s"), *actorRef->GetName() );

	const auto& ObjectPosition = actorRef->GetActorLocation();
	UE_LOG(LogTemp, Warning, TEXT("Object's location:(x,y,z,)<=>(%.3f,%.3f,%.3f)"), ObjectPosition.X, ObjectPosition.Y, ObjectPosition.Z  );
	UE_LOG(LogTemp, Warning, TEXT("Object's location str: %s"), *ObjectPosition.ToString() );

}


// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

