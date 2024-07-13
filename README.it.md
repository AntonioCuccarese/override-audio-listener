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

### Passo 3 - Aggiornare il nuovo MyPlayerController

Una volta che MyPlayerController è stato creato, devi aggiornarlo con il codice che sovrascrive la posizione dell'audio listener.

Per fare ciò, cerca MyPlayerController nella cartella **C++ Classes** e fai doppio clic su di esso. Si apriranno i file MyPlayerController.h e MyPlayerController.cpp.

[![my-player-controller.png](https://i.postimg.cc/PxQyZmp0/my-player-controller.png)](https://postimg.cc/Vr5XP0FF)

Sostituisci il codice di MyPlayerController.h e MyPlayerController.cpp con quello dei due file condivisi in questa repository.

**IMPORTANTE: Aggiorna il {{PROJECT_NAME}} all'interno di MyPlayerController.h con il nome effettivo del progetto, in maiuscolo. Questo è l'unico cambiamento necessario nei 2 file.**

### Passo 4 - Compilare

Dopo aver fatto ciò, clicca sull'icona quadrata nella barra inferiore di Unreal Engine, che ricompilerà le classi C++. Alla fine dell'operazione di compilazione, dovresti vedere il messaggio "Compile Complete!".

[![compile.png](https://i.postimg.cc/qMKfYvYq/compile.png)](https://postimg.cc/XpnDB4n6)

### Passo 5 - Impostare MyPlayerController come PlayerController

Questo è il passaggio finale, necessario per impostare il nuovo MyPlayerController come PlayerController nel progetto.

Clicca sulla lista di blueprints e nella sezione world override, sotto le classi del game mode, cambia il PlayerController con quello appena creato.

[![select-controller.png](https://i.postimg.cc/wB3DWTcv/select-controller.png)](https://postimg.cc/v1F1TyKF)
