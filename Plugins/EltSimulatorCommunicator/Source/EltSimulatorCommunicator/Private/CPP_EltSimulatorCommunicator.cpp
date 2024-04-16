#include "CPP_EltSimulatorCommunicator.h"
#include "SocketSubsystem.h"

#define Print(x) if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT(x)); }

ACPP_EltSimulatorCommunicator::ACPP_EltSimulatorCommunicator()
{
	PrimaryActorTick.bCanEverTick = true;

	LocalIP = TEXT("Unknown IP");

	EltSimulatorCommand = EEltSimulatorCommands::INVALID_COMMAND;

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

EEltSimulatorCommands ACPP_EltSimulatorCommunicator::StringToEltSimulatorCommand(FString NewCommand)
{
	if (NewCommand == "START_SIMULATION")
	{
		return EEltSimulatorCommands::START_SIMULATION;
	}
	else if (NewCommand == "DRONE_ACTIVATE")
	{
		return EEltSimulatorCommands::DRONE_ACTIVATE;
	}
	else if (NewCommand == "DRONE_DEACTIVATE")
	{
		return EEltSimulatorCommands::DRONE_DEACTIVATE;
	}
	else if (NewCommand == "SUBMARINE_ACTIVATE")
	{
		return EEltSimulatorCommands::SUBMARINE_ACTIVATE;
	}
	else if (NewCommand == "RADAR_ACTIVATE")
	{
		return EEltSimulatorCommands::RADAR_ACTIVATE;
	}
	else
	{
		return EEltSimulatorCommands::INVALID_COMMAND;
	}
}

FString ACPP_EltSimulatorCommunicator::EnumToDisplayNameString(EEltSimulatorCommands EnumValue)
{
	const UEnum* Enum = StaticEnum<EEltSimulatorCommands>();

	if (!Enum) return FString("Invalid");

	return Enum->GetDisplayNameTextByValue(static_cast<int64>(EnumValue)).ToString();
}

EEltSimulatorCommands ACPP_EltSimulatorCommunicator::ParseCommand(FString NewCommand)
{
	NewCommand.ReplaceInline(TEXT("{"), TEXT(""));
	NewCommand.ReplaceInline(TEXT("}"), TEXT(""));
	NewCommand.ReplaceInline(TEXT("\""), TEXT(""));

	TArray<FString> StringArray;

	NewCommand.ParseIntoArray(StringArray, TEXT(":"), true);

	if (StringArray.IsValidIndex(1))
	{
		EltSimulatorCommand = StringToEltSimulatorCommand(StringArray[1]);
	}
	else
	{
		EltSimulatorCommand = EEltSimulatorCommands::INVALID_COMMAND;
	}

	return EltSimulatorCommand;
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

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, Output);
}

void ACPP_EltSimulatorCommunicator::ServerOnNewClient(UWebSocket* NewClient)
{
	if (NewClient == nullptr) return;

	ClientsCount++;

	FString Output = "[" + NewClient->GetFName().ToString() + "] joined!";

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, Output);
}

void ACPP_EltSimulatorCommunicator::ServerOnMessage(FString NewCommand, UWebSocket* NewClient, int& SequenceIndex)
{
	if (NewClient == nullptr)
	{
		SequenceIndex = static_cast<int>(EEltSimulatorCommands::INVALID_COMMAND);

		return;
	}

	ParseCommand(NewCommand);

	SequenceIndex = static_cast<int>(EltSimulatorCommand);

	FString Output = "[" + NewClient->GetFName().ToString() + "] " + EnumToDisplayNameString(EltSimulatorCommand) + "\n[Sequence index] " + FString::FromInt(SequenceIndex);

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, Output);
}

void ACPP_EltSimulatorCommunicator::ServerOnClientLeft(UWebSocket* NewClient)
{
	if (NewClient == nullptr) return;

	FString Output = "[" + NewClient->GetFName().ToString() + "] left!";

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, Output);

	ClientsCount--;
}

void ACPP_EltSimulatorCommunicator::PrintLocalIP(float Duration)
{
	FString Output = "[Local IP] " + LocalIP + ":" + FString::FromInt(Port);

	GEngine->AddOnScreenDebugMessage(-1, Duration, FColor::Yellow, Output);
}
