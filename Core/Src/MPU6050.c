
#include "MPU6050.h"


void MPU6050_Init (void)
{
	uint8_t check;
	uint8_t Data;


	HAL_I2C_Mem_Read (&I2CHandle, MPU6050_ADDR,WHO_AM_I_REG,1, &check, 1, 1000);

	if ((check) == 0x68)  // 0x68 will be returned by the sensor if everything goes well
	{
		//reset the unit 
		Data = 0x80;
		if (HAL_I2C_Mem_Write(&I2CHandle, MPU6050_ADDR, PWR_MGMT_1_REG, 1,&Data, 1, 1000)!= HAL_OK)
		{ 
    		while(1)
			{

			}
		}
		// power management register 0X6B we should write all 0's to wake the sensor up
		Data = 0;
		if (HAL_I2C_Mem_Write(&I2CHandle, MPU6050_ADDR, PWR_MGMT_1_REG, 1,&Data, 1, 1000)!=HAL_OK)
		{	 
    		while(1)
			{
				
			}
		}
		// Set DATA RATE of 1KHz by writing SMPLRT_DIV register
		Data = 0x07;
		if(HAL_I2C_Mem_Write(&I2CHandle, MPU6050_ADDR, SMPLRT_DIV_REG, 1, &Data, 1, 1000)!=HAL_OK)
		 {
    		while(1)
			{
				
			}
 		 }

		//setting range of accel to += 2g, disabling self test
		Data = 0x00;
		if(HAL_I2C_Mem_Write(&I2CHandle, MPU6050_ADDR, ACCEL_CONFIG_REG, 1, &Data, 1, 1000)!=HAL_OK)
		 {
    		while(1)
			{
				
			}
 		 }
		//enabling interrupt on data ready 
		Data = 0x01;
		if(HAL_I2C_Mem_Write(&I2CHandle, MPU6050_ADDR, INT_ENABLE_REG, 1, &Data, 1, 1000)!=HAL_OK)
		 {
   			 while(1)
			{
				
			}
 		 }
		//configure the interrupt pin 
		Data = 0x00;
		if(HAL_I2C_Mem_Write(&I2CHandle, MPU6050_ADDR, INT_PIN_CFG_REG, 1, &Data, 1, 1000)!=HAL_OK)
		 {
    		while(1)
			{
				
			}
  		 }

	}

}


void MPU6050_Read_Accel (void)
{
	uint8_t ACCEL_Data[2];
	uint8_t Data;

	// Read 6 BYTES of data starting from ACCEL_XOUT_H register

	HAL_I2C_Mem_Read (&I2CHandle, MPU6050_ADDR, ACCEL_XOUT_H_REG, 1, ACCEL_Data, 2, 1000);

	ACCEL_X_RAW= (int16_t)(ACCEL_Data[0] << 8 | ACCEL_Data [1]);
	

	//setting the fsRange to +-2 the lsb sensitivity is 16384.0 so divide to get value in g's

	ACCEL_X = ACCEL_X_RAW/16384.0;

	//clear int_status register
	HAL_I2C_Mem_Read(&I2CHandle, MPU6050_ADDR, INT_STATUS_REG, 1, &Data, 1, 1000);

}
// uint8_t high;
// 	uint8_t low;
// 	HAL_I2C_Mem_Read (&I2CHandle, MPU6050_ADDR, 0x43, 1, &high, 1, 1000);
// 	HAL_I2C_Mem_Read (&I2CHandle, MPU6050_ADDR, 0x44, 1, &low, 1, 1000);
// Gyro_Y_RAW = (int16_t)(high << 8 | low);
// void MPU6050_Read_Gyro (void)
// {
// 	//for debugging
// 	if(HAL_OK ==HAL_I2C_IsDeviceReady(&I2CHandle,MPU6050_ADDR,20,1000)){
// 	uint8_t Gyro_x_Data[2];	
// 	// Read 2 BYTES of data starting from GYRO_XOUT_H register
// 	HAL_I2C_Mem_Read(&I2CHandle, MPU6050_ADDR, 0x43, 1, Gyro_x_Data, 2, 1000);
	

// 	//Gyro_x_Data[0] holds high bits, shift to left by 8 and or with low bits for total raw value
// 	Gyro_Y_RAW = (int16_t)(Gyro_x_Data[0] << 8 | Gyro_x_Data[1]);
//     //set the the scale of gyro to +-250 by setting FS_Sel to zero
//     //this results in sensitivity of 131 LSB so we must divide raw value by 131
// 	GyroY = Gyro_Y_RAW/131.0;

// }
//}
