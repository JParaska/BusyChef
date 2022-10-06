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
			GetWorldTimerManager().SetTimer(StartNextWaveHandle, StartNextWaveDelegate, DelayBetweenWaves, false);
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

	if (WaveSpawner != nullptr) {
		WaveSpawner->SetOwner(this);
	}

	ABusyChefGameModeBase* GameMode = UGameContextFunctionLibrary::GetBusyChefGameModeBase(this);
	if (GameMode != nullptr) {
		GameMode->OnGameContextChanged.AddDynamic(this, &AWaveManager::OnGameContextChanged);
	}
}

void AWaveManager::OnGameContextChanged(const EGameContext OldContext, const EGameContext NewContext) {
	if (NewContext == EGameContext::Game) { // && OldContext != EGameContext::Pause) {
		StartNextWaveDelegate.Unbind();
		StartNextWaveDelegate.BindUFunction(this, FName("StartWave"), 0);
		GetWorldTimerManager().SetTimer(StartNextWaveHandle, StartNextWaveDelegate, InitialDelay, false);
	}
	else if (NewContext == EGameContext::GameOver) {
		GetWorldTimerManager().ClearTimer(StartNextWaveHandle);

		CurrentWave = 0;
		CompletedWaves = 0;
	}
}
