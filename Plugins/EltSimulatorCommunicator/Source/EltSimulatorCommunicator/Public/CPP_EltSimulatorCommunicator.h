#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EltSimulatorCommands.h"
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

	UPROPERTY(BlueprintReadOnly, Category="ESC")
	FString LocalIP;

	UPROPERTY(BlueprintReadOnly, Category = "ESC")
	EEltSimulatorCommands EltSimulatorCommand;

	UPROPERTY(BlueprintReadWrite, Category = "ESC")
	int Port;

	UPROPERTY(BlueprintReadWrite, Category = "ESC")
	int ClientsCount;

	UFUNCTION(BlueprintCallable, Category="ESC")
	void UpdateLocalIP();

	UFUNCTION(BlueprintCallable, Category = "ESC")
	EEltSimulatorCommands StringToEltSimulatorCommand(FString NewCommand);

	UFUNCTION(BlueprintCallable, Category = "ESC")
	FString EnumToDisplayNameString(EEltSimulatorCommands EnumValue);

	UFUNCTION(BlueprintCallable, Category = "ESC")
	EEltSimulatorCommands ParseCommand(FString NewCommand);

	//UFUNCTION(BlueprintCallable, Category = "ESC")
	//void StartNewServer();

	UFUNCTION(BlueprintCallable, Category = "ESC")
	void ServerOnListening(UWebSocketServer* NewSocketServer);

	UFUNCTION(BlueprintCallable, Category = "ESC")
	void ServerOnNewClient(UWebSocket* NewClient);

	UFUNCTION(BlueprintCallable, Category = "ESC")
	void ServerOnMessage(FString NewCommand, UWebSocket* NewClient);

	UFUNCTION(BlueprintCallable, Category = "ESC")
	void ServerOnClientLeft(UWebSocket* NewClient);

	UFUNCTION(BlueprintCallable, Category = "ESC")
	void PrintLocalIP(float Duration);
};
