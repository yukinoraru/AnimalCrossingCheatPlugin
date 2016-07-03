#include "helpers.h"
#include "menu.h"

u32 threadStack[0x1000];
Handle fsUserHandle;
FS_archive sdmcArchive;

u8 cheatEnabled[64];
int isNewNtr = 0;

// detect language (0: english)
int detectLanguage() {
	// unimplemented
	return 0;
}

// this function will be called when the state of cheat item changed
void onCheatItemChanged(int id, int enable) {
	// TODO: handle on cheat item is select or unselected


}

// freeze the value
void freezeCheatValue() {
	if (cheatEnabled[0]) {
		WRITEU16(0x00720C1C, 0x0F40C3878);
	}
	if (cheatEnabled[1]) {
		WRITEU16(0x00720C20, 0x0F405900);
	}
	if (cheatEnabled[2]) {
		WRITEU16(0x00720CC4, 0x0F40C3878);
	}
	if (cheatEnabled[3]) {
		WRITEU16(0x00720B84, 0x00000014);
	}
	if (cheatEnabled[4]) {
		WRITEU16(0x00720B44, 0x00000014);
	}
	if (cheatEnabled[5]) {
		WRITEU16(0x00720B5C, 0x00000014);
	}
	if (cheatEnabled[6]) {
		WRITEU16(0x00720B94, 0x00000014);
	}
	if (cheatEnabled[7]) {
		WRITEU16(0x00720B64, 0x00000014);
	}
	// TODO: handle your own cheat items
}

// update the menu status
void updateCheatEnableDisplay(id) {
	gamePluginMenu.buf[gamePluginMenu.offsetInBuffer[id] + 1] = cheatEnabled[id] ? 'X' : ' ';
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
	addCheatMenuEntry("Infinite HP");
	addCheatMenuEntry("Infinite SP");
	addCheatMenuEntry("9999 Max HP");
	addCheatMenuEntry("Max Magic Skill");
	addCheatMenuEntry("Max Wind Magic");
	addCheatMenuEntry("Max Earth Magic");
	addCheatMenuEntry("Max Water Magic");
	addCheatMenuEntry("Max Fire Magic");
	// TODO: Add your own menu entries

	updateMenu();
}

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
		freezeCheatValue();
	}
}
