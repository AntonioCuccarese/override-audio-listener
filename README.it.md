[![en](https://img.shields.io/badge/lang-en-red.svg)](https://github.com/AntonioCuccarese/override-audio-listener/blob/main/README.md)
[![it](https://img.shields.io/badge/lang-it-green.svg)](https://github.com/AntonioCuccarese/override-audio-listener/blob/main/README.it.md)

# override-audio-listener

Questa è una guida su come sovrascrivere l'Audio Listener in Unreal Engine 5 usando un PlayerController personalizzato.

Questo nuovo controller, chiamato **MyPlayerController**, estende il PlayerController nativo, sovrascrivendo la posizione dell'audio listener.

In particolare, ora l'audio listener non si trova più sulla videocamera ma bensì sul player.

## Come fare

### Passo 1 - Mostrare i file C++ nel Content Drawer

Per poter trovare, creare e modificare i file C++, è necessario abilitare le opzioni "Show C++ Classes" e "Show Engine Content" nelle impostazioni del Content Drawer.

Se hai già abilitato queste due opzioni, passa al passaggio successivo.

[![enable-engine.png](https://i.postimg.cc/3wgNtWxX/enable-engine.png)](https://postimg.cc/mcgTDLMk)

### Passo 2 - Estendere il PlayerController

Mentre sei nel Content Drawer, cerca "PlayerController" nella cartella **Engine**, fai clic destro sulla classe C++ e seleziona "Create C++ class derived from PlayerController".

[![player-controller.png](https://i.postimg.cc/5tQhWkY1/player-controller.png)](https://postimg.cc/TyG7r0JH)

Si aprirà la finestra "Add C++ Class". Clicca su "Create Class" e attendi che l'operazione finisca.

Alla fine della creazione, si apriranno due file: MyPlayerController.h e MyPlayerController.cpp.

### Passo 3 - Aggiornare il MyPlayerController

Una volta che MyPlayerController è stato creato, devi aggiornarlo con il codice che sovrascrive la posizione dell'audio listener.

I file MyPlayerController.h e MyPlayerController.cpp dovrebbero ora essere già aperti nel tuo IDE (Visual Studio, XCode o simili). Se non lo sono, puoi aprirli cliccando su MyPlayerController nella cartella **C++ Classes**.

[![my-player-controller.png](https://i.postimg.cc/PxQyZmp0/my-player-controller.png)](https://postimg.cc/Vr5XP0FF)

#### Aggiornare MyPlayerController.h

Nel file MyPlayerController.h, sotto GENERATED_BODY(), incolla la seguente riga di codice: 
```
virtual void GetAudioListenerPosition(FVector& OutLocation, FVector& OutFrontDir, FVector& OutRightDir) const;
```
Il risultato deve essere uguale a questo, eccetto per il nome del progetto (in questo esempio è "PROJECT"):
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

#### Aggiornare MyPlayerController.cpp

Sostituisci il codice in MyPlayerController.cpp con il codice qui sotto:

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

>Puoi trovare il codice dei due file anche in questa repository. Importante: ricorda di sostituire il nome del progetto nel file MyPlayerController.h se decidi di sostituire i file del progetto con quelli scaricati da questa repository.

### Passo 4 - Compilare

Dopo aver fatto ciò, clicca sull'icona quadrata nella barra inferiore di Unreal Engine, che ricompilerà le classi C++. Alla fine dell'operazione di compilazione, dovresti vedere il messaggio "Compile Complete!".

[![compile.png](https://i.postimg.cc/qMKfYvYq/compile.png)](https://postimg.cc/XpnDB4n6)

### Passo 5 - Impostare MyPlayerController come PlayerController

Questo è il passaggio finale, necessario per impostare il nuovo MyPlayerController come PlayerController nel progetto.

Clicca sulla lista di blueprints e nella sezione world override, sotto le classi del game mode, cambia il PlayerController con quello appena creato.

[![select-controller.png](https://i.postimg.cc/wB3DWTcv/select-controller.png)](https://postimg.cc/v1F1TyKF)
