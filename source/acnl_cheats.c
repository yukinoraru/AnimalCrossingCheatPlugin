#include "helpers.h"

void duplicateItem(){
  u32 tmp = READU32(0x15FBEAD0);
  WRITEU32(0x15FBEAD4, tmp);
}
