#include "CPP_EltSimulatorCommunicator.h"
#include "SocketSubsystem.h"

#define Print(x) if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT(x)); }

ACPP_EltSimulatorCommunicator::ACPP_EltSimulatorCommunicator()
{
	PrimaryActorTick.bCanEverTick = true;

	LocalIP = TEXT("Unknown IP");

	IsDebugMode = false;

	EltSimulatorCommandCemaNo = EEltSimulatorCommandsCemaNo::INVALID_COMMAND;
	EltSimulatorCommandCemaYes = EEltSimulatorCommandsCemaYes::INVALID_COMMAND;

	Port = 8080;

	ClientsCount = 0;
}

void ACPP_EltSimulatorCommunicator::BeginPlay()
{
	Super::BeginPlay();

	UpdateLocalIP();

	// StartNewServer();
}

void ACPP_EltSimulatorCommunicator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ClientsCount <= 0)
	{
		PrintLocalIP(0.0f);
	}
}

void ACPP_EltSimulatorCommunicator::UpdateLocalIP()
{
	bool CanBindAll = false;

	TSharedPtr<FInternetAddr> LocalInfo = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->GetLocalHostAddr(*GLog, CanBindAll);

	if (LocalInfo.IsValid())
	{
		LocalIP = LocalInfo->ToString(false);
	}
	else
	{
		LocalIP = TEXT("Unknown IP");
	}
}

EEltSimulatorCommandsCemaNo ACPP_EltSimulatorCommunicator::StringToEltSimulatorCommandCemaNo(FString NewCommand)
{
	if (NewCommand == "INITIAL_SEQUENCE")
	{
		return EEltSimulatorCommandsCemaNo::INITIAL_SEQUENCE;
	}
	else if (NewCommand == "START_SIMULATION")
	{
		return EEltSimulatorCommandsCemaNo::START_SIMULATION;
	}
	else if (NewCommand == "DRONE_ACTIVATE")
	{
		return EEltSimulatorCommandsCemaNo::DRONE_ACTIVATE;
	}
	else if (NewCommand == "DRONE_DEACTIVATE")
	{
		return EEltSimulatorCommandsCemaNo::DRONE_DEACTIVATE;
	}
	else if (NewCommand == "NETWORK_SWITCH")
	{
		return EEltSimulatorCommandsCemaNo::NETWORK_SWITCH;
	}
	else if (NewCommand == "SUBMARINE_ACTIVATE")
	{
		return EEltSimulatorCommandsCemaNo::SUBMARINE_ACTIVATE;
	}
	else if (NewCommand == "CYBER_SOP")
	{
		return EEltSimulatorCommandsCemaNo::CYBER_SOP;
	}
	else if (NewCommand == "RADAR_ACTIVATE")
	{
		return EEltSimulatorCommandsCemaNo::RADAR_ACTIVATE;
	}
	else
	{
		return EEltSimulatorCommandsCemaNo::INVALID_COMMAND;
	}
}

EEltSimulatorCommandsCemaYes ACPP_EltSimulatorCommunicator::StringToEltSimulatorCommandCemaYes(FString NewCommand)
{
	if (NewCommand == "INITIAL_SEQUENCE")
	{
		return EEltSimulatorCommandsCemaYes::INITIAL_SEQUENCE;
	}
	else if (NewCommand == "START_SIMULATION")
	{
		return EEltSimulatorCommandsCemaYes::START_SIMULATION;
	}
	else if (NewCommand == "DRONE_ACTIVATE")
	{
		return EEltSimulatorCommandsCemaYes::DRONE_ACTIVATE;
	}
	else if (NewCommand == "UNAUTHORIZED_COMMUNICATIONS")
	{
		return EEltSimulatorCommandsCemaYes::UNAUTHORIZED_COMMUNICATIONS;
	}
	else if (NewCommand == "DRONE_DEACTIVATE")
	{
		return EEltSimulatorCommandsCemaYes::DRONE_DEACTIVATE;
	}
	else if (NewCommand == "NETWORK_SWITCH")
	{
		return EEltSimulatorCommandsCemaYes::NETWORK_SWITCH;
	}
	else if (NewCommand == "SUBMARINE_ACTIVATE")
	{
		return EEltSimulatorCommandsCemaYes::SUBMARINE_ACTIVATE;
	}
	else if (NewCommand == "CYBER_SOP")
	{
		return EEltSimulatorCommandsCemaYes::CYBER_SOP;
	}
	else if (NewCommand == "RADAR_ACTIVATE")
	{
		return EEltSimulatorCommandsCemaYes::RADAR_ACTIVATE;
	}
	else
	{
		return EEltSimulatorCommandsCemaYes::INVALID_COMMAND;
	}
}

