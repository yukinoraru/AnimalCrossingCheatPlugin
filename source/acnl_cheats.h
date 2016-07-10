#ifndef ACNL_CHEATS_H
#define ACNL_CHEATS_H

#include "helpers.h"

// ITEM
void duplicateItem();

// ENVIRONMENT
void pullAllWeeds();
void waterAllFlowers();
void growAllTrees();
void setAllFruitTreesPerfect();

// PLAYER
void setPlayerSpeedFaster();

// DEFINE CONSTANTS
#define OFFSET_TOWN_ITEMS 0x1609D158
#define ITEM_BYTES 0x04
#define RANGE_TOWN_ITEMS 0x5000

#endif
