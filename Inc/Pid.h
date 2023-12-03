//
// Created by cwlm on 2023/12/3.
//

#ifndef EC_HW_PLATFORM_PID_H
#define EC_HW_PLATFORM_PID_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../Inc/DataProcess.h"

class Pid {
public:
    Pid(float kp, float ki, float kd, float i_max, float out_max);

    float calc(float ref, float fdb);

public:
    float kp_, ki_, kd_;// coefficient for proportion, integration and differentiation
    float i_max_, out_max_;
    float output_;

private:
    float ref_, fdb_;
    float err_, err_sum_, last_err_;
    float pOut_, iOut_, dOut_;
};

#ifdef __cplusplus
}
#endif

#endif