/* robin@senseglove.com */

#pragma once

#include "CoreMinimal.h"

#include "Animation/AnimInstance.h"
#include "Animation/AnimInstanceProxy.h" 
#include "SenseGloveController.h"

#include "../Thirdparty/SenseGlove/incl/SenseGlove.h"
#include "../Thirdparty/SenseGlove/incl/DeviceList.h"
#include "../Thirdparty/SenseGlove/incl/Values.h"

#include "SenseGloveAnimInstance.generated.h"


/* Since Unreal 4.12 Animation is done in theads and should be called through 
this AnimInstanceProxy */
USTRUCT(BlueprintInternalUseOnly)
struct FSGProxy : public FAnimInstanceProxy
{
    GENERATED_BODY()

public:
    FSGProxy() : FAnimInstanceProxy() {}
    FSGProxy(UAnimInstance* Instance) : FAnimInstanceProxy(Instance) {}

    /** Update Internal variables*/
    virtual void Update(float DeltaSeconds) override;
    virtual bool Evaluate(FPoseContext& Output) override;

    USenseGloveController* Controller;

};


UCLASS(Blueprintable)
class USenseGloveAnimInstance : public UAnimInstance
{
    GENERATED_BODY()

    //UPROPERTY(Transient, BlueprintReadOnly, Category = "Example", meta = (AllowPrivateAccess = "true"))
    FSGProxy Proxy;

    virtual FAnimInstanceProxy* CreateAnimInstanceProxy() override

    {
        // override this to just return the proxy on this instance
        return &Proxy;
    }

    virtual void DestroyAnimInstanceProxy(FAnimInstanceProxy* InProxy) override

    {

    }

    virtual void NativeInitializeAnimation() override;
    virtual void NativeUninitializeAnimation() override;


    friend struct FTestProxy;

public:

    /* */

};

