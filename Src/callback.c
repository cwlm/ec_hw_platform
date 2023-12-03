//
// Created by cwlm on 2023/11/23.
//
#include "usart.h"
#include "../Inc/RemoteControl.h"

extern volatile uint8_t sbus_rx_buf[RC_FRAME_LENGTH];
extern RC_Ctl_t rC_ctrl;

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size) {
    if (huart->Instance == USART3) {
		    HAL_UARTEx_ReceiveToIdle_DMA(&huart3, (uint8_t *) sbus_rx_buf, RC_FRAME_LENGTH);
        sbus_to_rc(sbus_rx_buf, &rC_ctrl);
    }
}
