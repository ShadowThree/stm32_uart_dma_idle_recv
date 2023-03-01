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
#define LOG_BY_UART_IT      0       // send by interrupt seems NOT better. If want use IT mode, need enable in cubeMx and regenerate the project.

    uint8_t logBuf[LOG_BUF_LEN];
    
    // if last print NOT finish, this print will output nothing
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
        
        #if LOG_BY_UART_IT
        HAL_UART_Transmit_IT(LOG_UART, logBuf, strlen((const char*)logBuf));        // send in interrupt mode, maybe can change to DMA mode
        #else
        HAL_UART_Transmit(LOG_UART, logBuf, strlen((const char*)logBuf), 1000);   // send in block mode
        #endif
        
        #if LOG_BY_UART_IT
        while(LOG_UART->gState == HAL_UART_STATE_BUSY_TX);              // wait to send finish. Can NOT wait before last HAL_UART_Transmit_IT(), but why?
        //while(HAL_UART_GetState(LOG_UART) == HAL_UART_STATE_BUSY_TX);   // same as last line
        #endif
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
