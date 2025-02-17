/*
    Custom Player Nametags
    ----- by Nyzenic, edited by Akenno -----
    https://www.burgershot.gg/showthread.php?tid=113
*/

#include <a_samp>
#include <streamer>
#include <YSI\y_hooks>
#include <foreach> 


#define NT_DISTANCE          25.0
#define NT_UPDATE            500


 
new Text3D:cNametag[MAX_PLAYERS];
 
hook OnGameModeInit()
{
    ShowNameTags(0);
    print("--- Custom nametags by Nyzenic loaded. Edited by Akenno ---");
    SetTimer("UpdateNametag", NT_UPDATE, true);
    return 1;
}

static GetHealthDots(playerid)
{
    new
        dots[64], Float: HP;
 
    GetPlayerHealth(playerid, HP);
 
    if(HP >= 100)
        dots = "••••••••••";
    else if(HP >= 90)
        dots = "•••••••••{660000}•";
    else if(HP >= 80)
        dots = "••••••••{660000}••";
    else if(HP >= 70)
        dots = "•••••••{660000}•••";
    else if(HP >= 60)
        dots = "••••••{660000}••••";
    else if(HP >= 50)
        dots = "•••••{660000}•••••";
    else if(HP >= 40)
        dots = "••••{660000}••••••";
    else if(HP >= 30)
        dots = "•••{660000}•••••••";
    else if(HP >= 20)
        dots = "••{660000}••••••••";
    else if(HP >= 10)
        dots = "•{660000}•••••••••";
    else if(HP >= 0)
        dots = "{660000}••••••••••";
 
    return dots;
}

static GetArmorDots(playerid)
{
    new
        dots[64], Float: AR;
 
    GetPlayerArmour(playerid, AR);
 
    if(AR >= 100)
        dots = "••••••••••";
    else if(AR >= 90)
        dots = "•••••••••{666666}•";
    else if(AR >= 80)
        dots = "••••••••{666666}••";
    else if(AR >= 70)
        dots = "•••••••{666666}•••";
    else if(AR >= 60)
        dots = "••••••{666666}••••";
    else if(AR >= 50)
        dots = "•••••{666666}•••••";
    else if(AR >= 40)
        dots = "••••{666666}••••••";
    else if(AR >= 30)
        dots = "•••{666666}•••••••";
    else if(AR >= 20)
        dots = "••{666666}••••••••";
    else if(AR >= 10)
        dots = "•{666666}•••••••••";
    else if(AR >= 0)
        dots = "{666666}••••••••••";
 
    return dots;
}
 
hook OnPlayerConnect(playerid)
{
    cNametag[playerid] = CreateDynamic3DTextLabel("(Loading Nametag)", 0xFFFFFFFF, 0.0, 0.0, 0.1, NT_DISTANCE, .attachedplayer = playerid, .testlos = 1);
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    if(IsValidDynamic3DTextLabel(cNametag[playerid]))
              DestroyDynamic3DTextLabel(cNametag[playerid]);
    return 1;
}

forward UpdateNametag();
public UpdateNametag()
{
    foreach(new i : Player)
    {
        if(IsPlayerConnected(i)) 
        {
            new
                name[128],
                playername[MAX_PLAYER_NAME],
                Float: armour
            ;

            GetPlayerArmour(i, armour);
            GetPlayerName(i, playername, sizeof(playername));
            
            if(armour > 1.0) format(name, sizeof name, "{%06x}%s {FFFFFF}(%i)\n{FFFFFF}%s\n{FF0000}%s", GetPlayerColor(i) >>> 8, playername, i, GetArmorDots(i), GetHealthDots(i));
            else format(name, sizeof name, "{%06x}%s {FFFFFF}(%i)\n{FF0000}%s", GetPlayerColor(i) >>> 8, playername, i, GetHealthDots(i));

            UpdateDynamic3DTextLabelText(cNametag[i], 0xFFFFFFFF, name);
        }
    }
}
