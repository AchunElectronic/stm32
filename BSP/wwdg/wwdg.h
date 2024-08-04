#ifndef __WWDG_H__
#define __WWDG_H__

#include "sys.h"

void wwdg_init(uint32_t psc,uint8_t counter, uint8_t window);
void wwdg_feed(void);

#endif
