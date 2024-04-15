#pragma once

#include "EltSimulatorCommands.generated.h"

UENUM(BlueprintType, Category = "ESC")
enum class EEltSimulatorCommands : uint8
{
	NONE UMETA(DisplayName = "None"),
	START_SIMULATION UMETA(DisplayName = "Start simulation"),
	DRONE_ACTIVATE UMETA(DisplayName = "Drone activate"),
	DRONE_DEACTIVATE UMETA(DisplayName = "Drone deactivate"),
	SUBMARINE_ACTIVATE UMETA(DisplayName = "Submarine activate"),
	RADAR_ACTIVATE UMETA(DisplayName = "Radar activate")
};