/*
	
  ******************************************************************************
  * @file 			( фаил ):   VL6180X.h
  * @brief 		( описание ):  	
  ******************************************************************************
  * @attention 	( внимание ):	author: Golinskiy Konstantin	e-mail: golinskiy.konstantin@gmail.com
  ******************************************************************************
  
*/

#ifndef _VL6180X_H
#define _VL6180X_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------*/
#include "main.h"

// расспиновка модуля:
// VIN - питание модуля через стабилизатор напряжения (3-5 Вольт) Сам модуль работает максимум 2.8 Вольт
// 2V8 - питание модуля напрямую миную стабилизатор (2.8 Вольт), также при питании через VIN с данного пина можно снимать напряжение 2.8 Вольт до 150 мА
// GND - земля
// GPIO/GPIO1 - Выход прерывания. Открытый сток. Если используется, его следует тянуть вверх с 47 кОм резистор, в противном случае оставить неподключенным. 
//							Прерывание срабатывает при ниском уровне, Окуратно с этим портом он подтянут к 2.8 Вольтам если случайно туда дадим больше то модуль згорит.
// SHDN/GPIO0/CE - По умолчанию при включении включен чип (СЕ). Его следует тянуть высоко с помощью Резистор 47 кОм. Для отключения модуля тянем его к земле.
//							на модуле подтянут к питанию 2.8 Вольт через диод ( поетому когда на ножке будет +3.3 Вольта диод не пропустит )
// SCL - i2c
// SDA - i2c

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// внимание!!! есть похожий датчик Китайский аналог он имеет 2 отверстия ( оригинал имеет 3 отверстия ) там где 2 отверстия тот измеряет только растояние ( стоит дешевле )
// отверстия идут в один ряд ( есть еще очень маленькое сбоку но ето к датчику не относиться )
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------


// оригинальный адресс датчика на шине I2C
#define VL6180X_SLAVE_ADDRESS 											 (0x29<<1)

// ID датчика один и тотже на всех датчиках
#define VL6180X_ID_SENSOR                            0xB4			


