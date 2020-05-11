/*
 * reflow_profiles.c
 *
 *  Created on: 21.03.2019
 *      Author: Johannes
 */

#include "roc/reflow_profiles.h"
#include "sys/_stdint.h"

#define PROFILE_BYTE_SIZE 52

// HARDCODED DEFAULT PROFILE
uint8_t DEFAULT_PROFILE[PROFILE_BYTE_SIZE] =
{ 0x07, // name_length: Length of "Default" (max. 16) (0)
		0x44, // name_0: "D" (1)
		0x65, // name_1: "e" (2)
		0x66, // name_2: "f" (3)
		0x61, // name_3: "a" (4)
		0x75, // name_4: "u" (5)
		0x6c, // name_5: "l" (6)
		0x74, // name_6: "t" (7)
		0x00, // name_7 (8)
		0x00, // name_8 (9)
		0x00, // name_9 (10)
		0x00, // name_10 (11)
		0x00, // name_11 (12)
		0x00, // name_12 (13)
		0x00, // name_13 (14)
		0x00, // name_14 (15)
		0x00, // name_15 (16)
		0x3c, // cooldown_time: 60 seconds (17)
		0x04, // Time samples: 4 (max. 8) (18)
		0x00, // t_0_MSB (19)
		0x3c, // t_0_LSB: 60sec (20)
		0x00, // T_0_MSB (21)
		0x64, // T_0_LSB: 100°C (22)
		0x00, // t_1_MSB (23)
		0x96, // t_1_LSB: 150sec (24)
		0x00, // T_1_MSB (25)
		0x96, // T_1_LSB: 150°C (26)
		0x00, // t_2_MSB (27)
		0xb4, // t_2_LSB: 180sec (28)
		0x00, // T_2_MSB (29)
		0xb7, // T_2_LSB: 183°C (30)
		0x00, // t_3_MSB (31)
		0xf0, // t_3_LSB: 240sec (32)
		0x00, // T_3_MSB (33)
		0xeb, // T_3_LSB: 235°C (34)
		0x00, // t_4_MSB (35)
		0x00, // t_4_LSB (36)
		0x00, // T_4_MSB (37)
		0x00, // T_4_LSB (38)
		0x00, // t_5_MSB (39)
		0x00, // t_5_LSB (40)
		0x00, // T_5_MSB (41)
		0x00, // T_5_LSB (42)
		0x00, // t_6_MSB (43)
		0x00, // t_6_LSB (44)
		0x00, // T_6_MSB (45)
		0x00, // T_6_LSB (46)
		0x00, // t_7_MSB (47)
		0x00, // t_7_LSB (48)
		0x00, // T_7_MSB (50)
		0x00, // T_7_LSB (51)
		};

/*
 * Gets the profile count.
 */
uint8_t reflow_profiles_get_count(void)
{
	return 1;
}

/*
 * Gets the byte size of a reflow profile.
 */
uint8_t reflow_profiles_get_profile_byte_size(void)
{
	return PROFILE_BYTE_SIZE;
}

/*
 * Gets a profile from it's id.
 */
uint8_t* reflow_profiles_get_profile(uint8_t id)
{
	if (id == 0)
		return DEFAULT_PROFILE;
	else return 0;
}

/*
 * Gets the name length of a profile.
 */
uint8_t reflow_profiles_get_profile_name_length(uint8_t* profile)
{
	return profile[0];
}

/*
 * Util function that gets the name of a profile.
 */
void reflow_profiles_get_profile_name(uint8_t* profile, char* buf)
{

	for (uint8_t i = 0; i < reflow_profiles_get_profile_name_length(profile); i++)
	{
		buf[i] = (char)profile[i + 1];
	}
	buf[profile[0]] = 0x00; // 0x00 string terminator at the end.
}

/*
 * Gets the n-th time of the profile.
 */
uint16_t reflow_profiles_get_time(uint8_t* profile, uint8_t index)
{
	return (((uint16_t) profile[19 + (index * 4)]) << 8) + profile[20 + (index * 4)];
}

/*
 * Gets the n-th temperature of the profile.
 */
uint16_t reflow_profiles_get_temp(uint8_t* profile, uint8_t index)
{
	return (((uint16_t) profile[21 + (index * 4)]) << 8) + profile[22 + (index * 4)];
}

/*
 * Gets the maximum temperature of a reflow profile.
 */
uint16_t reflow_profiles_get_max_temp(uint8_t* profile)
{
	uint16_t current_max = 0x0000;
	for (uint8_t i = 0; i < reflow_profiles_get_profile_sample_count(profile); i++)
	{
		uint16_t tst_max = reflow_profiles_get_temp(profile, i);
		if (tst_max > current_max)
		{
			current_max = tst_max;
		}
	}
	return current_max;
}

/*
 * Gets the total time of a reflow profile.
 */
uint16_t reflow_profiles_get_total_time(uint8_t* profile)
{
	return reflow_profiles_get_time(profile, reflow_profiles_get_profile_sample_count(profile) - 1);
}

/*
 * Gets the cooldown time of a reflow profile.
 */
uint8_t reflow_profiles_get_profile_cooldown_time(uint8_t* profile)
{
	return profile[17];
}

/*
 * Gets the temperature sample count of a profile.
 */
uint8_t reflow_profiles_get_profile_sample_count(uint8_t* profile)
{
	return profile[18];
}
