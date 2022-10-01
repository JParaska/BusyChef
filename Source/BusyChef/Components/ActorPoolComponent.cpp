// This project is entry for Games Job FairAutumn'22 UE SHMUMP challenge. Created by Jan Paraska

#include "ActorPoolComponent.h"

#include "../BusyChefGameModeBase.h"
#include "../Utilities/GameContextFunctionLibrary.h"

// Sets default values for this component's properties
UActorPoolComponent::UActorPoolComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called every frame
void UActorPoolComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

IPoolableActorInterface* UActorPoolComponent::GetPoolableActor(const FTransform& Destination) {
	if (ActiveActors.Num() >= MaxActiveActors)
		return nullptr;

	IPoolableActorInterface* PooledActor;
	if (!ActorPool.Dequeue(PooledActor)) {
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = GetOwner();
		PooledActor = GetWorld()->SpawnActor<IPoolableActorInterface>(PoolableActorClass, Destination, SpawnParams);
	}
	else {
		PooledActor->SetTransform(Destination);
	}

	if (PooledActor != nullptr) {
		ActiveActors.Add(PooledActor);
		PooledActor->ActivatePoolable();
	}
	return PooledActor;
}

void UActorPoolComponent::ReturnPoolableActor(IPoolableActorInterface* PooledActor) {
	if (PooledActor == nullptr)
		return;

	if (ActiveActors.Contains(PooledActor)) {
		PooledActor->DeactivatePoolable();
		ActiveActors.Remove(PooledActor);
		ActorPool.Enqueue(PooledActor);
	}
}

void UActorPoolComponent::ReturnAll() {
	TArray<IPoolableActorInterface*> ActorsToReturn = ActiveActors.Array();
	for (IPoolableActorInterface* ActorToReturn : ActorsToReturn) {
		ReturnPoolableActor(ActorToReturn);
	}
}

int UActorPoolComponent::ActiveActorsCount() const {
	return ActiveActors.Num();
}

// Called when the game starts
void UActorPoolComponent::BeginPlay()
{
	Super::BeginPlay();

	ABusyChefGameModeBase* GameMode = UGameContextFunctionLibrary::GetBusyChefGameModeBase(this);
	if (GameMode != nullptr) {
		GameMode->OnGameContextChanged.AddDynamic(this, &UActorPoolComponent::OnGameContextChanged);
	}
}

void UActorPoolComponent::OnGameContextChanged(const EGameContext OldContext, const EGameContext NewContext) {
	if (NewContext == EGameContext::MainMenu || NewContext == EGameContext::Game) {
		ReturnAll();
	}
}
