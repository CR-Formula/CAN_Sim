/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion ------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes -----------------------------------------------------------------*/
// OS Specific Includes
#include "FreeRTOS.h" /* Must come first. */
#include "task.h" /* RTOS task related API prototypes. */
#include "queue.h" /* RTOS queue related API prototypes. */
#include "timers.h" /* Software timer related API prototypes. */
#include "semphr.h" /* Semaphore related API prototypes. */
// Hardware Specific Includes
#include "stm32f4xx_hal.h"
#include "stm32f415xx.h"

#include <stdint.h>

#ifndef GPIO_H
    #define GPIO_H
    #include "gpio.h"
#endif
#include "can.h"
#include "timer.h"
#include "uart.h"

#define DEBUG

/* Macros  ------------------------------------------------------------------*/
#define STATUS_LED_PIN              13

/* Data Structures  ---------------------------------------------------------*/

/* Functions prototypes -----------------------------------------------------*/

/**
 * @brief Handles Systems Errors
 * @note Holds Status LED on until reset
 * @todo Create Blink status codes for errors
 */
void Error_Handler(void);

/**
 * @brief Thread for blinking the status led
 */
void Status_LED();

/**
 * @brief Test message 1
 */
void CAN_Task1();

/**
 * @brief Test message 2
 */
void CAN_Task2();

/**
 * @brief Test message 3
 */
void CAN_Task3();

/**
 * @brief Thread for collecting system statistics
 * @note For Debug only
 */
void Collect_Stats();

/**
 * @brief Main Function to start FreeRTOS and initialize peripherals
 * 
 */
void main();

#endif /* __MAIN_H */
