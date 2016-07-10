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
  static const u32 weeds[] = {
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
  // define flowers (include wilted)
  static const u16 flowers[] = {
    // src, replace
    0x009F, 0x009F, // Red Tulips
    0x00A0, 0x00A0, // White Tulips
    0x00A1, 0x00A1, // Yellow Tulips
    0x00A2, 0x00A2, // Pink Tulips
    0x00A3, 0x00A3, // Purple Tulips
    0x00A4, 0x00A4, // Black Tulips
    0x00A5, 0x00A5, // Orange Tulips
    0x00A6, 0x00A6, // White Pansies
    0x00A7, 0x00A7, // Yellow Pansies
    0x00A8, 0x00A8, // Red Pansies
    0x00A9, 0x00A9, // Purple Pansies
    0x00AA, 0x00AA, // Orange Pansies
    0x00AB, 0x00AB, // Blue Pansies
    0x00AC, 0x00AC, // White Comsos
    0x00AD, 0x00AD, // Red Cosmos
    0x00AE, 0x00AE, // Sun Cosmos
    0x00AF, 0x00AF, // Pink Cosmos
    0x00B0, 0x00B0, // Orange Cosmos
    0x00B1, 0x00B1, // Black Cosmos
    0x00B2, 0x00B2, // Red Roses
    0x00B3, 0x00B3, // White Roses
    0x00B4, 0x00B4, // Yellow Roses
    0x00B5, 0x00B5, // Pink Roses
    0x00B6, 0x00B6, // Orange Roses
    0x00B7, 0x00B7, // Purple Roses
    0x00B8, 0x00B8, // Black Roses
    0x00B9, 0x00B9, // Blue Roses
    0x00BB, 0x00BB, // Red Carnations
    0x00BC, 0x00BC, // Pink Carnations
    0x00BD, 0x00BD, // White Carnations
    0x00BE, 0x00BE, // White Lilies
    0x00BF, 0x00BF, // Yellow Lilies
    0x00C0, 0x00C0, // Red Lilies
    0x00C1, 0x00C1, // Orange Lilies
    0x00C2, 0x00C2, // Pink Lilies
    0x00C3, 0x00C3, // Black Lilies
    0x00C4, 0x00C4, // Purple Violets
    0x00C5, 0x00C5, // Blue Violets
    0x00C6, 0x00C6, // White Violets
    0x00C7, 0x00C7, // Yellow Violets
    0x00C8, 0x00C8, // Jacob's Ladder
    0x00CE, 0x009F, // Red Tulips (Wilted)
    0x00CF, 0x00A0, // White Tulips (Wilted)
    0x00D0, 0x00A1, // Yellow Tulips (Wilted)
    0x00D1, 0x00A2, // Pink Tulips (Wilted)
    0x00D2, 0x00A3, // Purple Tulips (Wilted)
    0x00D3, 0x00A4, // Black Tulips (Wilted)
    0x00D4, 0x00A5, // Orange Tulips (Wilted)
    0x00D5, 0x00A6, // White Pansies (Wilted)
    0x00D6, 0x00A7, // Yellow Pansies (Wilted)
    0x00D7, 0x00A8, // Red Pansies (Wilted)
    0x00D8, 0x00A9, // Purple Pansies (Wilted)
    0x00D9, 0x00AA, // Orange Pansies (Wilted)
    0x00DA, 0x00AB, // Blue Pansies (Wilted)
    0x00DB, 0x00AC, // White Cosmos (Wilted)
    0x00DC, 0x00AD, // Red Cosmos (Wilted)
    0x00DD, 0x00AE, // Sun Cosmos (Wilted)
    0x00DE, 0x00AF, // Pink Cosmos (Wilted)
    0x00DF, 0x00B0, // Orange Cosmos (Wilted)
    0x00E0, 0x00B1, // Black Cosmos (Wilted)
    0x00E1, 0x00B2, // Red Roses (Wilted)
    0x00E2, 0x00B3, // White Roses (Wilted)
    0x00E3, 0x00B4, // Yellow Roses (Wilted)
    0x00E4, 0x00B5, // Pink Roses (Wilted)
    0x00E5, 0x00B6, // Orange Roses (Wilted)
    0x00E6, 0x00B7, // Purple Roses (Wilted)
    0x00E7, 0x00B8, // Black Roses (Wilted)
    0x00E8, 0x00B9, // Blue Roses (Wilted)
    0x00E9, 0x00BA, // Gold Roses (Wilted)
    0x00EA, 0x00BB, // Red Carnations (Wilted)
    0x00EB, 0x00BC, // Pink Carnations (Wilted)
    0x00EC, 0x00BD, // White Carnations (Wilted)
    0x00ED, 0x00BE, // White Lilies (Wilted)
    0x00EE, 0x00BF, // Yellow Lilies (Wilted)
    0x00EF, 0x00C0, // Red Lilies (Wilted)
    0x00F0, 0x00C1, // Orange Lilies (Wilted)
    0x00F1, 0x00C2, // Pink Lilies (Wilted)
    0x00F2, 0x00C3, // Black Lilies (Wilted)
    0x00F3, 0x00C4, // Purple Violets (Wilted)
    0x00F4, 0x00C5, // Blue Violets (Wilted)
    0x00F5, 0x00C6, // White Violets (Wilted)
    0x00F6, 0x00C7, // Yellow Violets (Wilted)
    0x00F7, 0x00C8, // Jacob's Ladder (Wilted)
  };

  int i;
  u32 address, item;

  // find all items in Town
  for(address = OFFSET_TOWN_ITEMS; address < OFFSET_TOWN_ITEMS + RANGE_TOWN_ITEMS; address += ITEM_BYTES){
    item = READU16(address);

    // find flowers
    for(i = 0; i < sizeof(flowers) / sizeof(u16); i += 2){
      if(item == flowers[i]){
        // replace item
        WRITEU16(address, flowers[i + 1]);

        // add water flag
        WRITEU16(address + 0x02, 0x4000);
        break;
      }
    }
  }
}

