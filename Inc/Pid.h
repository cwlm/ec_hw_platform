//
// Created by cwlm on 2023/12/3.
//

class Pid {
public:
    Pid(float kp, float ki, float kd, float i_max, float out_max);

    float calc(float ref, float fdb);

    void setKp(float kp);

    void setKi(float ki);

    void setKd(float kd);

private:
    float kp_, ki_, kd_;// coefficient for proportion, integration and differentiation
    float i_max_, out_max_;
    float output_;

    float ref_, fdb_;
    float err_, err_sum_, last_err_;
    float pOut_, iOut_, dOut_;
};