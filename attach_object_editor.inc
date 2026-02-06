#include <Pawn.CMD>
#include <sscanf2>
#include <YSI_Coding\y_hooks>
#include <YSI_Storage\y_ini>


enum E_ATTACH_EDITOR
{
    aeObjectID,
    aeAttachedPlayer,
    Float:aeOffsetX,
    Float:aeOffsetY,
    Float:aeOffsetZ,
    Float:aeRotX,
    Float:aeRotY,
    Float:aeRotZ,
    aeActive
}
new AttachEditor[MAX_PLAYERS][E_ATTACH_EDITOR];

// Function to open the attached object editor
public OnPlayerEditAttachedObject(playerid, EDIT_RESPONSE:response, index, modelid, boneid, Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fScaleX, Float:fScaleY, Float:fScaleZ)
{
    if (response == EDIT_RESPONSE_FINAL)
    {
        SendClientMessage(playerid, COLOR_GREEN, "Attached object edition saved.");

        AttachEditor[playerid][aeOffsetX] = fOffsetX;
        AttachEditor[playerid][aeOffsetY] = fOffsetY;
        AttachEditor[playerid][aeOffsetZ] = fOffsetZ;
        AttachEditor[playerid][aeRotX] = fRotX;
        AttachEditor[playerid][aeRotY] = fRotY;
        AttachEditor[playerid][aeRotZ] = fRotZ;
    }
    else if (response == EDIT_RESPONSE_CANCEL) SetPlayerAttachedObject(playerid, index, AttachEditor[playerid][aeObjectID], 1, AttachEditor[playerid][aeOffsetX], AttachEditor[playerid][aeOffsetY], AttachEditor[playerid][aeOffsetZ], AttachEditor[playerid][aeRotX], AttachEditor[playerid][aeRotY], AttachEditor[playerid][aeRotZ]);
    return 1;
}


// Command to start the attached object editor
CMD:attacheditor(playerid, params[])
{
    new objid;
    switch(AttachEditor[playerid][aeActive])
    {
        case 0: // Not active, create new object
        {
            if(sscanf(params, "d", objid))
            {
                return SendClientMessage(playerid, COLOR_RED, "Usage: /attacheditor [objectid]");
            }

            // Create a default object
            AttachEditor[playerid][aeAttachedPlayer] = playerid; // default attach to self
            AttachEditor[playerid][aeActive] = 1;

            // Create object above player
            new Float:px, Float:py, Float:pz;
            GetPlayerPos(playerid, px, py, pz);
            AttachEditor[playerid][aeObjectID] = objid;

            // Attach immediately with default offsets
            SetPlayerAttachedObject(playerid, 0, AttachEditor[playerid][aeObjectID], 1);

            EditAttachedObject(playerid, 0);
        }
        case 1: EditAttachedObject(playerid, AttachEditor[playerid][aeObjectID]); // Already active, just show menu
    }
    return 1;
}

CMD:editobj(playerid, params[]){

    if (AttachEditor[playerid][aeObjectID] == -1)
    {
        return SendClientMessage(playerid, COLOR_RED, "Invalid object ID.");
    }

    EditAttachedObject(playerid, 0); // Already active, just show menu
    return 1;
}

CMD:saveobj(playerid, params[])
{
    if (!AttachEditor[playerid][aeActive] || AttachEditor[playerid][aeObjectID] == INVALID_OBJECT_ID)
        return SendClientMessage(playerid, 0xFF0000FF, "No object to save.");

    new filename[64];
    if (strlen(params) < 1)
    {
        format(filename, sizeof(filename), "attach_%d.ini", playerid); // default
    }
    else
    {
        strmid(filename, params, 0, sizeof(filename)-1);
    }

    new INI:file = INI_Open(filename);
    if (!file)
    {
        SendClientMessage(playerid, 0xFFFF0000, "Failed to open INI file.");
        return 1;
    }

    INI_SetTag(file, "AttachObject");

    INI_WriteInt(file, "objectid", AttachEditor[playerid][aeObjectID]);
    INI_WriteFloat(file, "offsetX", AttachEditor[playerid][aeOffsetX], 3);
    INI_WriteFloat(file, "offsetY", AttachEditor[playerid][aeOffsetY], 3);
    INI_WriteFloat(file, "offsetZ", AttachEditor[playerid][aeOffsetZ], 3);
    INI_WriteFloat(file, "rotX", AttachEditor[playerid][aeRotX], 3);
    INI_WriteFloat(file, "rotY", AttachEditor[playerid][aeRotY], 3);
    INI_WriteFloat(file, "rotZ", AttachEditor[playerid][aeRotZ], 3);

    INI_Close(file);

    SendClientMessage(playerid, 0xFF00FF00, "Attachment saved to INI file.");
    return 1;
}