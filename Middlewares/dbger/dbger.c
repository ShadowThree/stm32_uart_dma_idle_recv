/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    dbger.c
  * @brief   This file provides code for realise the log priority.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "dbger.h"

#if LOG_ENABLE && LOG_BY_UART

    uint8_t logBuf[LOG_BUF_LEN];
    
    void log_print(uint8_t level, char* fmt, ...)
    {
        if(level > LOG_LEVEL) {
            return;
        }
        
        int ret;
        va_list ParamList;

        va_start(ParamList, fmt);
        ret = vsprintf((char*)logBuf, fmt, ParamList);
        va_end(ParamList);
        
        if(ret < 0) {   // vsprintf() error
            return;
        }
        
        //HAL_UART_Transmit(LOG_UART, logBuf, strlen((const char*)logBuf), 1000);   // send in block mode
        HAL_UART_Transmit_IT(LOG_UART, logBuf, strlen((const char*)logBuf));        // send in interrupt mode, maybe can change to DMA mode
        
        while(LOG_UART->gState == HAL_UART_STATE_BUSY_TX);              // wait to send finish.
        //while(HAL_UART_GetState(LOG_UART) == HAL_UART_STATE_BUSY_TX);   // same as last line
    }
#elif LOG_ENABLE && LOG_BY_RTT
    
    void log_print(uint8_t level, char* fmt, ...)
    {
        if(level > LOG_LEVEL) {
            return;
        }
        
        int ret;
        va_list ParamList;

        va_start(ParamList, fmt);
        ret = SEGGER_RTT_vprintf(0, fmt, &ParamList);
        va_end(ParamList);
        
        if(ret < 0) {
            // TODO:
        }
    }
    
#endif
