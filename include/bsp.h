/**
  ===========================
  * @file    : bsp.h
  * @brief   : BSP 接口声明
  * @author  : 白狼
  ===========================
  */

#ifndef __BSP_H
#define __BSP_H

void BSP_Init(void);
void BSP_SetLED(int state);
void BSP_DelayMS(int ms);

#endif
