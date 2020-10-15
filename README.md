# UE4 Senseglove Plugin

SenseGlove plugin for Unreal Engine 4. 
Note: If you are starting a project from scratch, it's more convenient to use the demo scene: https://gitlab.com/senseglove/ue4-senseglove-demo-scene

## Prerequisites

1. Unreal Engine v4.10 and upwards
2. SenseCom.exe and SGCore.dll. Available here: https://github.com/Adjuvo/SenseGlove-API

## Install and configure

1. Copy this repository into either the 'Global' plugin directory or 'Local' Plugin directory of your project. 
If you don't have any Plugins directory in your project, you should create a Plugins directory and put this Plugin in a subdirectory:
Directory structure should be similar to: *My UE4 Project > Plugins > UE4_SenseGlove*
2. Copy SGCore.dll into the 'Binaries/Win64' directory of your project.

## Getting basic Hand Tracking
1. Make sure SenseCom.exe is running and a SenseGlove is connected.
2. Add a new Blueprint *Pawn* Class.
3. Add a SenseGlove Controller Component to the Blueprint. Under details > SenseGlove you can select if you want to interface a left or right glove.
4. Add a Skeletal Mesh Component to the Blueprint.
5. Import a compatible right or left hand Model (.fbx file). You can find two compatible example meshes in the Resources directory.
6. Link the imported Skeletal Mesh to the Skeletal Mesh Component. (Skeletal Mesh Component > Mesh > Skeletal Mesh)
7. Set 'SenseGloveAnimInstance' as Animation Class to this Skeletal Mesh. (Skeletal Mesh Component > Animation > Anim Class > SenseGloveAnimInstance)

![Screenshot](https://gitlab.com/senseglove/ue4-senseglove-plugin/-/raw/master/components.png "components")
![Screenshot](https://gitlab.com/senseglove/ue4-senseglove-plugin/-/raw/master/meshanimation.png "mesh animation")

## Sending Basic Commands
Once basic hand tracking is set up, you can send haptics commands to the glove
1. Open any Blueprint class
2. Make a reference to the SenseGloveController
3. The SensegloveController has a variety of built-in commands (i.e) SendBuzz/SendForceFeedback

![Screenshot](https://gitlab.com/senseglove/ue4-senseglove-plugin/-/raw/master/haptic_commands.png "haptic commands")
