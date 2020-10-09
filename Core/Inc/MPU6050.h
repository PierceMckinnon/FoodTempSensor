#ifndef MPU6050_H
#define MPU6050_H
#include "stm32f3xx_hal.h"
#include "stm32f3xx_hal_i2c.h"

#define MPU6050_ADDR 0x68<<1
#define SMPLRT_DIV_REG 0x19
#define GYRO_CONFIG_REG 0x1B
#define GYRO_XOUT_H_REG 0x43
#define PWR_MGMT_1_REG 0x6B
#define WHO_AM_I_REG 0x75

int16_t Gyro_Y_RAW;
float  GyroY;
extern I2C_HandleTypeDef I2CHandle;

void MPU6050_Read_Gyro(void);
void MPU6050_Init(void);



#endif