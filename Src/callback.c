//
// Created by cwlm on 2023/11/23.
//
#include "usart.h"
#include "../Inc/RemoteControl.h"

extern volatile uint8_t sbus_rx_buf[RC_FRAME_LENGTH];
extern RC_Ctl_t rC_ctrl;

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size) {
    if (huart->Instance == USART3) {
        HAL_UART_Transmit(&huart3, (const uint8_t *) &rC_ctrl, 18, 100);
        sbus_to_rc();
        HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_RESET);
    }
}
