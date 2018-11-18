/*
 * LCD.h
 *
 *  Created on: Nov 18, 2018
 *      Author: ziad
 */

#ifndef LCD_H_
#define LCD_H_

typedef enum {LCD_OK =0, LCD_NOK}LCD_ChkType;
void LCD_Init(void);
LCD_ChkType LCD_DispChar(char Data);
LCD_ChkType LCD_SetCursPos(int x,int y);
LCD_ChkType LCD_Clear(void);
LCD_ChkType LCD_DispString(char* StrPtr);


#endif /* LCD_H_ */
