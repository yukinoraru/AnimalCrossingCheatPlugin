#include "acnl_cheats.h"

//*********************************
// ITEM SECTION
//*********************************

//
void duplicateItem(){
  u32 tmp = READU32(0x160562d0);
  WRITEU32(0x160562d4, tmp);
}


//*********************************
// ENVIRONMENT SECTION
//*********************************

//
void pullAllWeeds(){
  // define weeds
  u32 weeds[] = {
    0x0000007C, // Weed 1
    0x0000007D, // Weed 2
    0x0000007E, // Weed 3
    0x0000007F, // Weed 4
    0x000000CB, // Dandelion Puff
    0x000000CC, // Clovers (Weed)
    0x000000CD, // Rafflesia
    0x000000F8, // Rafflesia (Wilted)
  };

  int i;
  u32 address, item;

  // find all items in Town
  for(address = OFFSET_TOWN_ITEMS; address < OFFSET_TOWN_ITEMS + RANGE_TOWN_ITEMS; address += ITEM_BYTES){
    item = READU32(address);

    // find weeds
    for(i = 0; i < sizeof(weeds) / sizeof(u32); i++){
      if(item == weeds[i]){
        // replace weeds to nothing(=0x7FFE)
        WRITEU32(address, 0x00007FFE);
        break;
      }
    }
  }
}

//
void waterAllFlowers(){

}

//
void growAllTrees(){

}

//*********************************
// PLAYER SECTION
//*********************************

//
void setPlayerSpeedFaster(){

}