//----------------------------------------------------------
// перечень регистров из даташита --------------------------
#define VL6180X_IDENTIFICATION_MODEL_ID              0x0000
#define VL6180X_IDENTIFICATION_MODEL_REV_MAJOR       0x0001
#define VL6180X_IDENTIFICATION_MODEL_REV_MINOR       0x0002
#define VL6180X_IDENTIFICATION_MODULE_REV_MAJOR      0x0003
#define VL6180X_IDENTIFICATION_MODULE_REV_MINOR      0x0004
#define VL6180X_IDENTIFICATION_DATE_HI               0x0006 //16bit value
#define VL6180X_IDENTIFICATION_DATE_LO               0x0007
#define VL6180X_IDENTIFICATION_TIME_1                0x0008 //16bit value
#define VL6180X_IDENTIFICATION_TIME_2                0x0009
#define VL6180X_SYSTEM_MODE_GPIO0                    0x0010
#define VL6180X_SYSTEM_MODE_GPIO1                    0x0011
#define VL6180X_SYSTEM_HISTORY_CTRL                  0x0012
#define VL6180X_SYSTEM_INTERRUPT_CONFIG_GPIO         0x0014
#define VL6180X_SYSTEM_INTERRUPT_CLEAR               0x0015
#define VL6180X_SYSTEM_FRESH_OUT_OF_RESET            0x0016
#define VL6180X_SYSTEM_GROUPED_PARAMETER_HOLD        0x0017
#define VL6180X_SYSRANGE_START                       0x0018
#define VL6180X_SYSRANGE_THRESH_HIGH                 0x0019
#define VL6180X_SYSRANGE_THRESH_LOW                  0x001A
#define VL6180X_SYSRANGE_INTERMEASUREMENT_PERIOD     0x001B
#define VL6180X_SYSRANGE_MAX_CONVERGENCE_TIME        0x001C
#define VL6180X_SYSRANGE_CROSSTALK_COMPENSATION_RATE 0x001E
#define VL6180X_SYSRANGE_CROSSTALK_VALID_HEIGHT      0x0021
#define VL6180X_SYSRANGE_EARLY_CONVERGENCE_ESTIMATE  0x0022
#define VL6180X_SYSRANGE_PART_TO_PART_RANGE_OFFSET   0x0024
#define VL6180X_SYSRANGE_RANGE_IGNORE_VALID_HEIGHT   0x0025
#define VL6180X_SYSRANGE_RANGE_IGNORE_THRESHOLD      0x0026
#define VL6180X_SYSRANGE_MAX_AMBIENT_LEVEL_MULT      0x002C
#define VL6180X_SYSRANGE_RANGE_CHECK_ENABLES         0x002D
#define VL6180X_SYSRANGE_VHV_RECALIBRATE             0x002E
#define VL6180X_SYSRANGE_VHV_REPEAT_RATE             0x0031
#define VL6180X_SYSALS_START                         0x0038
#define VL6180X_SYSALS_THRESH_HIGH                   0x003A
#define VL6180X_SYSALS_THRESH_LOW                    0x003C
#define VL6180X_SYSALS_INTERMEASUREMENT_PERIOD       0x003E
#define VL6180X_SYSALS_ANALOGUE_GAIN                 0x003F
#define VL6180X_SYSALS_INTEGRATION_PERIOD            0x0040
#define VL6180X_RESULT_RANGE_STATUS                  0x004D
#define VL6180X_RESULT_ALS_STATUS                    0x004E
#define VL6180X_RESULT_INTERRUPT_STATUS_GPIO         0x004F
#define VL6180X_RESULT_ALS_VAL                       0x0050
#define VL6180X_RESULT_HISTORY_BUFFER                0x0052
#define VL6180X_RESULT_RANGE_VAL                     0x0062
#define VL6180X_RESULT_RANGE_RAW                     0x0064
#define VL6180X_RESULT_RANGE_RETURN_RATE             0x0066
#define VL6180X_RESULT_RANGE_REFERENCE_RATE          0x0068
#define VL6180X_RESULT_RANGE_RETURN_SIGNAL_COUNT     0x006C
#define VL6180X_RESULT_RANGE_REFERENCE_SIGNAL_COUNT  0x0070
#define VL6180X_RESULT_RANGE_RETURN_AMB_COUNT        0x0074
#define VL6180X_RESULT_RANGE_REFERENCE_AMB_COUNT     0x0078
#define VL6180X_RESULT_RANGE_RETURN_CONV_TIME        0x007C
#define VL6180X_RESULT_RANGE_REFERENCE_CONV_TIME     0x0080
#define VL6180X_READOUT_AVERAGING_SAMPLE_PERIOD      0x010A
#define VL6180X_FIRMWARE_BOOTUP                      0x0119
#define VL6180X_FIRMWARE_RESULT_SCALER               0x0120
#define VL6180X_I2C_SLAVE_DEVICE_ADDRESS             0x0212
#define VL6180X_INTERLEAVED_MODE_ENABLE              0x02A3
//----------------------------------------------------------


//-------------------------------------------------
typedef enum{
	GAIN_20 = 0, // Actual ALS Gain of 20
	GAIN_10,     // Actual ALS Gain of 10.32
	GAIN_5,      // Actual ALS Gain of 5.21
	GAIN_2_5,    // Actual ALS Gain of 2.60
	GAIN_1_67,   // Actual ALS Gain of 1.72
	GAIN_1_25,   // Actual ALS Gain of 1.28
	GAIN_1 ,     // Actual ALS Gain of 1.01
	GAIN_40,     // Actual ALS Gain of 40
}vl6180x_als_gain;



typedef struct{
  uint8_t idModel;					// Model Number
  uint8_t idModelRevMajor;	// Model Number
  uint8_t idModelRevMinor;	// Model Number
  uint8_t idModuleRevMajor;	// Module major revision
  uint8_t idModuleRevMinor;	// Module minor revision
  uint16_t idDate;					// Manufacture date
  uint16_t idTime;					// Manufacture time seconds after midnight
}VL6180xIdentification;


typedef struct{
	I2C_HandleTypeDef hi2cx;
	uint8_t address;
	uint8_t data;
	uint16_t data_16;
	uint8_t distance;
	float alsCalculated;
}VL6180x;
//-------------------------------------------------



//-----------------------------------
void VL6180x_init(VL6180x*,I2C_HandleTypeDef,uint8_t);
void VL6180x_getIdentification(VL6180x*,VL6180xIdentification*);
void VL6180x_getDistance(VL6180x*);
void VL6180x_getAmbientLight(VL6180x*,vl6180x_als_gain);
uint8_t VL6180x_changeAddress(VL6180x* DataStruct, uint8_t new_address);
//----------------------------------




//------------------------------------------------------------------------------------


#ifdef __cplusplus
}
#endif

#endif	/*	_VL6180X_H */

/************************ (C) COPYRIGHT GKP *****END OF FILE****/
