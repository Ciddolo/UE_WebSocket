#pragma once

#include "EltSimulatorEnums.generated.h"

UENUM(BlueprintType, Category = "ESC")
enum class EEltSimulatorScenarios : uint8
{
	CEMA_NO = 0 UMETA(DisplayName = "CEMA NO"),
	CEMA_YES = 1 UMETA(DisplayName = "CEMA YES"),
};

UENUM(BlueprintType, Category = "ESC")
enum class EEltSimulatorCommandsCemaNo : uint8
{
	ZERO_ENTRY = 0 UMETA(DisplayName = "CEMA_NO - 0 - Zero entry"),
	INITIAL_SEQUENCE = 1 UMETA(DisplayName = "CEMA_NO - 1 - Initial sequence"),
	START_SIMULATION = 7 UMETA(DisplayName = "CEMA_NO - 7 - Start simulation"),
	DRONE_ACTIVATE = 11 UMETA(DisplayName = "CEMA_NO - 11 - Drone activate"),
	DRONE_DEACTIVATE = 18 UMETA(DisplayName = "CEMA_NO - 18 - Drone deactivate"),
	NETWORK_SWITCH = 22 UMETA(DisplayName = "CEMA_NO - 22 - Network switch"),
	SUBMARINE_ACTIVATE = 25 UMETA(DisplayName = "CEMA_NO - 25 - Submarine activate"),
	CYBER_SOP = 28 UMETA(DisplayName = "CEMA_NO - 28 - Cyber sop"),
	RADAR_ACTIVATE = 30 UMETA(DisplayName = "CEMA_NO - 30 - Radar activate"),
	INVALID_COMMAND = 255 UMETA(DisplayName = "CEMA_NO - 255 - Invalid command")
};

UENUM(BlueprintType, Category = "ESC")
enum class EEltSimulatorCommandsCemaYes : uint8
{
	ZERO_ENTRY = 0 UMETA(DisplayName = "CEMA_YES - 0 - Zero entry"),
	INITIAL_SEQUENCE = 1 UMETA(DisplayName = "CEMA_YES - 1 - Initial sequence"),
	START_SIMULATION = 7 UMETA(DisplayName = "CEMA_YES - 7 - Start simulation"),
	DRONE_ACTIVATE = 11 UMETA(DisplayName = "CEMA_YES - 11 - Drone activate"),
	UNAUTHORIZED_COMMUNICATIONS = 18 UMETA(DisplayName = "CEMA_YES - 18 - Unauthorized communication"),
	DRONE_DEACTIVATE = 22 UMETA(DisplayName = "CEMA_YES - 22 - Drone deactivate"),
	NETWORK_SWITCH = 26 UMETA(DisplayName = "CEMA_YES - 26 - Network switch"),
	SUBMARINE_ACTIVATE = 29 UMETA(DisplayName = "CEMA_YES - 29 - Submarine activate"),
	CYBER_SOP = 32 UMETA(DisplayName = "CEMA_YES - 32 - Cyber sop"),
	RADAR_ACTIVATE = 36 UMETA(DisplayName = "CEMA_YES - 36 - Radar activate"),
	INVALID_COMMAND = 255 UMETA(DisplayName = "CEMA_YES - 255 - Invalid command")
};