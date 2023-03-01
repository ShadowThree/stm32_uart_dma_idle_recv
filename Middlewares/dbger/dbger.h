/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    dbger.h
  * @brief   This file provides code for outputing the LOG by uart or RTT.
             The priority levels as below:
                1.[AST]:Assert      (Highest)
                2.[ERR]:Error
                3.[WAR]:Warnning
                4.[INF]:Info
                5.[DBG]:Debug
                6.[VBS]:Verbose     (Lowest)
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 shadowthreed@gmail.com
  * All rights reserved.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/**
  ******* HOW TO USE *********
  * 0. add the files in this folder to current project
  * 1. #include "dbger.h"
  # 2. change the config in dbger.h: LOG_ENABLE, LOG_BY_RTT, LOG_LEVEL, LOG_COLOR_ENABLE. LOG_BUF_LEN & LOG_UART if LOG_BY_UART is 1.
  * 3. call LOG_INIT() at init;     // Just need call once
  * 4. LOG_DBG("HelloWorld! number[%d]\r\n", 1);
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DBGER_H__
#define __DBGER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define LOG_ENABLE          1
#define LOG_BY_RTT          1
#define LOG_BY_UART         (!LOG_BY_RTT)
#define LOG_LEVEL           6       // the priority less than or queal to LOG_LEVEL will be output
#define LOG_COLOR_ENABLE    1

#if LOG_ENABLE
  #include <string.h>
  #define __FILENAME__        (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)      // strrchr(str, ch): return the last position of ch in str, or NULL
#endif

#if LOG_ENABLE && LOG_COLOR_ENABLE    // set LOG color
  #define COLOR_RED       "\033[31m"
  #define COLOR_PINK      "\033[35m"
  #define COLOR_YELLOW    "\033[33m"
  #define COLOR_GREEN     "\033[32m"
  #define COLOR_GRAY      "\033[37m"
  #define COLOR_DEFAULT   "\033[0m"       // off, default white
#else
  #define COLOR_RED
  #define COLOR_PINK
  #define COLOR_YELLOW
  #define COLOR_GREEN
  #define COLOR_GRAY
  #define COLOR_DEFAULT
#endif

#if LOG_ENABLE && LOG_BY_UART

  #include <stdarg.h>
  #include <stdio.h>
  #include "usart.h"
  #define LOG_BUF_LEN       (256)
  #define LOG_UART          (&huart3)
  
  #define LOG_INIT()                MX_USART3_UART_Init();
  #define LOG(level, fmt, ...)      log_print(level, fmt, ##__VA_ARGS__)
  
  #define LOG_AST(fmt, ...)         LOG(1, COLOR_RED     "[AST:%s:%d] " fmt, __FILENAME__, __LINE__, ##__VA_ARGS__)
  #define LOG_ERR(fmt, ...)         LOG(2, COLOR_PINK    "[ERR:%s:%d] " fmt, __FILENAME__, __LINE__, ##__VA_ARGS__)
  #define LOG_WAR(fmt, ...)         LOG(3, COLOR_YELLOW  "[WAR:%s:%d] " fmt, __FILENAME__, __LINE__, ##__VA_ARGS__)
  #define LOG_INF(fmt, ...)         LOG(4, COLOR_DEFAULT "[INF] "       fmt, ##__VA_ARGS__)
  #define LOG_DBG(fmt, ...)         LOG(5, COLOR_GREEN   "[DBG] "       fmt, ##__VA_ARGS__)
  #define LOG_VBS(fmt, ...)         LOG(6, COLOR_GRAY                   fmt, ##__VA_ARGS__)
  
  extern uint8_t logBuf[LOG_BUF_LEN];
  
#elif LOG_ENABLE && LOG_BY_RTT
  #include "SEGGER_RTT.h"
  #define LOG_INIT()                SEGGER_RTT_Init()
  #define LOG(level, fmt, ...)      do {                                \
                                        if(level <= 3) {                \
                                            SEGGER_RTT_SetTerminal(0);  \
                                        } else if(level <= 4) {         \
                                            SEGGER_RTT_SetTerminal(1);  \
                                        } else {                        \
                                            SEGGER_RTT_SetTerminal(2);  \
                                        }                               \
                                        log_print(level, fmt, ##__VA_ARGS__);   \
                                    } while(0)
  
  #define LOG_AST(fmt, ...)         LOG(1, COLOR_RED     "[AST:%s:%d] " fmt, __FILENAME__, __LINE__, ##__VA_ARGS__)
  #define LOG_ERR(fmt, ...)         LOG(2, COLOR_PINK    "[ERR:%s:%d] " fmt, __FILENAME__, __LINE__, ##__VA_ARGS__)
  #define LOG_WAR(fmt, ...)         LOG(3, COLOR_YELLOW  "[WAR:%s:%d] " fmt, __FILENAME__, __LINE__, ##__VA_ARGS__)
  #define LOG_INF(fmt, ...)         LOG(4, COLOR_DEFAULT "[INF] "       fmt, ##__VA_ARGS__)
  #define LOG_DBG(fmt, ...)         LOG(5, COLOR_GREEN   "[DBG] "       fmt, ##__VA_ARGS__)
  #define LOG_VBS(fmt, ...)         LOG(6, COLOR_GRAY                   fmt, ##__VA_ARGS__)
  
#elif !LOG_ENABLE

  #define LOG_INIT()
  #define LOG_AST(fmt, ...)
  #define LOG_ERR(fmt, ...)
  #define LOG_WAR(fmt, ...)
  #define LOG_INF(fmt, ...)
  #define LOG_DBG(fmt, ...)
  #define LOG_VBS(fmt, ...)

#endif

extern void log_print(uint8_t level, char* fmt, ...);

#ifdef __cplusplus
}
#endif

#endif /* __DBGER_H__ */
