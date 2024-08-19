#include "bkp.h"

void bkp_init()
{
    RCC->APB1ENR |= 0x01<<27;   /* BKPEN */
    RCC->APB1ENR |= 0x01<<28;   /* PWREN */
    PWR->CR |= 0x01<<8;         /* DBP */
}
void bkp_rite(uint32_t DRx, uint32_t Data)
{
  uint32_t tmp = 0U;

  tmp = (uint32_t)BKP_BASE;
  tmp += (DRx * 4U);

  *(uint32_t *) tmp = (Data & 0xFFFF);
}

