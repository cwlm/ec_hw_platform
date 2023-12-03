# 电控部作业链

## 1.框架配置

- **我是纯废物，框架配不明白**
- [x] TODO:
    - [x] TIM3 这里使用 TIM3 作为 ADC 的触发源以在指定频率下开启 ADC 转换。将 Trigger Event Selection 改为 Update Event。
    - [x] TIM4 `TIM4` 作为驱动蜂鸣器的 PWM
      输出，其输出频率决定了蜂鸣器频率，输出占空比决定了输出功率（音量）。令蜂鸣器输出频率为$f_{buzzer}$，$f_{buzzer}=\frac{f_
      {APB1timerclock}}{(Prescaler+1)(CounterPeriod+1)}$。这里可以开启 `auto reload preload`
    - [x] `USART3` 连接到 `SBUS/DBUS` 协议的接收机，请根据遥控器驱动教程配置。

## 2.遥控器接收，看门狗

- 代码写好了，待测试
- [x] TODO:
    - [x] 测试
    - [x] 归一化
    - [x] 配置看门狗

## 3.电机

M3508最大空载转速为589rpm，在一个CAN周期中最多转动589rpm*1ms=3.534度<180度

M2006最大空载转速为777rpm，在一个CAN周期中最多转动777rpm*1ms=4.662度<180度

GM6020最大空载转速为320rpm，在一个CAN周期中最多转动320rpm*1ms=1.92度<180度

故出现>180度的变化则为新的一圈
