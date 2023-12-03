//
// Created by cwlm on 2023/12/3.
//
#include "../Inc/DataProcess.h"

float limit(float val, float min, float max) {
    if (val >= max)
        return max;
    if (val <= min)
        return min;
    return val;
}

float loopLimit(float val, float min, float max) {
    float range = max - min;

    while (val < min) {
        val += range;
    }

    while (val > max) {
        val -= range;
    }

    return val;
}

float deadBand(float val, float min, float max) {
    if (val >= min && val <= max) {
        return 0.0f;
    } else {
        return val;
    }
}

float encoder2Degree(float ecd, float ecd_range) {
    return ecd / ecd_range * 360;
}
