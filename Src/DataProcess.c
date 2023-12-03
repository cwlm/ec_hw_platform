//
// Created by cwlm on 2023/12/3.
//

#ifndef EC_HW_PLATFORM_DATAPROCESS_H
#define EC_HW_PLATFORM_DATAPROCESS_H

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

#endif //EC_HW_PLATFORM_DATAPROCESS_H
