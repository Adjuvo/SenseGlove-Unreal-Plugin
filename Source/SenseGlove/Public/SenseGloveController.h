/* robin@senseglove.com */

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "../Thirdparty/SenseGlove/incl/SenseGlove.h"
#include "../Thirdparty/SenseGlove/incl/DeviceList.h"

#include "SenseGloveController.generated.h"

UENUM(BlueprintType)
enum class ThumperWaveForm : uint8
{
	Blank = 0,
	Impact_Thump_100 = 1,
	Impact_Thump_30 = 3,
	Impact_Thump_10 = 6,
	Object_Grasp_100 = 7,
	Object_Grasp_60 = 8,
	Object_Grasp_30 = 9,
	Button_Double_100 = 10,
	Button_Double_60 = 11,
	Cue_Game_Over = 118,
	Turn_Off = 124,
	None = 126
};

UENUM(BlueprintType)
enum class GloveType : uint8
{
	RightGlove = 0,
	LeftGlove = 1
};


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class USenseGloveController : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USenseGloveController();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

	/* controllerHandle is also used by SenseGloveAnimInstance */
	SGCore::SG::SenseGlove* controllerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SenseGlove")
		TEnumAsByte<GloveType> gloveType = GloveType::RightGlove;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "SenseGlove")
		bool sendBuzz(int thumb, int index, int middle, int ring, int pinky);

	UFUNCTION(BlueprintCallable, Category = "SenseGlove")
		bool sendForceFeedback(int thumb, int index, int middle, int ring, int pinky);

	UFUNCTION(BlueprintCallable, Category = "SenseGlove")
		bool sendThumper(TEnumAsByte<ThumperWaveForm> wave);

private:
	int ff[5] = { 0 };
	int buzz[5] = { 0 };

};


