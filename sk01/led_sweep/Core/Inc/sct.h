/*
 * sct.h
 *
 *  Created on: Oct 9, 2024
 *      Author: 240635
 */

#ifndef SCT_H_
#define SCT_H_


void sct_init(void);

void sct_led(uint32_t value);

void sct_value(uint16_t value, uint8_t led);

void sct_bargraph(uint8_t ledNum);

void sct_universalBargraph(uint8_t ledBinaryIndex);

#endif /* SCT_H_ */
