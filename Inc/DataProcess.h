//
// Created by cwlm on 2023/12/4.
//

#ifndef EC_HW_PLATFORM_DATAPROCESS_H
#define EC_HW_PLATFORM_DATAPROCESS_H

#ifdef __cplusplus
extern "C"{
#endif

float limit(float val, float min, float max);
float loopLimit(float val, float min, float max);
float deadBand(float val, float min, float max);


#ifdef __cplusplus
}
#endif

#endif //EC_HW_PLATFORM_DATAPROCESS_H