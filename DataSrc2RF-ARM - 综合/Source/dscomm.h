#ifndef __DSCOMM_H
#define __DSCOMM_H

#include "CPESchipdef.h"
#include <stdio.h>
#include "serial.h"
#include "ammeter_cmd.h"

/*******************数据源类型定义*******************/
#define TEMP_SENSOR        0x01
#define RADIO_SENSOR			 0x02

#define AMMETER_DATA       0xFF

#define SensorType         u8

/***********************function*************************/
void DS_RecvData(void);
void DS_SendCmd(void);
void DS_getAMTData(void);
void DS_getAMTPara(AMTCmdType cmdType);
void DS_getTempData(void);
void DS_getThermoElecData(void);
void DS_getSensorData(SensorType sensorType);
void DS_copyBuffer(u8 command[]);

#endif
