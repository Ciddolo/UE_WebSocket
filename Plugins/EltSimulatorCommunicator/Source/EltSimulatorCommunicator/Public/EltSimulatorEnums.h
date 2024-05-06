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
	ZERO_ENTRY = 0 UMETA(DisplayName = "CEMA_NO - Zero entry"),
	INITIAL_SEQUENCE = 1 UMETA(DisplayName = "CEMA_NO - Initial sequence"),
	START_SIMULATION = 6 UMETA(DisplayName = "CEMA_NO - Start simulation"),
	DRONE_ACTIVATE = 10 UMETA(DisplayName = "CEMA_NO - Drone activate"),
	UNAUTHORIZED_COMMUNICATIONS = 17 UMETA(DisplayName = "CEMA_NO - Unauthorized communication"),
	DRONE_DEACTIVATE = 22 UMETA(DisplayName = "CEMA_NO - Drone deactivate"),
	NETWORK_SWITCH = 25 UMETA(DisplayName = "CEMA_NO - Network switch"),
	SUBMARINE_ACTIVATE = 28 UMETA(DisplayName = "CEMA_NO - Submarine activate"),
	CYBER_SOP = 32 UMETA(DisplayName = "CEMA_NO - Cyber sop"),
	RADAR_ACTIVATE = 37 UMETA(DisplayName = "CEMA_NO - Radar activate"),
	INVALID_COMMAND = 255 UMETA(DisplayName = "CEMA_NO - Invalid command")
};

UENUM(BlueprintType, Category = "ESC")
enum class EEltSimulatorCommandsCemaYes : uint8
{
	ZERO_ENTRY = 0 UMETA(DisplayName = "CEMA_YES - Zero entry"),
	INITIAL_SEQUENCE = 1 UMETA(DisplayName = "CEMA_YES - Initial sequence"),
	START_SIMULATION = 6 UMETA(DisplayName = "CEMA_YES - Start simulation"),
	DRONE_ACTIVATE = 10 UMETA(DisplayName = "CEMA_YES - Drone activate"),
	UNAUTHORIZED_COMMUNICATIONS = 17 UMETA(DisplayName = "CEMA_YES - Unauthorized communication"),
	DRONE_DEACTIVATE = 22 UMETA(DisplayName = "CEMA_YES - Drone deactivate"),
	NETWORK_SWITCH = 25 UMETA(DisplayName = "CEMA_YES - Network switch"),
	SUBMARINE_ACTIVATE = 28 UMETA(DisplayName = "CEMA_YES - Submarine activate"),
	CYBER_SOP = 32 UMETA(DisplayName = "CEMA_YES - Cyber sop"),
	RADAR_ACTIVATE = 37 UMETA(DisplayName = "CEMA_YES - Radar activate"),
	INVALID_COMMAND = 255 UMETA(DisplayName = "CEMA_YES - Invalid command")
};