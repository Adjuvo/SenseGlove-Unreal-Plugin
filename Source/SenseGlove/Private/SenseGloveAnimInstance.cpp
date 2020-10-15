/* robin@senseglove.com */
#include "SenseGloveAnimInstance.h"

#define LOCTEXT_NAMESPACE "FSenseGloveModule"

/* Function that can modify the update speed */
void FSGProxy::Update(float DeltaSeconds) {

}

bool FSGProxy::Evaluate(FPoseContext& Output)
{
	
	/* Local variables storage finger and thumb rotation */
	SGCore::Kinematics::Vect3D hai1, hai2, hai3;
	SGCore::Kinematics::Vect3D ham1, ham2, ham3;
	SGCore::Kinematics::Vect3D har1, har2, har3;
	SGCore::Kinematics::Vect3D hap1, hap2, hap3;
	SGCore::Kinematics::Vect3D hat1, hat2, hat3;

	/* Handangles is a two dimensional array, 
	starting at the root of the fingers / thumb. 
	See SenseCom API for extended documentation */
	std::vector<std::vector<SGCore::Kinematics::Vect3D>> handAngles;
	
	/* Default is right-handed, in case of not instanced in Blueprint */
	bool rightHanded = true;

	/* HACK to not keep spamming warning messages */
	bool warningMessageOnce = false;
	
	/* Check if SenseComm is opened */
	if (!SGCore::DeviceList::SenseCommRunning()) {
		
		if (!warningMessageOnce) {
			UE_LOG(SenseGlove, Warning, TEXT("SenseCom is not running! Please run SenseCom"));
			warningMessageOnce = true;
		}

		return false;
	}

	/* Check if there exists a USenseGloveController Component in the hierarchy */
	if (!Controller) {
		if (!warningMessageOnce) {
			//UE_LOG(SenseGlove, Log, TEXT("No controller component in Blueprint or Class!"));
			warningMessageOnce = true;
		}
		return false;
	}

	/* Check GloveType instance set in Blueprint */
	if (Controller->gloveType == GloveType::RightGlove)
		rightHanded = true;
	else if (Controller->gloveType == GloveType::LeftGlove) {
		rightHanded = false;
	}
	else {
		UE_LOG(SenseGlove, Warning, TEXT("Unknown Glove Type (neither right nor left"));
		return false;
	}

	if (!Controller->controllerHandle)
		return false;

	/* Get the first available right or left glove */
	if (!SGCore::SG::SenseGlove::GetSenseGlove(rightHanded, *Controller->controllerHandle)) {
		if (!warningMessageOnce) {
			UE_LOG(SenseGlove, Warning, TEXT("Can't get SenseGlove! Make sure you have connected a SenseGlove"));
			warningMessageOnce = true;
		}
		return false;
	}

	/* HandProfile, parameter true is right, false is left */
	SGCore::SG::SG_HandProfile handProfile;
	if (rightHanded) {
		handProfile = SGCore::SG::SG_HandProfile::Default(true);
	}
	else {
		handProfile = SGCore::SG::SG_HandProfile::Default(false);
	};

	warningMessageOnce = false;
	
	/* Get a bone listing as you see in the editor after
	importing a skeletal mesh. Should conform to the senseGlove origin mesh
	naming convention. Check is a bit shady, because it only checks one name */
	auto bc = Output.Pose.GetBoneContainer();
	if (bc.GetPoseBoneIndexForBoneName("metarig") == -1) {
		UE_LOG(SenseGlove, Error, TEXT("Skeletal mesh doesn't conform to naming convention"));
		return false;
	}

	SGCore::SG::SG_Solver solver = SGCore::SG::SG_Solver::Interpolation;
	SGCore::HandPose handPose;

	if (Controller->controllerHandle->GetHandPose(handProfile, solver, handPose)) {

			handAngles = handPose.handAngles;
			/* Possible not thread-safe
			Temporary storage within routine 
			Explicit for debugging purposes */

			hai1 = SGCore::Kinematics::Values::Degrees(handAngles[1][0]);
			hai2 = SGCore::Kinematics::Values::Degrees(handAngles[1][1]);
			hai3 = SGCore::Kinematics::Values::Degrees(handAngles[1][2]);

			ham1 = SGCore::Kinematics::Values::Degrees(handAngles[2][0]);
			ham2 = SGCore::Kinematics::Values::Degrees(handAngles[2][1]);
			ham3 = SGCore::Kinematics::Values::Degrees(handAngles[2][2]);

			har1 = SGCore::Kinematics::Values::Degrees(handAngles[3][0]);
			har2 = SGCore::Kinematics::Values::Degrees(handAngles[3][1]);
			har3 = SGCore::Kinematics::Values::Degrees(handAngles[3][2]);

			hap1 = SGCore::Kinematics::Values::Degrees(handAngles[4][0]);
			hap2 = SGCore::Kinematics::Values::Degrees(handAngles[4][1]);
			hap3 = SGCore::Kinematics::Values::Degrees(handAngles[4][2]);

			hat1 = SGCore::Kinematics::Values::Degrees(handAngles[0][0]);
			hat2 = SGCore::Kinematics::Values::Degrees(handAngles[0][1]);
			hat3 = SGCore::Kinematics::Values::Degrees(handAngles[0][2]);

	}

	/* Explicit for debugging purposes */
	int t1 = bc.GetPoseBoneIndexForBoneName("thumb_01");
	int t2 = bc.GetPoseBoneIndexForBoneName("thumb_02");
	int t3 = bc.GetPoseBoneIndexForBoneName("thumb_03");

	int i1 = bc.GetPoseBoneIndexForBoneName("f_index_01");
	int i2 = bc.GetPoseBoneIndexForBoneName("f_index_02");
	int i3 = bc.GetPoseBoneIndexForBoneName("f_index_03");

	int m1 = bc.GetPoseBoneIndexForBoneName("f_middle_01");
	int m2 = bc.GetPoseBoneIndexForBoneName("f_middle_02");
	int m3 = bc.GetPoseBoneIndexForBoneName("f_middle_03");

	int r1 = bc.GetPoseBoneIndexForBoneName("f_ring_01");
	int r2 = bc.GetPoseBoneIndexForBoneName("f_ring_02");
	int r3 = bc.GetPoseBoneIndexForBoneName("f_ring_03");

	int p1 = bc.GetPoseBoneIndexForBoneName("f_pinky_01");
	int p2 = bc.GetPoseBoneIndexForBoneName("f_pinky_02");
	int p3 = bc.GetPoseBoneIndexForBoneName("f_pinky_03");

	int corr = 1;
	if (!rightHanded)
		corr = -1;

	FQuat adji1(FRotator(-hai1.x, -hai1.y, corr * -hai1.z));
	FQuat adji2(FRotator(-hai2.x, -hai2.y, corr * -hai2.z));
	FQuat adji3(FRotator(-hai3.x, -hai3.y, corr * -hai3.z));

	FQuat adjm1(FRotator(-ham1.x, -ham1.y, corr * -ham1.z));
	FQuat adjm2(FRotator(-ham2.x, -ham2.y, corr * -ham2.z));
	FQuat adjm3(FRotator(-ham3.x, -ham3.y, corr * -ham3.z));

	FQuat adjr1(FRotator(-har1.x, -har1.y, corr * -har1.z));
	FQuat adjr2(FRotator(-har2.x, -har2.y, corr * -har2.z));
	FQuat adjr3(FRotator(-har3.x, -har3.y, corr * -har3.z));

	FQuat adjp1(FRotator(-hap1.x, -hap1.y, corr * -hap1.z));
	FQuat adjp2(FRotator(-hap2.x, -hap2.y, corr * -hap2.z));
	FQuat adjp3(FRotator(-hap3.x, -hap3.y, corr * -hap3.z));

	FQuat adjt1;

	/* HACK: The -15 degrees is an adjustment for the current hand Model */
	if (corr == 1)
		adjt1 = FQuat(FRotator(hat1.x, -hat1.z - 15, hat1.y));
	else {
		adjt1 = FQuat(FRotator(hat1.x, hat1.z - 15, hat1.y));
	}

	FQuat adjt2(FRotator(0, 0, hat2.y));
	FQuat adjt3(FRotator(0, 0, hat3.y));
	
	/* Use the reference pose, to set an initial position and then apply rotations */
	Output.ResetToRefPose();

	Output.Pose[(FCompactPoseBoneIndex)i1].SetRotation(adji1);
	Output.Pose[(FCompactPoseBoneIndex)i2].SetRotation(adji2);
	Output.Pose[(FCompactPoseBoneIndex)i3].SetRotation(adji3);

	Output.Pose[(FCompactPoseBoneIndex)m1].SetRotation(adjm1);
	Output.Pose[(FCompactPoseBoneIndex)m2].SetRotation(adjm2);
	Output.Pose[(FCompactPoseBoneIndex)m3].SetRotation(adjm3);

	Output.Pose[(FCompactPoseBoneIndex)r1].SetRotation(adjr1);
	Output.Pose[(FCompactPoseBoneIndex)r2].SetRotation(adjr2);
	Output.Pose[(FCompactPoseBoneIndex)r3].SetRotation(adjr3);

	Output.Pose[(FCompactPoseBoneIndex)p1].SetRotation(adjp1);
	Output.Pose[(FCompactPoseBoneIndex)p2].SetRotation(adjp2);
	Output.Pose[(FCompactPoseBoneIndex)p3].SetRotation(adjp3);

	Output.Pose[(FCompactPoseBoneIndex)t1].SetRotation(adjt1);	
	Output.Pose[(FCompactPoseBoneIndex)t2].SetRotation(adjt2);
	Output.Pose[(FCompactPoseBoneIndex)t3].SetRotation(adjt3);

	return true;
}
/* First time the instance is spawned (or opened in the editor)
Thise function gets called many times when previewing, opening, dragging dropping, simulating
Used as a piggybag to initialize a senseglove device */
void USenseGloveAnimInstance::NativeInitializeAnimation()
{
	//UE_LOG(SenseGlove, Log, TEXT("Initialized animation, create new Senseglove"));

	APawn* pawn = TryGetPawnOwner();
	
	if (!pawn) {
		UE_LOG(SenseGlove, Warning, TEXT("No Pawn owner for Animation Instance!"));
	}
	else {
		/* Get the first available SenseGlove controller */
		Proxy.Controller = pawn->FindComponentByClass<USenseGloveController>();

		if (Proxy.Controller) {
			UE_LOG(SenseGlove, Log, TEXT("Found controller component"));
			Proxy.Controller->controllerHandle;

		}
		//else {
		//	UE_LOG(SenseGlove, Warning, TEXT("Can't find controller component (yet), make sure you add a SenseGloveController"));
		//}

	}

}

void USenseGloveAnimInstance::NativeUninitializeAnimation() {

	//UE_LOG(SenseGlove, Log, TEXT("Uninitialize animation instance"));

}

#undef LOCTEXT_NAMESPACE
