// This project is entry for Games Job FairAutumn'22 UE SHMUMP challenge. Created by Jan Paraska

#include "WaveManager.h"

#include "SpawnerBase.h"
#include "../BusyChefGameModeBase.h"
#include "../Utilities/GameContextFunctionLibrary.h"

// Sets default values
AWaveManager::AWaveManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called every frame
void AWaveManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWaveManager::StartWave(const int Index) {
	if (WaveSpawner == nullptr)
		return;

	CurrentWave = Index >= Waves.Num() ? 0 : Index;
	
	const FWaveConfiguration Wave = Waves[CurrentWave];
	const int WaveScale = Wave.bCanBeScaled ? CompletedWaves / Waves.Num() : 0; // for each completed round, add extra enemies

	for (TPair<TSubclassOf<AActor>, int> Config : Wave.Enemies) {
		WaveSpawner->Spawn(Config.Key, Config.Value + WaveScale);
	}
}

void AWaveManager::FinishWave(const bool StartNext) {
	CompletedWaves++;

	if (StartNext) {
		int WaveToStart = CurrentWave + 1;

		if (DelayBetweenWaves > 0) {
			StartNextWaveDelegate.Unbind();
			StartNextWaveDelegate.BindUFunction(this, FName("StartWave"), WaveToStart);
			GetWorldTimerManager().SetTimer(StartNextWaveHandle, StartNextWaveDelegate, DelayBetweenWaves, false);
			OnWaveCompleted.Broadcast();
		}
		else {
			StartWave(WaveToStart);
		}
	}
}

// Called when the game starts or when spawned
void AWaveManager::BeginPlay()
{
	Super::BeginPlay();

	ABusyChefGameModeBase* GameMode = UGameContextFunctionLibrary::GetBusyChefGameModeBase(this);
	if (GameMode != nullptr) {
		if (!GameMode->SetWaveManager(this)) {
			Destroy(); // there should be only one wave manager in scene
			return;
		}

		GameMode->OnGameContextChanged.AddDynamic(this, &AWaveManager::OnGameContextChanged);
	}

	if (WaveSpawner != nullptr) {
		WaveSpawner->SetOwner(this);
	}
}

void AWaveManager::OnGameContextChanged(const EGameContext OldContext, const EGameContext NewContext) {
	switch (NewContext) {
	case EGameContext::Pause:
	{
		GetWorldTimerManager().PauseTimer(StartNextWaveHandle);
		break;
	}
	case EGameContext::Game:
	{
		if (OldContext == EGameContext::Pause) {
			GetWorldTimerManager().UnPauseTimer(StartNextWaveHandle);
		}
		else {
			StartNextWaveDelegate.Unbind();
			StartNextWaveDelegate.BindUFunction(this, FName("StartWave"), 0);
			GetWorldTimerManager().SetTimer(StartNextWaveHandle, StartNextWaveDelegate, DelayBetweenWaves, false);
			OnWaveCompleted.Broadcast();
		}
		break;
	}
	case EGameContext::GameOver:
	{
		GetWorldTimerManager().ClearTimer(StartNextWaveHandle);

		CurrentWave = 0;
		CompletedWaves = 0;
		break;
	}
	}
}
