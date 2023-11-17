# 电控部作业链

- **我是纯废物，框架配不明白**
- 没配对的部分：
  1. TIM3 这里使用 TIM3 作为 ADC 的触发源以在指定频率下开启 ADC 转换。将 Trigger Event Selection 改为 Update Event。
  2. TIM4
`TIM4` 作为驱动蜂鸣器的 PWM 输出，其输出频率决定了蜂鸣器频率，输出占空比决定了输出功率（音量）。令蜂鸣器输出频率为$f_{buzzer}$，$f_{buzzer}=\frac{f_{APB1timerclock}}{(Prescaler+1)(CounterPeriod+1)}$。这里可以开启 `auto reload preload`

  3. `USART3` 连接到 `SBUS/DBUS` 协议的接收机，请根据遥控器驱动教程配置。
