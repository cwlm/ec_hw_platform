//
// Created by cwlm on 2023/12/3.
//

#include "../Inc/Pid.h"
#include "../Inc/dataProcess.h"

Pid::Pid(float kp, float ki, float kd, float i_max, float out_max) : kp_(kp), ki_(ki), kd_(kd), i_max_(i_max),
                                                                     out_max_(out_max), output_(0.0f), ref_(0.0f),
                                                                     fdb_(0.0f), err_(0.0f), err_sum_(0.0f),
                                                                     last_err_(0.0f), pOut_(0.0f), iOut_(0.0f),
                                                                     dOut_(0.0f) {}

float Pid::calc(float ref, float fdb) {
    ref_ = ref;
    fdb_ = fdb;

    last_err_ = err_;
    err_ = ref_ - fdb_;
    err_sum_ = clamp(err_sum_ + err_, -i_max_, i_max_);

    pOut_ = kp_ * err_;
    iOut_ = ki_ * err_sum_;
    dOut_ = kd_ * (last_err_ - err_);

    output_ = clamp(pOut_ + iOut_ + dOut_, -out_max_, out_max_);
    return output_;
}

void Pid::setKp(float kp) {
    kp_ = kp;
}

void Pid::setKi(float ki) {
    ki_ = ki;
}

void Pid::setKd(float kd) {
    kp_ = kd;
}
