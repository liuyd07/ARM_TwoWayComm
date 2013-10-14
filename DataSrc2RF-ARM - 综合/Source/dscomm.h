#ifndef __DSCOMM_H
#define __DSCOMM_H

#include "CPESchipdef.h"
#include <stdio.h>
#include "stm32f10x_lib.h"
#include "serial.h"
#include "ammeter_cmd.h"

/*******************数据源类型定义*******************/
#define TEMP_SENSOR        0x01
#define RADIO_SENSOR			 0x02

#define AMMETER_DATA       0xFF

#define SensorType         u8


void DS_getAMTData(void);
void DS_getSensorData(SensorType sensorType);

#endif
