#ifndef __IWDG_H__
#define __IWDG_H__

#include "sys.h"

void iwdg_init(uint16_t ms);
void iwdg_feed(void);

#endif

