# 电控部作业链

## 1.框架配置

- **我是纯废物，框架配不明白**
- [x] TODO:
  -[x] TIM3 这里使用 TIM3 作为 ADC 的触发源以在指定频率下开启 ADC 转换。将 Trigger Event Selection 改为 Update Event。
  -[x] TIM4
`TIM4` 作为驱动蜂鸣器的 PWM 输出，其输出频率决定了蜂鸣器频率，输出占空比决定了输出功率（音量）。令蜂鸣器输出频率为$f_{buzzer}$，$f_{buzzer}=\frac{f_{APB1timerclock}}{(Prescaler+1)(CounterPeriod+1)}$。这里可以开启 `auto reload preload`
  -[x] `USART3` 连接到 `SBUS/DBUS` 协议的接收机，请根据遥控器驱动教程配置。

## 2.遥控器接收，看门狗

- 代码写好了，待测试
- [ ] TODO:
  - [ ] 测试
  - [ ] 归一化
  - [ ] 配置看门狗
