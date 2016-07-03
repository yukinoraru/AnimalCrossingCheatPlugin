#include "helpers.h"
#include "menu.h"

u32 threadStack[0x1000];
Handle fsUserHandle;
FS_archive sdmcArchive;

u8 cheatEnabled[64];
int isNewNtr = 0;
u32 currentKeyState = 0;

//
void handleCheats(u32 key) {
	// TODO: handle your own cheat items
	// if (cheatEnabled[0]) {
	// 	WRITEU32(0x00720C1C, 0x0F40C3878);
	// }
}

// update the menu status
void updateCheatEnableDisplay(int id) {
	gamePluginMenu.buf[gamePluginMenu.offsetInBuffer[id] + 1] = cheatEnabled[id] ? 'X' : ' ';
}

// this function will be called when the state of cheat item changed
void onCheatItemChanged(int id, int enable) {
	// TODO: handle on cheat item is select or unselected
}

// scan and handle events
void scanCheatMenu() {
	int ret = scanMenu();
	if (ret != -1) {
		cheatEnabled[ret] = !cheatEnabled[ret];
		updateCheatEnableDisplay(ret);
		onCheatItemChanged(ret, cheatEnabled[ret]);
	}
}

// init
void initCheatMenu() {
	initMenu();

	// TODO :
	// addMenuEntry("HEADER1")
	// addCheatMenuEntry("  UHUHU");

	updateMenu();
}

// entry point
void gamePluginEntry() {
	u32 ret, key;
	INIT_SHARED_FUNC(plgGetIoBase, 8);
	INIT_SHARED_FUNC(copyRemoteMemory, 9);
	// wait for game starts up (5 seconds)
	svc_sleepThread(5000000000);

	if (((NS_CONFIG*)(NS_CONFIGURE_ADDR))->sharedFunc[8]) {
		isNewNtr = 1;
	} else {
		isNewNtr = 0;
	}

	if (isNewNtr) {
		IoBasePad = plgGetIoBase(IO_BASE_PAD);
	}

	initCheatMenu();

	while (1) {
		svc_sleepThread(100000000);

		scanCheatMenu();

		//
		updateKeyState();
		handleCheats(currentKeyState);
	}
}
