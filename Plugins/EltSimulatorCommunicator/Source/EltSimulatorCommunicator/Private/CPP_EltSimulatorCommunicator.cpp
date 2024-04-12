#include "CPP_EltSimulatorCommunicator.h"
#include "SocketSubsystem.h"

ACPP_EltSimulatorCommunicator::ACPP_EltSimulatorCommunicator()
{
	LocalIP = TEXT("Unknown IP");

	ClientsCount = 0;
}

void ACPP_EltSimulatorCommunicator::BeginPlay()
{
	Super::BeginPlay();

	UpdateLocalIP();
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
