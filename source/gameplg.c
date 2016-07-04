#include "helpers.h"
#include "menu.h"
#include "acnl_cheats.h"

u32 threadStack[0x1000];
Handle fsUserHandle;
FS_archive sdmcArchive;

u8 cheatEnabled[64];
int isNewNtr = 0;
u32 currentKeyState = 0;

// WARN: strong dependency to initCheatMenu
// these enums are keys for cheatEnabled array
enum menuEnum
{
	//
	headerItem,
		menuDupeItem,

	//
	headerEnvironment,
		menuPullingWeeds,
};

int headerIds[] = {
	headerItem,
	headerEnvironment,
};

// initalize main menu
void initCheatMenu() {
	initMenu();

	addMenuEntry("**ITEM**");
	addCheatMenuEntry("  dup item: slot1->2");

	addMenuEntry("**ENVIRONMENT**");
	addCheatMenuEntry("  pulling all weeds");

	updateMenu();
}

// update the menu status
void updateCheatEnableDisplay(int id) {
	// +1 means inside the checkbox -> [ ]
	gamePluginMenu.buf[gamePluginMenu.offsetInBuffer[id] + 1] = cheatEnabled[id] ? 'X' : ' ';
}

// core logic
void handleCheats(u32 key) {
	//
	if(cheatEnabled[menuDupeItem]) {
			if(currentKeyState == BUTTON_R){
				duplicateItem();
			}
	//
	} else if(cheatEnabled[menuPullingWeeds]) {
		//TODO:
	}
}

//
void disableCheat(int id)
{
	cheatEnabled[id] = false;
	updateCheatEnableDisplay(id);
}

// this function will be called when the state of cheat item changed
void onCheatItemChanged(int id, int enable) {
	if(id == menuDupeItem && enable == true){
			disableCheat(menuDupeItem);
	}
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

// return true if id is a header menu
bool isHeader(int id) {
	int i;
	for(i = 0; i < sizeof(headerIds) / sizeof(int); i++){
		if (headerIds[i] == id)
			return true;
	}
	return false;
}

// scan and handle events
void scanCheatMenu() {
	int ret = scanMenu();
	if (ret != -1 && !isHeader(ret)) {
		cheatEnabled[ret] = !cheatEnabled[ret];
		updateCheatEnableDisplay(ret);
		onCheatItemChanged(ret, cheatEnabled[ret]);
	}
}

// entry point
void gamePluginEntry() {
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

	//
	initCheatMenu();

	while (1) {
		svc_sleepThread(100000000);

		//
		scanCheatMenu();

		//
		updateKeyState();

		//
		handleCheats(currentKeyState);
	}
}
