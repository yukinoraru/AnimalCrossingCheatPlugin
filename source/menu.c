#include "menu.h"

GAME_PLUGIN_MENU gamePluginMenu;

void initMenu() {
	memset(&gamePluginMenu, 0, sizeof(GAME_PLUGIN_MENU));
}

void addMenuEntry(char* str) {
	if (gamePluginMenu.count > 64) {
		return;
	}
	u32 pos = gamePluginMenu.count;
	u32 len = strlen(str) + 1;
	gamePluginMenu.offsetInBuffer[pos] = gamePluginMenu.bufOffset;
	strcpy((char*)(&(gamePluginMenu.buf[gamePluginMenu.bufOffset])), str);

	gamePluginMenu.count += 1;
	gamePluginMenu.bufOffset += len;
}

// add one cheat menu entry
void addCheatMenuEntry(char* str) {
	char buf[100];
	xsprintf(buf, "[ ] %s", str);
	addMenuEntry(buf);
}

int scanMenu() {
	u32 i;
	for (i = 0; i < gamePluginMenu.count; i++) {
		if (gamePluginMenu.state[i]) {
			gamePluginMenu.state[i] = 0;
			return i;
		}
	}
	return -1;
}

u32 updateMenu() {
	PLGLOADER_INFO *plgLoaderInfo = (void*)0x07000000;
	plgLoaderInfo->gamePluginPid = getCurrentProcessId();
	plgLoaderInfo->gamePluginMenuAddr = (u32)&gamePluginMenu;

	u32 ret = 0;
	u32 hProcess;
	u32 homeMenuPid = plgGetIoBase(5);

	if (homeMenuPid == 0) {
		return 1;
	}

	ret = svc_openProcess(&hProcess, homeMenuPid);
	if (ret != 0) {
		return ret;
	}

	copyRemoteMemory( hProcess, &(plgLoaderInfo->gamePluginPid), CURRENT_PROCESS_HANDLE,  &(plgLoaderInfo->gamePluginPid), 8);

	final:
	svc_closeHandle(hProcess);
	return ret;
}
