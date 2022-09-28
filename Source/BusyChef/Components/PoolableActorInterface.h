// This project is entry for Games Job FairAutumn'22 UE SHMUMP challenge. Created by Jan Paraska

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PoolableActorInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPoolableActorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BUSYCHEF_API IPoolableActorInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void ActivatePoolable() = 0;

	virtual void SetTransform(const FTransform& Destination) = 0;

	virtual void DeactivatePoolable() = 0;

	virtual void ReturnToPool() = 0;
};
