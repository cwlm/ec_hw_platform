//
// Created by cwlm on 2023/12/4.
//

#include "../Inc/Motor.h"
#include <cmath>

Motor::Motor(const Type &type, const float &ratio, const ControlMethod &method, const Pid &pPid,
             const Pid &sPid) : info_({type, ratio}), method_(method), pPid_(pPid), sPid_(sPid), intensity_(0),
                                target_angle_(0.0f), target_speed_(0.0f),
                                motor_data_({0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f}) {}

void Motor::Reset() {
    mode_ = WORKING;
    intensity_ = 0;
    target_angle_ = 0.0f;
    target_speed_ = 0.0f;
    motor_data_ = {.angle=0.0f,
            .ecd_angle=0.0f,
            .last_ecd_angle=0.0f,
            .rotate_speed=0.0f,
            .current=0.0f,
            .temp=0.0f};
    if (method_ == Motor::POSITION_SPEED)
        pPid_ = Pid(pPid_.kp_, (info_.ratio > 0) ? pPid_.ki_ : (-pPid_.ki_),
                    (info_.ratio > 0) ? pPid_.kd_ : (-pPid_.kd_), pPid_.i_max_, pPid_.out_max_);

    sPid_ = Pid(sPid_.kp_, (info_.ratio > 0) ? sPid_.ki_ : (-sPid_.ki_), (info_.ratio > 0) ? sPid_.kd_ : (-sPid_.kd_),
                sPid_.i_max_, sPid_.out_max_);
}

void Motor::Handle() {
    switch (mode_) {
        case POWER_OFF:
            intensity_ = 0;
            return;
        case WORKING:
            motor_data_.angle = motor_data_.ecd_angle / info_.ratio; //减速比为编码器角度/输出角度
            if (method_ == Motor::POSITION_SPEED) //双环控制，计算位置PID
                target_speed_ = pPid_.calc(target_angle_, motor_data_.angle);
            break;
        case STOP:
            target_speed_ = 0.0f;
            break;
    }
    switch (info_.type) {
        case M3508:
            intensity_ = (int16_t) roundf(sPid_.calc(target_speed_, motor_data_.rotate_speed) / 10 * 10000);
            break;
        case M2006:
            intensity_=(int16_t)roundf(sPid_.calc(target_speed_, motor_data_.rotate_speed) / 20 * 16384);
            break;
        case GM6020:
            intensity_=(int16_t)roundf(sPid_.calc(target_speed_, motor_data_.rotate_speed) / 24 * 30000);
            break;
    }
}

void Motor::SetAngle(const float &target_angle) {
    target_angle_=target_angle;
}

void Motor::SetSpeed(const float &target_speed) {
    target_speed_=target_speed;
}


