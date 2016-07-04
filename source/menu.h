#ifndef MENU_H
#define MENU_H

#include "helpers.h"

extern GAME_PLUGIN_MENU gamePluginMenu;

void initMenu();

void addMenuEntry(char* str);
void addCheatMenuEntry(char* str);

u32 updateMenu();

#endif
