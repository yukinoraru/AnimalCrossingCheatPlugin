#include "helpers.h"

void duplicateItem(){
  u32 tmp = READU32(0x160562d0);
  WRITEU32(0x160562d4, tmp);
}