//
void growAllTrees(){
  // define trees
  static const u16 trees[] = {
    // src, replace
    0x003A, 0x003E, // Apple Tree (Growing 1)
    0x003B, 0x003E, // Apple Tree (Growing 2)
    0x003C, 0x003E, // Apple Tree (Growing 3)
    0x003D, 0x003E, // Apple Tree (Growing 4)
    0x003E, 0x003E, // Apple Tree
    0x003F, 0x003F, // Orange Tree (Growing 1)
    0x0040, 0x003F, // Orange Tree (Growing 2)
    0x0041, 0x003F, // Orange Tree (Growing 3)
    0x0042, 0x003F, // Orange Tree (Growing 4)
    0x0043, 0x003F, // Orange Tree
    0x0044, 0x0048, // Pear Tree (Growing 1)
    0x0045, 0x0048, // Pear Tree (Growing 2)
    0x0046, 0x0048, // Pear Tree (Growing 3)
    0x0047, 0x0048, // Pear Tree (Growing 4)
    0x0048, 0x0048, // Pear Tree
    0x0049, 0x004D, // Peach Tree (Growing 1)
    0x004A, 0x004D, // Peach Tree (Growing 2)
    0x004B, 0x004D, // Peach Tree (Growing 3)
    0x004C, 0x004D, // Peach Tree (Growing 4)
    0x004D, 0x004D, // Peach Tree
    0x004E, 0x0052, // Cherry Tree (Growing 1)
    0x005F, 0x0052, // Cherry Tree (Growing 2)
    0x0050, 0x0052, // Cherry Tree (Growing 3)
    0x0051, 0x0052, // Cherry Tree (Growing 4)
    0x0052, 0x0052, // Cherry Tree
    0x0005, 0x0039, // Dead Bamboo
    0x0006, 0x0026, // Dead Tree
    0x0022, 0x0026, // Tree (Growing 1)
    0x0023, 0x0026, // Tree (Growing 2)
    0x0024, 0x0026, // Tree (Growing 3)
    0x0025, 0x0026, // Tree (Growing 4)
    0x0026, 0x0026, // Tree
    0x0027, 0x002B, // cedar (growing 1)
    0x0028, 0x002B, // cedar (growing 2)
    0x0029, 0x002B, // cedar (growing 3)
    0x002A, 0x002B, // cedar (growing 4)
    0x002B, 0x002B, // cedar
    0x002C, 0x0030, // coconut palm tree (growing 1)
    0x002D, 0x0030, // coconut palm tree (growing 2)
    0x002E, 0x0030, // coconut palm tree (growing 3)
    0x002F, 0x0030, // coconut palm tree (growing 4)
    0x0030, 0x0030, // coconut palm tree
    0x0031, 0x0035, // banana palm tree (growing 1)
    0x0032, 0x0035, // banana palm tree (growing 2)
    0x0033, 0x0035, // banana palm tree (growing 3)
    0x0034, 0x0035, // banana palm tree (growing 4)
    0x0035, 0x0035, // banana palm tree
    0x0036, 0x0039, // bamboo (growing 1)
    0x0037, 0x0039, // bamboo (growing 2)
    0x0038, 0x0039, // bamboo (growing 3)
    0x0039, 0x0039, // bamboo
    0x0053, 0x0057, // durian tree (growing 1)
    0x0054, 0x0057, // durian tree (growing 2)
    0x0055, 0x0057, // durian tree (growing 3)
    0x0056, 0x0057, // durian tree (growing 4)
    0x0057, 0x0057, // durian tree
    0x0058, 0x005C, // lemon tree (growing 1)
    0x0059, 0x005C, // lemon tree (growing 2)
    0x005A, 0x005C, // lemon tree (growing 3)
    0x005B, 0x005C, // lemon tree (growing 4)
    0x005C, 0x005C, // lemon tree
    0x005D, 0x0061, // lychee tree (growing 1)
    0x005E, 0x0061, // lychee tree (growing 2)
    0x005F, 0x0061, // lychee tree (growing 3)
    0x0060, 0x0061, // lychee tree (growing 4)
    0x0061, 0x0061, // lychee tree
    0x0062, 0x0066, // mango tree (growing 1)
    0x0063, 0x0066, // mango tree (growing 2)
    0x0064, 0x0066, // mango tree (growing 3)
    0x0065, 0x0066, // mango tree (growing 4)
    0x0066, 0x0066, // mango tree
    0x0067, 0x006B, // persimmons tree (growing 1)
    0x0068, 0x006B, // persimmons tree (growing 2)
    0x0069, 0x006B, // persimmons tree (growing 3)
    0x006A, 0x006B, // persimmons tree (growing 4)
    0x006B, 0x006B, // persimmons tree
    0x006C, 0x0070, // money tree (growing 1)
    0x006D, 0x0070, // money tree (growing 2)
    0x006E, 0x0070, // money tree (growing 3)
    0x006F, 0x0070, // money tree (growing 4)
    0x0070, 0x0070, // money tree
    0x0080, 0x0082, // holly bush (growing 1)
    0x0081, 0x0082, // holly bush (growing 2)
    0x0082, 0x0082, // holly bush
    0x0083, 0x0085, // pink azalea bush (growing 1)
    0x0084, 0x0085, // pink azalea bush (growing 2)
    0x0085, 0x0085, // pink azalea bush
    0x0086, 0x0088, // white azalea bush (growing 1)
    0x0087, 0x0088, // white azalea bush (growing 2)
    0x0088, 0x0088, // white azalea bush
    0x0089, 0x008B, // blue hydrangea bush (growing 1)
    0x008A, 0x008B, // blue hydrangea bush (growing 2)
    0x008B, 0x008B, // blue hydrangea bush
    0x008C, 0x008E, // pink hydrangea bush (growing 1)
    0x008D, 0x008E, // pink hydrangea bush (growing 2)
    0x008E, 0x008E, // pink hydrangea bush
    0x008F, 0x0091, // red hibiscus bush (growing 1)
    0x0090, 0x0091, // red hibiscus bush (growing 2)
    0x0091, 0x0091, // red hibiscus bush
    0x0092, 0x0094, // yellow hibiscus bush (growing 1)
    0x0093, 0x0094, // yellow hibiscus bush (growing 2)
    0x0094, 0x0094, // yellow hibiscus bush
    0x0095, 0x0097, // sweet olive bush (growing 1)
    0x0096, 0x0097, // sweet olive bush (growing 2)
    0x0097, 0x0097, // sweet olive bush
  };

  int i;
  u32 address, item;

  // find all items in Town
  for(address = OFFSET_TOWN_ITEMS; address < OFFSET_TOWN_ITEMS + RANGE_TOWN_ITEMS; address += ITEM_BYTES){

    // READ16 means ignoring any flags
    item = READU16(address);

    // find trees
    for(i = 0; i < sizeof(trees) / sizeof(u16); i += 2){
      if(item == trees[i]){
        // replace
        WRITEU16(address, trees[i + 1]);

        // reset fruit flags
        // 0x0000 = with fruits
        // 0x0003 = no fruits
        // 0x0008 = perfect (0)
        WRITEU16(address + 0x02, 0x0000);
        break;
      }
    }

  }
}

