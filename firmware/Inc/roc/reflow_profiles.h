/*
 * reflow_profiles.h
 *
 *  Created on: 21.03.2019
 *      Author: Johannes
 */

#ifndef INC_ROC_REFLOW_PROFILES_H_
#define INC_ROC_REFLOW_PROFILES_H_

#include "sys/_stdint.h"

uint8_t reflow_profiles_get_count(void);
uint8_t reflow_profiles_get_profile_byte_size(void);
uint8_t* reflow_profiles_get_profile(uint8_t id);
uint8_t reflow_profiles_get_profile_name_length(uint8_t* profile);
void reflow_profiles_get_profile_name(uint8_t* profile, char* buf);
uint16_t reflow_profiles_get_time(uint8_t* profile, uint8_t index);
uint16_t reflow_profiles_get_temp(uint8_t* profile, uint8_t index);
uint16_t reflow_profiles_get_max_temp(uint8_t* profile);
uint16_t reflow_profiles_get_total_time(uint8_t* profile);
uint8_t reflow_profiles_get_profile_cooldown_time(uint8_t* profile);
uint8_t reflow_profiles_get_profile_sample_count(uint8_t* profile);

#endif /* INC_ROC_REFLOW_PROFILES_H_ */
