//
// Created by cwlm on 2023/12/3.
//

#include "../Inc/Motor.h"
#include <cmath>

Motor::Motor(const Type &type, const float &ratio, const ControlMethod &method, const Pid &ppid,
             const Pid &spid) : info_({type, ratio}), method_(method), ppid_(ppid), spid_(spid), intensity_(0),
                                target_angle(0.0f), target_speed(0.0f),
                                motor_data_({0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f}) {}

void Motor::Reset() {
    mode_ = WORKING;
    intensity_ = 0;
    target_angle = 0.0f;
    target_speed = 0.0f;
    motor_data_ = {.angle=0.0f,
            .ecd_angle=0.0f,
            .last_ecd_angle=0.0f,
            .rotate_speed=0.0f,
            .current=0.0f,
            .temp=0.0f};
    if (method_ == Motor::POSITION_SPEED)
        ppid_ = Pid(ppid_.kp_, (info_.ratio > 0) ? ppid_.ki_ : (-ppid_.ki_),
                    (info_.ratio > 0) ? ppid_.kd_ : (-ppid_.kd_), ppid_.i_max_, ppid_.out_max_);

    spid_ = Pid(spid_.kp_, (info_.ratio > 0) ? spid_.ki_ : (-spid_.ki_), (info_.ratio > 0) ? spid_.kd_ : (-spid_.kd_),
                spid_.i_max_, spid_.out_max_);
}

void Motor::Handle() {
    switch (mode_) {
        case POWER_OFF:
            intensity_ = 0;
            return;
        case WORKING:
            motor_data_.angle = motor_data_.ecd_angle / info_.ratio; //减速比为编码器角度/输出角度
            if (method_ == Motor::POSITION_SPEED) //双环控制，计算位置PID
                target_speed = ppid_.calc(target_angle, motor_data_.angle);
            break;
        case STOP:
            target_speed = 0.0f;
            break;
    }
    switch (info_.type) {
        case M3508:
            intensity_ = (int16_t) roundf(spid_.calc(target_speed, motor_data_.rotate_speed) / 10 * 10000);
            break;
        case M2006:
            break;
        case GM6020:
            break;
    }
}

void Motor::SetAngle(const float &target_angle) {

}

void Motor::SetSpeed(const float &target_speed) {

}