void setAllFruitTreesPerfect(){
  // define fruit trees
  static const u16 trees[] = {
    // src, replace
    0x003E, // Apple Tree
    0x0043, // Orange Tree
    0x0048, // Pear Tree
    0x004D, // Peach Tree
    0x0052, // Cherry Tree
  };

  int i;
  u32 address, item;

  // find all items in Town
  for(address = OFFSET_TOWN_ITEMS; address < OFFSET_TOWN_ITEMS + RANGE_TOWN_ITEMS; address += ITEM_BYTES){

    // READ16 means ignoring any flags
    item = READU16(address);

    // find trees
    for(i = 0; i < sizeof(trees) / sizeof(u16); i++){
      if(item == trees[i]){
        // enable perfect flag
        WRITEU16(address + 0x02, 0x0808);
        break;
      }
    }

  }
}

//*********************************
// PLAYER SECTION
//*********************************

//
void setPlayerSpeedFaster(){
  const u32 defaultVelocity = 0x41A79DB3;
  const u32 currentVelocityAddress = 0x1736AA3C;

  u32 currentVelocity  = READU32(currentVelocityAddress);

  //
  if(currentVelocity > defaultVelocity){
    WRITEU32(currentVelocityAddress, defaultVelocity);
  }
  else if(currentVelocity > 0){
    WRITEU32(currentVelocityAddress, currentVelocity + 0x00100000);
  }
}
