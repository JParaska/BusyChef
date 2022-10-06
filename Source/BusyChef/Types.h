// This project is entry for Games Job FairAutumn'22 UE SHMUMP challenge. Created by Jan Paraska

#pragma once

// ----------------------------------------------------------------------------------------------------------------
// This header is for enums and structs used by classes and blueprints accross the game
// ----------------------------------------------------------------------------------------------------------------

#include "Types.generated.h"

#pragma region ForwardDeclarations
class AActor;
#pragma endregion ForwardDeclarations

#pragma region Enums
UENUM(BlueprintType)
enum class EGameContext : uint8 {
	None,
	MainMenu,
	CharacterSelection, // Skipped for now
	Game,
	GameWon,
	GameOver
};

UENUM(BlueprintType)
enum class EWeaponType : uint8 {
	StraightLine,
	Balistic,
	Static
};
#pragma endregion Enums

#pragma region Structs
USTRUCT(BlueprintType)
struct FWaveConfiguration {

	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	TMap<TSubclassOf<AActor>, int> Enemies;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	bool bCanBeScaled = true;
};
#pragma endregion Structs