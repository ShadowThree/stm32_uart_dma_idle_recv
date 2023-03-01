/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED0_RED_Pin GPIO_PIN_9
#define LED0_RED_GPIO_Port GPIOD
#define LED1_Pin GPIO_PIN_10
#define LED1_GPIO_Port GPIOD
#define LED2_Pin GPIO_PIN_11
#define LED2_GPIO_Port GPIOD
#define UART1_Tx_CMD_J2_Pin GPIO_PIN_9
#define UART1_Tx_CMD_J2_GPIO_Port GPIOA
#define UART1_Rx_CMD_J2_Pin GPIO_PIN_10
#define UART1_Rx_CMD_J2_GPIO_Port GPIOA
#define UART3_Tx_LOG_J1_Pin GPIO_PIN_10
#define UART3_Tx_LOG_J1_GPIO_Port GPIOC
#define UART3_Rx_LOG_J1_Pin GPIO_PIN_11
#define UART3_Rx_LOG_J1_GPIO_Port GPIOC
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
