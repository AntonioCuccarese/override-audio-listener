[![en](https://img.shields.io/badge/lang-en-red.svg)](https://github.com/AntonioCuccarese/override-audio-listener/blob/main/README.md)
[![it](https://img.shields.io/badge/lang-it-green.svg)](https://github.com/AntonioCuccarese/override-audio-listener/blob/main/README.it.md)

# override-audio-listener

This is a guide to override Audio Listener in Unreal Engine 5 by using a custom PlayerController.

This new controller, called **MyPlayerController**, will extend the original PlayerController, overriding the audio listener function.

## How to

### Step 1 - Show C++ files in Content Drawer

To be able to find, create and edit C++ files you should flag "Show C++ Classes" and "Show Engine Content" in the Content Drawer settings.

If you have already enabled these two options, skip to the following step.

[![enable-engine.png](https://i.postimg.cc/3wgNtWxX/enable-engine.png)](https://postimg.cc/mcgTDLMk)

### Step 2 - Extend PlayerController

While in the Content Drawer, search for "PlayerController" inside the **Engine** folder, right click on the C++ class and select "Create C++ class derived from PlayerController".

[![player-controller.png](https://i.postimg.cc/5tQhWkY1/player-controller.png)](https://postimg.cc/TyG7r0JH)

It will open the "Add C++ Class" window. Click on "Create Class" and wait for the operation to finish.

### Step 3 - Update the new MyPlayerController

Once the MyPlayerController has been created you have to update it with the code that overrides the audio listener.

In order to do that, search for MyPlayerController inside the **C++ Classes** folder and double click on it. It will open MyPlayerController.h and MyPlayerController.cpp.

[![my-player-controller.png](https://i.postimg.cc/PxQyZmp0/my-player-controller.png)](https://postimg.cc/Vr5XP0FF)

Replace the code of MyPlayerController.h and MyPlayerController.cpp with the code of the two files shared in this repository.

**NOTE: Update the {{PROJECT_NAME}} inside the MyPlayerController.h shared here with the actual project name, in uppercase. This is the only change needed in the 2 files.**

### Step 4 - Compile

After that, click on the square icon on the right side of the Unreal bottom bar, it will recompile the C++ classes. At the end of the compiling operation, you should see the "Compile Complete!" message.

[![compile.png](https://i.postimg.cc/qMKfYvYq/compile.png)](https://postimg.cc/XpnDB4n6)

### Step 5 - Set MyPlayerController as PlayerController

This is the final step, needed to set the brand new MyPlayerController as PlayerController in the project.

Click on the list of blueprints and in the world override, under the game mode classes, change the PlayerController with the new created one.

[![select-controller.png](https://i.postimg.cc/wB3DWTcv/select-controller.png)](https://postimg.cc/v1F1TyKF)
