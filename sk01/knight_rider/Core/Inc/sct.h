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

void sct_valueAndBar(uint16_t value, uint8_t ledID);

#endif /* SCT_H_ */
