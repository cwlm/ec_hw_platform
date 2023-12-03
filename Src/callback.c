//
// Created by cwlm on 2023/11/23.
//
#include "usart.h"
#include "../Inc/RemoteControl.h"

extern volatile uint8_t sbus_rx_buf[RC_FRAME_LENGTH];
extern RC_Ctl_t rC_ctrl;

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size) {
    if (huart->Instance == USART3) {
        sbus_to_rc();
        HAL_UARTEx_ReceiveToIdle_DMA(&huart3, (uint8_t *) sbus_rx_buf, RC_FRAME_LENGTH);
        HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_RESET);
    }
}
