//
// Created by cwlm on 2023/12/3.
//
#include "../Inc/DataProcess.h"

float clamp(float val, float min, float max) {
    if (val < min) {
        return min;
    } else if (val > max) {
        return max;
    } else {
        return val;
    }
}
