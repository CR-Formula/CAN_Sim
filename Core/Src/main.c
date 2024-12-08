/************************************************
* @file    main.c 
* @author  APBashara
* @date    9/2024
* 
* @brief   Main Code to run Tasks and Setup Peripherals
***********************************************/

#include "main.h"

/* Global Variables ---------------------------------------------------------*/

/* Function Calls -----------------------------------------------------------*/
void main() {
  uint8_t Task_Status = 1;

  // Initialize Hardware
  Sysclk_168();
  LED_Init();
  CAN1_Init();
  CAN_Filters_Init();
  CAN_Start();
  GPIO_Init();
  USART3_Init();

  // Create FreeRTOS Tasks
  Task_Status &= xTaskCreate(Status_LED, "Status_Task", 128, NULL, 5, NULL);
  Task_Status &= xTaskCreate(CAN_Task1, "CAN_Task", 256, NULL, 1, NULL);
  Task_Status &= xTaskCreate(CAN_Task2, "CAN_Task", 256, NULL, 2, NULL);
  Task_Status &= xTaskCreate(CAN_Task3, "CAN_Task", 256, NULL, 3, NULL);
#ifdef DEBUG
  Task_Status &= xTaskCreate(Collect_Stats, "Stats_Task", 512, NULL, 5, NULL);
#endif

  if (Task_Status != pdPASS) {
    Error_Handler();
  }

  vTaskStartScheduler(); // Start FreeRTOS Scheduler

  while(1);
}

void Status_LED() {
  const TickType_t StatusFrequency = 1000;
  TickType_t xLastWakeTime = xTaskGetTickCount();

  while(1) {
    Toggle_Pin(GPIOC, STATUS_LED_PIN);
    vTaskDelayUntil(&xLastWakeTime, StatusFrequency);
  }
}

void CAN_Task1() {
  volatile CAN_Frame tFrame = {
    .id = 0x048,
    .dlc = 8,
    .rtr = CAN_RTR_Data,
    .data = {0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8}
  };

  const TickType_t CANFrequency = 50;
  TickType_t xLastWakeTime = xTaskGetTickCount();

  while(1) {
    for (uint8_t i = 0; i < 8; i++) {
      tFrame.data[i]++;
    }
    CAN_Transmit(CAN1, &tFrame);
  }
}

void CAN_Task2() {
  volatile CAN_Frame tFrame = {
    .id = 0x148,
    .dlc = 8,
    .rtr = CAN_RTR_Data,
    .data = {0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8}
  };

  const TickType_t CANFrequency = 50;
  TickType_t xLastWakeTime = xTaskGetTickCount();

  while(1) {
    for (uint8_t i = 0; i < 8; i++) {
      tFrame.data[i]++;
    }
    CAN_Transmit(CAN1, &tFrame);
  }
}

void CAN_Task3() {
  volatile CAN_Frame tFrame = {
    .id = 0x069,
    .dlc = 8,
    .rtr = CAN_RTR_Data,
    .data = {0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8}
  };

  const TickType_t CANFrequency = 1000;
  TickType_t xLastWakeTime = xTaskGetTickCount();

  while(1) {
    for (uint8_t i = 0; i < 8; i++) {
      tFrame.data[i]++;
    }
    CAN_Transmit(CAN1, &tFrame);
  }
}

#ifdef DEBUG
void Collect_Stats() {
  const TickType_t StatsFrequency = 1000;
  TickType_t xLastWakeTime = xTaskGetTickCount();
  uint8_t StatsBuffer[64*5];

  while(1) {
    vTaskGetRunTimeStats(&StatsBuffer);
    send_String(USART3, &StatsBuffer);
    vTaskDelayUntil(&xLastWakeTime, StatsFrequency);
  }
}
#endif

void Error_Handler() {
  Set_Pin(GPIOC, STATUS_LED_PIN);
  while(1);
}

void EXTI9_5_IRQHandler() {
  if (EXTI->PR & (0x1 << 9)) {
    EXTI->PR |= (0x1 << 9); // Clear the status bit
    // Set Flag for Lora Recv
  }
}