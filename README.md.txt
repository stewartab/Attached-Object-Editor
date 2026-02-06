# Attach Object Editor for SA-MP (YSI-Based)

A **dialog-based attach object editor** for SA-MP servers.  
Allows admins or developers to **spawn objects, attach them to players, adjust offsets and rotation, remove objects, and save/load them to INI files** — all without typing commands. Built entirely using **PAWN + YSI includes**.

---

## Features

- Spawn and attach objects to players using an **in-game dialog**.  
- Live adjustment of **position offsets** (X/Y/Z) and **rotation** (RX/RY/RZ).  
- Attach multiple objects to different players simultaneously.  
- Remove attached objects with a single click.  
- Save attachments to **INI files**, automatically creating the file if it doesn’t exist.  
- Load attachments from INI files and automatically attach them to the player.  
- Fully compatible with **YSI `y_ini`**, **PAWN CMD**, and **sscanf**.  
- Works in **real-time** without restarting the server.

---

## Required Libraries

- **[YSI Includes](https://github.com/IllidanS4/YSI-Includes)**: `y_ini`, `y_hooks`  
- **PawnCMD**: For handling commands (optional if using dialog only)  
- **sscanf**: For parsing user input  

Include in your `gamemode.pwn`:

```pawn
#include <y_ini>
#include <y_hooks>
#include <pawncmd>
#include <sscanf>
#include "attach_editor"
```

---


## Installation
1. Copy `attach_object_editor.inc` into your PAWN includes or server gamemode folder.
2. Ensure all required libraries (y_ini, y_hooks, pawncmd, sscanf) are included.
3. Compile your gamemode with PAWN 3.10+.

---

## Usage
## Dialog-Based Editor
- Open the attach object editor dialog (for admins/developers).
- Spawn Object: Enter the object model ID.
- Attach Object: Choose a player to attach the object.
- Adjust Offsets/Rotation: Fine-tune X/Y/Z offsets and RX/RY/RZ rotation.
- Remove Object: Detach and delete the object from the player.
## Saving and Loading Attachments
- Save Attachment: Saves the current attachment to an INI file.
   - Default: attach_<playerid>.ini
- Load Attachment: Loads and attaches an object from an INI file.
   - Default: attach_<playerid>.ini

> The INI file is automatically created if it doesn’t exist.

## Example INI Output
```ini
[AttachObject]
objectid=1277
playerid=0
offsetX=0.150
offsetY=0.050
offsetZ=0.050
rotX=0.0
rotY=0.0
rotZ=90.0
```
- Stores object ID, attached player, offsets, and rotation.
- Fully editable and reusable across servers or sessions.

---

## Requirements
- SA-MP 0.3.7+ server
- PAWN 3.10+ compiler
- YSI Includes: y_ini, y_hooks
- PawnCMD: For command support (`y_commands` or `zcmd` can be used)
- sscanf: For parsing input

---

## License
- Free to use and distribute for SA-MP servers.
- Credit appreciated if redistributed.