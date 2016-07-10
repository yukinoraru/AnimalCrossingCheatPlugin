#include "helpers.h"
#include "menu.h"
#include "acnl_cheats.h"

u32 threadStack[0x1000];
Handle fsUserHandle;
FS_archive sdmcArchive;

u8 cheatEnabled[64];
u32 currentKeyState = 0;

// these enums are keys for cheatEnabled array
enum menuEnum
{
	//
	headerItem,
		menuDuplicateItem,

	//
	headerEnvironment,
		menuPullAllWeeds,
		menuWaterAllFlowers,
		menuGrowAllTrees,
		menuPerfectAllFruits,

  //
	headerPlayer,
		menuPlayerSpeed,

};

int menuHeaderIds[] = {
	headerItem,
	headerEnvironment,
	headerPlayer,
};

// initalize main menu
void initCheatMenu() {
	initMenu();

	addMenuEntry("ITEM");
	addCheatMenuEntry(" dup item: slot1 -> 2");

	addMenuEntry("ENVIRONMENT");
	addCheatMenuEntry(" pulling all weeds");
	addCheatMenuEntry(" water all flowers");
	addCheatMenuEntry(" grow all trees");
	addCheatMenuEntry(" all fruits to perfect");

	addMenuEntry("PLAYER");
	addCheatMenuEntry(" super fast dash");

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
	if(cheatEnabled[menuDuplicateItem]) {
		if(key == BUTTON_R){
			duplicateItem();
		}

	//
	} else if(cheatEnabled[menuPullAllWeeds]) {
		if(key == (BUTTON_L | BUTTON_X)){
			pullAllWeeds();
			waitKeyUp();
		}

	//
	} else if(cheatEnabled[menuWaterAllFlowers]){
		if(key == (BUTTON_L | BUTTON_Y)){
			waterAllFlowers();
			waitKeyUp();
		}

	//
	} else if(cheatEnabled[menuGrowAllTrees]){
		if(key == (BUTTON_L | BUTTON_B)){
			growAllTrees();
			waitKeyUp();
		}

	//
	} else if(cheatEnabled[menuPerfectAllFruits]){
		if(key == (BUTTON_L | BUTTON_A)){
			setAllFruitTreesPerfect();
			waitKeyUp();
		}

	//
	} else if(cheatEnabled[menuPlayerSpeed]){
		if(key == BUTTON_B){
			setPlayerSpeedFaster();
		}
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
	// if(id == menuPullAllWeeds && enable == true){
	// 		disableCheat(menuDuplicateItem);
	// }
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
bool isHeaderMenu(int id) {
	int i;
	for(i = 0; i < sizeof(menuHeaderIds) / sizeof(int); i++){
		if (menuHeaderIds[i] == id)
			return true;
	}
	return false;
}

// scan and handle events
void scanCheatMenu() {
	int ret = scanMenu();

	if (ret != -1 && !isHeaderMenu(ret)) {
		cheatEnabled[ret] = !cheatEnabled[ret];

		updateCheatEnableDisplay(ret);

		onCheatItemChanged(ret, cheatEnabled[ret]);
	}
}

// entry point
void gamePluginEntry() {
	int isNewNtr;

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
