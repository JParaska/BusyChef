// This project is entry for Games Job FairAutumn'22 UE SHMUMP challenge. Created by Jan Paraska

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Types.h"
#include "WaveManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWaveCompleted);

#pragma region Forward declarations
class ASpawnerBase;
#pragma endregion

UCLASS()
class BUSYCHEF_API AWaveManager : public AActor
{
	GENERATED_BODY()

#pragma region Properties
private:

	int CurrentWave = -1;

	int CompletedWaves = 0;

	FTimerDelegate StartNextWaveDelegate;
	FTimerHandle StartNextWaveHandle;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave", meta = (AllowPrivateAccess = "true"))
	float DelayBetweenWaves = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave", meta = (AllowPrivateAccess = "true"))
	float InitialDelay = 15.0f;

	/*
	* 0 - Default wave
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave", meta = (AllowPrivateAccess = "true"))
	TArray<FWaveConfiguration> Waves;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ASpawnerBase> WaveSpawner;

public:

	UPROPERTY(BlueprintAssignable)
	FOnWaveCompleted OnWaveCompleted;
#pragma endregion
	
#pragma region Methods
public:	
	// Sets default values for this actor's properties
	AWaveManager();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Wave")
	void StartWave(const int Index);

	void FinishWave(const bool StartNext);

	UFUNCTION(BlueprintPure)
	int GetWavesCompleted() const { return CompletedWaves; }

	UFUNCTION(BlueprintPure)
	int GetCurrentWave() const { return CurrentWave; }

	UFUNCTION(BlueprintPure)
	float GetDelayBetweenWaves() const { return DelayBetweenWaves; }

	UFUNCTION(BlueprintPure)
	float GetInitialDelay() const { return InitialDelay; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UFUNCTION()
	void OnGameContextChanged(const EGameContext OldContext, const EGameContext NewContext);
#pragma endregion
};
