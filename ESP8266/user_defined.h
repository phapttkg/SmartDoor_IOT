/*
 Copyright (C) 2020 Mr. Cong <thanhcong402@gmail.com>
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */
 
/**
 * @file user_defined.h
 *	Master_Sendingcard.ino
 *	Slave_Receivingcard.ino
 */

#ifndef __USER_DEFINE__
#define __USER_DEFINE__

 //-----------------Define, variables-----------------------
/**
 * @enum USER_FC
 * @brief
 * Modbus function codes summary.
 * These are the implement function codes either for Master or for Slave.
 *
 * @see also fctsupported
 * @see also modbus_t
 */

enum USER_FC
{
    USER_FC_NONE                     = 0,   /*!< null operator */
    USER_FC_READ_INFO               = 1,	/*!< FCT=1 -> read coils or digital outputs */
    USER_FC_READ_DISCRETE_INPUT      = 2,	/*!< FCT=2 -> read digital inputs */
    USER_FC_READ_REGISTERS           = 3,	/*!< FCT=3 -> read registers or analog outputs */
    USER_FC_READ_INPUT_REGISTER      = 4,	/*!< FCT=4 -> read analog inputs */
    USER_FC_WRITE_ID               = 5,	/*!< FCT=5 -> write single coil or output */
    USER_FC_WRITE_INFO           = 6,	/*!< FCT=6 -> write single register */
    USER_FC_WRITE_ID_ALL		=7,	
	USER_FC_WRITE_MULTIPLE_COILS     = 15,	/*!< FCT=15 -> write multiple coils or outputs */
    USER_FC_WRITE_MULTIPLE_REGISTERS = 16	/*!< FCT=16 -> write multiple registers */
};
/**
 * @enum DATA_CODE_FUNCTION
 * @brief
 * Indexes to Slave function data array positions
 *	[ID_USER] [FUNC_USER] [DATA]
 */
enum DATA_CODE_FUNCTION
{
    ID_USER								=0,
	FUNC_USER, //!< ID field
	HH_SET_SAVE, //!< ID field
    MM_SET_SAVE, //!< Function code position
    HH_SET_RUNNING_SAVE, //!< Address high byte
    MM_SET_RUNNING_SAVE, //!< Address low byte
    HH_SET, //!< Number of coils or registers high byte
    MM_SET, //!< Number of coils or registers low byte
	HH_SET_RUNNING, //!< Number of coils or registers low byte
	MM_SET_RUNNING, //!< Number of coils or registers low byte	
	ID_SET, //!< Number of coils or registers low byte	
	ACTIVE_INDEX, //!< Number of coils or registers low byte	
    BYTE_CNT_  //!< byte counter
};

#define ID_test 71
#endif // __USER_DEFINE__
