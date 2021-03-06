#include "main.h"
#include "stm32f3xx_hal_i2c.h"
#include "MPU6050.h"

float ACCEL_X=0;
int i=0;
void MPU6050_Init(void)
{
	uint8_t check;
	uint8_t Data;
	
	Data = 0x80;
	if (HAL_I2C_Mem_Write(&I2CHandle, MPU6050_ADDR, PWR_MGMT_1_REG, 1,&Data, 1, 1000)!= HAL_OK)
	{ 		
		while(1)
		{

		}
			
	}

	if (HAL_I2C_Mem_Read(&I2CHandle, MPU6050_ADDR,WHO_AM_I_REG,1, &check, 1, 1000)!=HAL_OK)
	{
		while(1)
		{

		}
	}

	if ((check) == 0x68)  // 0x68 will be returned by the sensor if everything goes well
	{
		//reset the unit 
		
		// power management register 0X6B we should write all 0's to wake the sensor up
		Data = 0x08;
		check = 0x00;
		if(HAL_I2C_Mem_Write(&I2CHandle, MPU6050_ADDR, PWR_MGMT_1_REG, 1,&Data, 1, 1000)!=HAL_OK)
		{	
			while(1)
			{
					
			}
			
		}
		HAL_I2C_Mem_Read(&I2CHandle, MPU6050_ADDR,PWR_MGMT_1_REG, 1,&check, 1, 1000);
		if(check!=Data)
		{
			while(1)
			{
					
			}
		}

		//setting range of accel to += 2g, disabling self test
		Data = 0x08;
		check =0x00;
		if(HAL_I2C_Mem_Write(&I2CHandle, MPU6050_ADDR, ACCEL_CONFIG_REG, 1, &Data, 1, 1000)!=HAL_OK)
		 {
			while(1)
			{
					
			}
			
 		 }
		HAL_I2C_Mem_Read(&I2CHandle, MPU6050_ADDR,ACCEL_CONFIG_REG, 1,&check, 1, 1000);
		if(check!=Data)
		{
			while(1)
			{
					
			}
		}
		
		// Set DATA SAMPLE RATE of 1KHz by writing SMPLRT_DIV register
		Data = 0xDF;
		check =0x00;
		if(HAL_I2C_Mem_Write(&I2CHandle, MPU6050_ADDR, SMPLRT_DIV_REG, 1, &Data, 1, 1000)!=HAL_OK)
		 {
			while(1)
			{
					
			}
			
		}
		HAL_I2C_Mem_Read(&I2CHandle, MPU6050_ADDR,SMPLRT_DIV_REG, 1,&check, 1, 1000);
		if(check!=Data)
		{
			while(1)
			{
					
			}
		}

		//enabling interrupt on data ready 
		Data = 0x01;
		check = 0x00;
		if(HAL_I2C_Mem_Write(&I2CHandle, MPU6050_ADDR, INT_ENABLE_REG, 1, &Data, 1, 1000)!=HAL_OK)
		 {
				while(1)
				{
					
				}
 		 }
		HAL_I2C_Mem_Read(&I2CHandle, MPU6050_ADDR,INT_ENABLE_REG, 1,&check, 1, 1000);
		if(check!=Data)
		{
			while(1)
			{
					
			}
		}
		
		//configure the interrupt pin to be active high, send a 50us pulse
		Data = 0x00;
		check =0x00;
		if(HAL_I2C_Mem_Write(&I2CHandle, MPU6050_ADDR, INT_PIN_CFG_REG, 1, &Data, 1, 1000)!=HAL_OK)
		 {
			while(1)
			{
					
			}
  		 }
		HAL_I2C_Mem_Read(&I2CHandle, MPU6050_ADDR, INT_PIN_CFG_REG, 1,&check, 1, 1000);
		if(check!=Data)
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

	if(HAL_I2C_Mem_Read (&I2CHandle, MPU6050_ADDR, ACCEL_XOUT_H_REG, 1, ACCEL_Data, 2, 1000)!=HAL_OK)
	{
		while(1)
		{
			
		}
	}

	int16_t  ACCEL_X_RAW= (int16_t)(ACCEL_Data[0] << 8 | ACCEL_Data [1]);
	

	//setting the fsRange to +-2 the lsb sensitivity is 16384.0 so divide to get value in g's

	ACCEL_X = ACCEL_X_RAW/16384.0;

	if(ACCEL_X<-0.2 && i==0)
	{
		printval();
		i=1;
	}
	else if(ACCEL_X>0.2 && i==1)
	{
		printval();
		i=0;
	}

	
	//clear int_status register
	if(HAL_I2C_Mem_Read(&I2CHandle, MPU6050_ADDR, INT_STATUS_REG, 1, &Data, 1, 1000)!=HAL_OK)
	{
		while(1)
		{

		}
	}
}
