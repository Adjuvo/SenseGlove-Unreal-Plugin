/* robin@senseglove.com */

#include "SenseGloveController.h"

// Sets default values for this component's properties
USenseGloveController::USenseGloveController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	if (SGCore::DeviceList::SenseCommRunning()) {
		//UE_LOG(SenseGlove, Log, TEXT("SenseComm is Running now (init routine)"));
		controllerHandle = new SGCore::SG::SenseGlove();
		
	}

	else {
		//UE_LOG(SenseGlove, Log, TEXT("SenseComm is not Running (init routine)"));
	}
}


// Called when the game starts
void USenseGloveController::BeginPlay()
{
	Super::BeginPlay();
	
	// ...
	
}


// Called every frame
void USenseGloveController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


bool USenseGloveController::sendBuzz(int thumb, int index, int middle, int ring, int pinky)

{
	/* Values should be between 0 - 100, no range checking because they are
	already checked in SenseComm */

	if (!SGCore::DeviceList::SenseCommRunning()) {
		UE_LOG(SenseGlove, Warning, TEXT("SenseComm is not running"));
		return false;
	}

	if (!SGCore::SG::SenseGlove::GetSenseGlove(*controllerHandle)) {
		UE_LOG(SenseGlove, Warning, TEXT("Failed to get a SenseGlove, please connect a SenseGlove"));
		return false;
	}

	controllerHandle->SendHaptics(SGCore::Haptics::SG_BuzzCmd(thumb, index, middle, ring, pinky));

	return true;
}

bool USenseGloveController::sendForceFeedback(int thumb, int index, int middle, int ring, int pinky)
{
	/* Values should be between 0 - 100, no range checking because they are
	already checked in SenseComm */

	if (!SGCore::DeviceList::SenseCommRunning()) {
		UE_LOG(SenseGlove, Warning, TEXT("SenseComm is not running"));
		return false;
	}

	if (!SGCore::SG::SenseGlove::GetSenseGlove(*controllerHandle)) {
		UE_LOG(SenseGlove, Warning, TEXT("Failed to get a SenseGlove, please connect a SenseGlove"));
		return false;
	}

	controllerHandle->SendHaptics(SGCore::Haptics::SG_FFBCmd(thumb, index, middle, ring, pinky));

	return true;
}

bool USenseGloveController::sendThumper(TEnumAsByte<ThumperWaveForm> wave)
{
	if (!SGCore::DeviceList::SenseCommRunning()) {
		UE_LOG(SenseGlove, Warning, TEXT("SenseComm is not running"));
		return false;
	}

	if (!SGCore::SG::SenseGlove::GetSenseGlove(*controllerHandle)) {
		UE_LOG(SenseGlove, Warning, TEXT("Failed to get a SenseGlove, please connect a SenseGlove"));
		return false;
	}


	controllerHandle->SendHaptics(SGCore::Haptics::SG_ThumperCmd((int) wave.GetValue()));

	return true;
}
