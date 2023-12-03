//
// Created by cwlm on 2023/11/17.
//

#include "../Inc/RemoteControl.h"

volatile uint8_t sbus_rx_buf[RC_FRAME_LENGTH];
RC_Ctl_t rC_ctrl;

extern UART_HandleTypeDef huart3;

void RC_init(void) {
    HAL_UARTEx_ReceiveToIdle_DMA(&huart3, (uint8_t *) sbus_rx_buf, RC_FRAME_LENGTH);
}

void sbus_to_rc() {

    uint16_t ch[4];

    ch[0] = (sbus_rx_buf[0] | (sbus_rx_buf[1] << 8)) & 0x07ff; //!< Channel 0
    ch[1] = ((sbus_rx_buf[1] >> 3) | (sbus_rx_buf[2] << 5)) & 0x07ff; //!< Channel 1
    ch[2] = ((sbus_rx_buf[2] >> 6) | (sbus_rx_buf[3] << 2) | //!< Channel 2
                         (sbus_rx_buf[4] << 10)) & 0x07ff;
    ch[3] = ((sbus_rx_buf[4] >> 1) | (sbus_rx_buf[5] << 7)) & 0x07ff; //!< Channel 3

    // Data Normalization
    if (ch[0])
        rC_ctrl.rc.ch[0] = (float) (ch[0] - RC_CH_VALUE_OFFSET) / (float) (RC_CH_VALUE_MAX - RC_CH_VALUE_OFFSET);
    if (ch[1])
        rC_ctrl.rc.ch[1] = (float) (ch[1] - RC_CH_VALUE_OFFSET) / (float) (RC_CH_VALUE_MAX - RC_CH_VALUE_OFFSET);
    if (ch[2])
        rC_ctrl.rc.ch[2] = (float) (ch[2] - RC_CH_VALUE_OFFSET) / (float) (RC_CH_VALUE_MAX - RC_CH_VALUE_OFFSET);
    if (ch[3])
        rC_ctrl.rc.ch[3] = (float) (ch[3] - RC_CH_VALUE_OFFSET) / (float) (RC_CH_VALUE_MAX - RC_CH_VALUE_OFFSET);

    rC_ctrl.rc.s[0] = ((sbus_rx_buf[5] >> 4) & 0x0003); //!< Switch left
    rC_ctrl.rc.s[1] = ((sbus_rx_buf[5] >> 4) & 0x000C) >> 2; //!< Switch right

    rC_ctrl.mouse.x = sbus_rx_buf[6] | (sbus_rx_buf[7] << 8); //!< Mouse X axis
    rC_ctrl.mouse.y = sbus_rx_buf[8] | (sbus_rx_buf[9] << 8); //!< Mouse Y axis
    rC_ctrl.mouse.z = sbus_rx_buf[10] | (sbus_rx_buf[11] << 8); //!< Mouse Z axis
    rC_ctrl.mouse.press_l = sbus_rx_buf[12]; //!< Mouse Left Is Press ?
    rC_ctrl.mouse.press_r = sbus_rx_buf[13]; //!< Mouse Right Is Press ?
    rC_ctrl.key.v = sbus_rx_buf[14] | (sbus_rx_buf[15] << 8); //!< KeyBoard value
}
