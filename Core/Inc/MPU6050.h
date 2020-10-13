#ifndef MPU6050_H
#define MPU6050_H
#include "stm32f3xx_hal.h"
#include "stm32f3xx_hal_i2c.h"

#define MPU6050_ADDR 0xD0
#define SMPLRT_DIV_REG 0x19
#define GYRO_CONFIG_REG 0x1B
#define ACCEL_CONFIG_REG 0x1C
#define INT_ENABLE_REG 0x38
#define INT_PIN_CFG_REG 0x37
#define INT_STATUS_REG 0x3A
#define GYRO_XOUT_H_REG 0x43
#define ACCEL_XOUT_H_REG 0x3B
#define PWR_MGMT_1_REG 0x6B
#define WHO_AM_I_REG 0x75

// int16_t Gyro_Y_RAW;
// float  GyroY;
int16_t ACCEL_X_RAW;
float ACCEL_X;
extern I2C_HandleTypeDef I2CHandle;

void MPU6050_Read_Accel(void);
void MPU6050_Init(void);



#endif