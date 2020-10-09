#include "FloatToChar.h"
#include "math.h"
//want to take the floating point rounded to 2 decimal places
//and convert it to char to be printed to the lcd
//This can be done by add the float to '0'
void float_char(char *buff, float y)
{
    //deal with decimals and units in front of decimal point
    //decimals
    int dec; 
    //units in front of decimal
    int units;
    //have to consider negative floats as well 
    //dealing with floats from -99->99
    //dealing with units left of decimal first positive and negative
    if(y<0)
    {
        //only want to deal with max 4 digits
        dec = ((int)(y*-100))%100;
        units = (int)(y*-1);
        *buff++ = '-';
      
      
    }
    else 
    {
        dec = ((int)(y*100))%100;
        units = (int)(y*1);
    }
    //only need 4 values, easiest way to do this is line by line since looking for specific output.
    //*buff++ == assign value to dereferenced pointer then increment pointer
    int i = 0;
    while((units/pow(10,i))>=1)
    {
        i++;
    }
    i--;
    while(i>=0)
    {
        *buff++=(units/(int)pow(10,i))%10 + '0';
        
        i--;
    }
    
        // *buff++=(units/10)%10 + '0';
        // *buff++=units%10 + '0';
        *buff++='.';
        *buff++=(dec/10)%10 + '0';
        *buff++=dec%10 + '0';
        *buff++='\0';
    
}