#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_EltSimulatorCommunicator.generated.h"

UCLASS()
class ELTSIMULATORCOMMUNICATOR_API ACPP_EltSimulatorCommunicator : public AActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	ACPP_EltSimulatorCommunicator();

	UPROPERTY(BlueprintReadOnly, Category="ESC")
	FString LocalIP;

	UPROPERTY(BlueprintReadWrite, Category = "ESC")
	int ClientsCount;

	UFUNCTION(BlueprintCallable, Category="ESC")
	void UpdateLocalIP();
};
