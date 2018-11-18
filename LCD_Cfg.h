/*
 * LCD_Cfg.h
 *
 *  Created on: Nov 18, 2018
 *      Author: ziad
 */

#ifndef LCD_CFG_H_
#define LCD_CFG_H_

/* Data Mode Config */
#define DATA_MODE_4 0
#define DATA_MODE_8 1
#define DATA_MODE DATA_MODE_4

/* Cursor mode Config */
#define CURSOR_OFF 0
#define CURSOR_BLINK 1
#define CURSOR_MODE CURSOR_OFF

/* GPIO Groups Config */
#define RS_GROUP_IDX 0
#define RW_GROUP_IDX 1
#define EN_GROUP_IDX 2
#if DATA_MODE == DATA_MODE_8
#define DB0_GROUP_IDX 3
#define DB1_GROUP_IDX 4
#define DB2_GROUP_IDX 5
#define DB3_GROUP_IDX 6
#endif
#define DB4_GROUP_IDX 3
#define DB5_GROUP_IDX 4
#define DB6_GROUP_IDX 5
#define DB7_GROUP_IDX 6



#endif /* LCD_CFG_H_ */
