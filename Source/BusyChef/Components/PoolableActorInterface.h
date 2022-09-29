// This project is entry for Games Job FairAutumn'22 UE SHMUMP challenge. Created by Jan Paraska

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PoolableActorInterface.generated.h"

UINTERFACE(MinimalAPI)
class UPoolableActorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for poolable actors
 */
class BUSYCHEF_API IPoolableActorInterface
{
	GENERATED_BODY()

public:

	/*
	* Called by pool when pooling actor
	*/
	virtual void ActivatePoolable() = 0;

	/*
	* Sets poolable actor transform
	*/
	virtual void SetTransform(const FTransform& Destination) = 0;

	/*
	* Called by pool when actor is returned to pool
	*/
	virtual void DeactivatePoolable() = 0;

	/*
	* Initiates returning to pool
	*/
	virtual void ReturnToPool() = 0;
};
