
#include "LiquidCrystal.h"
#include "FloatToChar.h"
#include "math.h"


uint8_t one[8] = {
0x00,
0x0E,
0x04,
0x04,
0x04,
0x04,
0x05,
0x04
};
uint8_t two[8] = {
0x00,
0x1F,
0x02,
0x04,
0x08,
0x10,
0x11,
0x0E
};
uint8_t three[8] = {
0x00,
0x0D,
0x20,
0x10,
0x08,
0x04,
0x08,
0x1F
};
uint8_t four[8] = {
0x00,
0x08,
0x08,
0x1F,
0x09,
0x0A,
0x0C,
0x08
};

uint8_t five[8] = {
0x00,
0x0E,
0x11,
0x10,
0x10,
0x0F,
0x01,
0x1F
};
uint8_t six[8] = {
0x00,
0x0E,
0x11,
0x11,
0x0F,
0x01,
0x02,
0x0C
};
uint8_t seven[8] = {
0x00,
0x02,
0x02,
0x02,
0x04,
0x08,
0x11,
0x1F
};
uint8_t nine[8] = {
0x00,
0x06,
0x08,
0x10,
0x1E,
0x11,
0x11,
0x0E
};
uint8_t em[8] = {
0x00,
0x06,
0x08,
0x10,
0x1E,
0x11,
0x11,
0x0E
};
uint8_t eee[8] = {
0x00,
0x1F,
0x01,
0x01,
0x0F,
0x01,
0x01,
0x1F
};
uint8_t tee[8] = {
0x00,
0x04,
0x04,
0x04,
0x04,
0x04,
0x04,
0x1F
};

//want to take the floating point rounded to 2 decimal places
//and convert it to char to be printed to the lcd
//This can be done by add the float to '0'
uint8_t* specialchars[13] = {NULL,one,two,three,four,five,six,seven,NULL,nine,tee,eee,em};
//call in main
void initialize()
{
        createChar(5,specialchars[10]);
        createChar(6,specialchars[11]);
        createChar(7,specialchars[12]);
}

void float_char(char *buff, float y, int z)
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
        *buff++='.';
        *buff++=(dec/10)%10 + '0';
        *buff++=dec%10 + '0';
        *buff++='\0';
    //look over this implementation
    // if(z==1)
    // {
    //     int i=0;
    //         while(i<5)
    //         {
    //             if (i==3)
    //             {
    //                 i++;
    //             }
    //             else
    //             {
    //                 if(buff[i]!=8 && buff[i]!=0)
    //                 {
    //                      createChar(i,specialchars[buff[i]]);
    //                 }
                   
    //                  i++;
    //             }
               
    //         }
    // }
}