#pragma once

#include "EltSimulatorCommands.generated.h"

UENUM(BlueprintType, Category = "ESC")
enum class EEltSimulatorCommands : uint8
{
	START_SIMULATION = 0 UMETA(DisplayName = "Start simulation"),
	DRONE_ACTIVATE = 7 UMETA(DisplayName = "Drone activate"),
	DRONE_DEACTIVATE = 17 UMETA(DisplayName = "Drone deactivate"),
	SUBMARINE_ACTIVATE = 20 UMETA(DisplayName = "Submarine activate"),
	RADAR_ACTIVATE = 27 UMETA(DisplayName = "Radar activate"),
	INVALID_COMMAND = 255 UMETA(DisplayName = "Invalid command")
};