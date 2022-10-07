// This project is entry for Games Job FairAutumn'22 UE SHMUMP challenge. Created by Jan Paraska

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "../Types.h"
#include "BCGameplayStatics.generated.h"

#pragma region Forward declarations
class ABusyChefGameModeBase;
#pragma endregion

/**
 * 
 */
UCLASS()
class BUSYCHEF_API UBCGameplayStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintPure, Category = "Gameplay static", meta = (WorldContext = "WorldContextObject"))
	static ABusyChefGameModeBase* GetBusyChefGameModeBase(const UObject* WorldContextObject);
};
