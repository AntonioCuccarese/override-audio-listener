[![en](https://img.shields.io/badge/lang-en-red.svg)](https://github.com/AntonioCuccarese/override-audio-listener/blob/main/README.md)
[![it](https://img.shields.io/badge/lang-it-green.svg)](https://github.com/AntonioCuccarese/override-audio-listener/blob/main/README.it.md)

# override-audio-listener

This is a guide to override Audio Listener in Unreal Engine 5 by using a custom PlayerController.

This new controller, called **MyPlayerController**, will extend the original PlayerController, overriding the position of the audio listener.

In particular, the audio listener will be placed on the player instead of being placed on the camera.

## How to

### Step 1 - Show C++ files in Content Drawer

To be able to find, create and edit C++ files you should flag "Show C++ Classes" and "Show Engine Content" in the Content Drawer settings.

If you have already enabled these two options, skip to the following step.

[![enable-engine.png](https://i.postimg.cc/3wgNtWxX/enable-engine.png)](https://postimg.cc/mcgTDLMk)

### Step 2 - Extend PlayerController

While in the Content Drawer, search for "PlayerController" inside the **Engine** folder, right click on the C++ class and select "Create C++ class derived from PlayerController".

[![player-controller.png](https://i.postimg.cc/5tQhWkY1/player-controller.png)](https://postimg.cc/TyG7r0JH)

It will open the "Add C++ Class" window. Click on "Create Class" and wait for the operation to finish.

At the end it will open the new created MyPlayerController.h and MyPlayerController.cpp files.

### Step 3 - Update the new MyPlayerController

Once the MyPlayerController has been created you have to update it with the code that overrides the audio listener position.

You should now have the MyPlayerController.h and MyPlayerController.cpp files open in your IDE (Visual Studio, XCode or similar). If not, you can open clicking on the MyPlayerController inside the **C++ Classes** folder.

[![my-player-controller.png](https://i.postimg.cc/PxQyZmp0/my-player-controller.png)](https://postimg.cc/Vr5XP0FF)


#### Update MyPlayerController.h

In the MyPlayerController.h, under GENERATED_BODY(), paste the following string: 
```
virtual void GetAudioListenerPosition(FVector& OutLocation, FVector& OutFrontDir, FVector& OutRightDir) const;
```
The result should be equal to this, except for the project name (in this example it is "PROJECT"):
```
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API AMyPlayerController : public APlayerController
{
    GENERATED_BODY()
    
    virtual void GetAudioListenerPosition(FVector& OutLocation, FVector& OutFrontDir, FVector& OutRightDir) const;
};
```

#### Update MyPlayerController.cpp

Replace the code inside MyPlayerController.cpp with the following one:
```
#include "MyPlayerController.h"

void AMyPlayerController::GetAudioListenerPosition(FVector& OutLocation, FVector& OutFrontDir, FVector& OutRightDir) const {
    
    FVector ViewLocation;
    FRotator ViewRotation;

    if (bOverrideAudioListener) {
        USceneComponent* ListenerComponent = AudioListenerComponent.Get();
        if (ListenerComponent != nullptr) {
            ViewRotation = ListenerComponent->GetComponentRotation() + AudioListenerRotationOverride;
            ViewLocation = ListenerComponent->GetComponentLocation() + ViewRotation.RotateVector(AudioListenerLocationOverride);
        } else {
            ViewLocation = AudioListenerLocationOverride;
            ViewRotation = AudioListenerRotationOverride;
        }
    } else {
        GetPlayerViewPoint(ViewLocation, ViewRotation);
        if (GetPawn()) {
            ViewLocation = GetPawn()->GetActorLocation();
        }
    }

    const FRotationTranslationMatrix ViewRotationMatrix(ViewRotation, ViewLocation);

    OutLocation = ViewLocation;
    OutFrontDir = ViewRotationMatrix.GetUnitAxis(EAxis::X);
    OutRightDir = ViewRotationMatrix.GetUnitAxis(EAxis::Y);

}
```

### Step 4 - Compile

After that, click on the square icon on the right side of the Unreal bottom bar, it will recompile the C++ classes. At the end of the compiling operation, you should see the "Compile Complete!" message.

[![compile.png](https://i.postimg.cc/qMKfYvYq/compile.png)](https://postimg.cc/XpnDB4n6)

### Step 5 - Set MyPlayerController as PlayerController

This is the final step, needed to set the brand new MyPlayerController as PlayerController in the project.

Click on the list of blueprints and in the world override, under the game mode classes, change the PlayerController with the new created one.

[![select-controller.png](https://i.postimg.cc/wB3DWTcv/select-controller.png)](https://postimg.cc/v1F1TyKF)
