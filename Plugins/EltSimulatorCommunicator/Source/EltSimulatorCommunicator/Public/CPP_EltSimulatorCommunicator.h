#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EltSimulatorEnums.h"
#include "WebSocketServer/Public/WebSocketServer.h"
#include "CPP_EltSimulatorCommunicator.generated.h"

UCLASS()
class ELTSIMULATORCOMMUNICATOR_API ACPP_EltSimulatorCommunicator : public AActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	ACPP_EltSimulatorCommunicator();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly, Category = "ESC")
	UWebSocketServer* WebSocketServer;

	UPROPERTY(BlueprintReadOnly, Category = "ESC")
	FString LocalIP;

	UPROPERTY(EditAnywhere, Category = "ESC")
	bool IsDebugMode;

	UPROPERTY(EditAnywhere, Category = "ESC")
	EEltSimulatorScenarios EltSimulatorScenario;

	UPROPERTY(BlueprintReadOnly, Category = "ESC")
	EEltSimulatorCommandsCemaNo EltSimulatorCommandCemaNo;

	UPROPERTY(BlueprintReadOnly, Category = "ESC")
	EEltSimulatorCommandsCemaYes EltSimulatorCommandCemaYes;

	UPROPERTY(BlueprintReadWrite, Category = "ESC")
	int Port;

	UPROPERTY(BlueprintReadWrite, Category = "ESC")
	int ClientsCount;

	UFUNCTION(BlueprintCallable, Category = "ESC")
	void UpdateLocalIP();

	UFUNCTION(BlueprintCallable, Category = "ESC")
	EEltSimulatorCommandsCemaNo StringToEltSimulatorCommandCemaNo(FString NewCommand);

	UFUNCTION(BlueprintCallable, Category = "ESC")
	EEltSimulatorCommandsCemaYes StringToEltSimulatorCommandCemaYes(FString NewCommand);

	template<typename EnumType>
	UFUNCTION(BlueprintCallable, Category = "ESC")
	FString EnumToDisplayNameString(EnumType EnumValue);

	UFUNCTION(BlueprintCallable, Category = "ESC")
	void ParseCommand(FString NewCommand);

	//UFUNCTION(BlueprintCallable, Category = "ESC")
	//void StartNewServer();

	UFUNCTION(BlueprintCallable, Category = "ESC")
	void ServerOnListening(UWebSocketServer* NewSocketServer);

	UFUNCTION(BlueprintCallable, Category = "ESC")
	void ServerOnNewClient(UWebSocket* NewClient);

	UFUNCTION(BlueprintCallable, Category = "ESC")
	void ServerOnMessage(FString NewCommand, UWebSocket* NewClient, UPARAM(DisplayName = "Sequence index") int& SequenceIndex);

	UFUNCTION(BlueprintCallable, Category = "ESC")
	void ServerOnClientLeft(UWebSocket* NewClient);

	UFUNCTION(BlueprintCallable, Category = "ESC")
	void PrintLocalIP(float Duration);
};
