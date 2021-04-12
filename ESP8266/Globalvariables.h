/*
 Copyright (C) 2011 J. Coliz <thanhcong402@gmail.com>
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */
 
/**
 * @file Master_Sendingcard.h
 *
 */

#ifndef __GLOABL_VARIABLES__
#define __GLOABL_VARIABLES__

 //-----------------Define, variables-----------------------
#define STX 'Q'
#define ETX 'T'

int row_=0;
int column_=0;
boolean start_drop_sku=false;

//------------------End output define---------------------------
struct display
{
   int red;
   int green;
   int blue;
};
typedef struct display RGBdisplay;

RGBdisplay RGB_Player[8];
//----------------------------------------------------------
//---------------UARST------------------------------------------------
int inByte = 0;         // incoming serial byte
boolean stringComplete = false;  // whether the string is complete
int serialInArray[30]; //= new int[3];    // Where we'll put what we receive
int dataProcess[30];
int serialCount = 0;                 // A count of how many bytes we receive
boolean firstContact = false;        // Whether we've heard from the microcontroller
//---------------END UARST------------------------------------------------
//----------------------------------------------------------

boolean ledState=false;
int resend_interval=0;
boolean  start_send=false;

int tamper_interval=0;
boolean update_tamper =0;
boolean check_motor =0;
boolean wait_off_led=0;
unsigned long time_off_led;
int erro_status=0;
int id_send;
int id_set;
//----------------------------------------------------------
//-----------------Khay chua san pham-----------------------
int Vitrilaysanpham[5]={430,280,37,281,37};//A B C D E

//-----------------End Khay chua san pham-----------------------
//----------------------------------------------------------

#endif // __GLOABL_VARIABLES__
