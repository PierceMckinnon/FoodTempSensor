
#include "MPU6050.h"


void MPU6050_Init (void)
{
	uint8_t check;
	uint8_t Data;


	HAL_I2C_Mem_Read (&I2CHandle, MPU6050_ADDR,WHO_AM_I_REG,1, &check, 1, 1000);

	if ((check<<1) == MPU6050_ADDR)  // 0x68 will be returned by the sensor if everything goes well
	{
		// power management register 0X6B we should write all 0's to wake the sensor up
		Data = 0;
		HAL_I2C_Mem_Write(&I2CHandle, MPU6050_ADDR, PWR_MGMT_1_REG, 1,&Data, 1, 1000);

	

		// Set DATA RATE of 1KHz by writing SMPLRT_DIV register
		Data = 0x07;
		HAL_I2C_Mem_Write(&I2CHandle, MPU6050_ADDR, SMPLRT_DIV_REG, 1, &Data, 1, 1000);

		// Set Gyroscopic configuration in GYRO_CONFIG Register
		// XG_ST=0,YG_ST=0,ZG_ST=0, FS_SEL=0 -> ± 250 °/s
		Data = 0x00;
		HAL_I2C_Mem_Write(&I2CHandle, MPU6050_ADDR, GYRO_CONFIG_REG, 1, &Data, 1, 1000);
	}

}
// uint8_t high;
// 	uint8_t low;
// 	HAL_I2C_Mem_Read (&I2CHandle, MPU6050_ADDR, 0x43, 1, &high, 1, 1000);
// 	HAL_I2C_Mem_Read (&I2CHandle, MPU6050_ADDR, 0x44, 1, &low, 1, 1000);
// Gyro_Y_RAW = (int16_t)(high << 8 | low);
void MPU6050_Read_Gyro (void)
{
	//for debugging
	if(HAL_OK ==HAL_I2C_IsDeviceReady(&I2CHandle,MPU6050_ADDR,20,1000)){
	uint8_t Gyro_x_Data[2];	
	// Read 2 BYTES of data starting from GYRO_XOUT_H register
	HAL_I2C_Mem_Read(&I2CHandle, MPU6050_ADDR, 0x43, 1, Gyro_x_Data, 2, 1000);
	

	//Gyro_x_Data[0] holds high bits, shift to left by 8 and or with low bits for total raw value
	Gyro_Y_RAW = (int16_t)(Gyro_x_Data[0] << 8 | Gyro_x_Data[1]);
    //set the the scale of gyro to +-250 by setting FS_Sel to zero
    //this results in sensitivity of 131 LSB so we must divide raw value by 131
	GyroY = Gyro_Y_RAW/131.0;

}
}