template<typename EnumType>
FString ACPP_EltSimulatorCommunicator::EnumToDisplayNameString(EnumType EnumValue)
{
	const UEnum* Enum = StaticEnum<EnumType>();

	if (!Enum) return FString("Invalid");

	return Enum->GetDisplayNameTextByValue(static_cast<int64>(EnumValue)).ToString();
}

void ACPP_EltSimulatorCommunicator::ParseCommand(FString NewCommand)
{
	NewCommand.ReplaceInline(TEXT("{"), TEXT(""));
	NewCommand.ReplaceInline(TEXT("}"), TEXT(""));
	NewCommand.ReplaceInline(TEXT("\""), TEXT(""));

	TArray<FString> StringArray;

	NewCommand.ParseIntoArray(StringArray, TEXT(":"), true);

	if (EltSimulatorScenario == EEltSimulatorScenarios::CEMA_NO)
	{
		if (StringArray.IsValidIndex(1))
		{
			EltSimulatorCommandCemaNo = StringToEltSimulatorCommandCemaNo(StringArray[1]);
		}
		else
		{
			EltSimulatorCommandCemaNo = EEltSimulatorCommandsCemaNo::INVALID_COMMAND;
		}
	}
	else if (EltSimulatorScenario == EEltSimulatorScenarios::CEMA_YES)
	{
		if (StringArray.IsValidIndex(1))
		{
			EltSimulatorCommandCemaYes = StringToEltSimulatorCommandCemaYes(StringArray[1]);
		}
		else
		{
			EltSimulatorCommandCemaYes = EEltSimulatorCommandsCemaYes::INVALID_COMMAND;
		}
	}
}

//void ACPP_EltSimulatorCommunicator::StartNewServer()
//{
//	WebSocketServer = UWebSocketServer::CreateWebSocketServer();
//
//	if (WebSocketServer == nullptr) return;
//}

void ACPP_EltSimulatorCommunicator::ServerOnListening(UWebSocketServer* NewSocketServer)
{
	WebSocketServer = NewSocketServer;

	if (WebSocketServer == nullptr) return;

	FString Output = WebSocketServer->GetFName().ToString() + " is listening!";

	if (IsDebugMode)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, Output);
	}
}

void ACPP_EltSimulatorCommunicator::ServerOnNewClient(UWebSocket* NewClient)
{
	if (NewClient == nullptr) return;

	ClientsCount++;

	FString Output = "[" + NewClient->GetFName().ToString() + "] joined!";

	if (IsDebugMode)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, Output);
	}
}

void ACPP_EltSimulatorCommunicator::ServerOnMessage(FString NewCommand, UWebSocket* NewClient, int& SequenceIndex)
{
	if (NewClient == nullptr)
	{
		if (EltSimulatorScenario == EEltSimulatorScenarios::CEMA_NO)
		{
			SequenceIndex = static_cast<int>(EEltSimulatorCommandsCemaNo::INVALID_COMMAND);
		}
		else if (EltSimulatorScenario == EEltSimulatorScenarios::CEMA_YES)
		{
			SequenceIndex = static_cast<int>(EEltSimulatorCommandsCemaYes::INVALID_COMMAND);
		}

		return;
	}

	ParseCommand(NewCommand);

	FString Output = "";

	if (EltSimulatorScenario == EEltSimulatorScenarios::CEMA_NO)
	{
		SequenceIndex = static_cast<int>(EltSimulatorCommandCemaNo);

		Output = "[" + NewClient->GetFName().ToString() + "] " + EnumToDisplayNameString(EltSimulatorCommandCemaNo) + "\n[Sequence index] " + FString::FromInt(SequenceIndex);
	}
	else if (EltSimulatorScenario == EEltSimulatorScenarios::CEMA_YES)
	{
		SequenceIndex = static_cast<int>(EltSimulatorCommandCemaYes);

		Output = "[" + NewClient->GetFName().ToString() + "] " + EnumToDisplayNameString(EltSimulatorCommandCemaYes) + "\n[Sequence index] " + FString::FromInt(SequenceIndex);
	}

	if (IsDebugMode)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, Output);
	}
}

void ACPP_EltSimulatorCommunicator::ServerOnClientLeft(UWebSocket* NewClient)
{
	if (NewClient == nullptr) return;

	FString Output = "[" + NewClient->GetFName().ToString() + "] left!";

	if (IsDebugMode)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, Output);
	}

	ClientsCount--;
}

void ACPP_EltSimulatorCommunicator::PrintLocalIP(float Duration)
{
	FString Output = "[Local IP] " + LocalIP + ":" + FString::FromInt(Port);

	GEngine->AddOnScreenDebugMessage(-1, Duration, FColor::Yellow, Output);
}
