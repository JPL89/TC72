// @File		TC72.H		 		
// @Author		JOSIMAR PEREIRA LEITE
// @country		Brazil
// @Date		04/05/23
//
//
// Copyright (C) 2023  JOSIMAR PEREIRA LEITE
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
#ifndef TC72_H
#define TC72_H

#define TC72_SCK            PORTCbits.RC0
#define TC72_CE             PORTCbits.RC1
#define TC72_SDI            PORTCbits.RC2
#define TC72_SDO            PORTCbits.RC3

#define TC72_SCK_TRIS       TRISCbits.RC0
#define TC72_CE_TRIS        TRISCbits.RC1
#define TC72_SDI_TRIS       TRISCbits.RC2
#define TC72_SDO_TRIS       TRISCbits.RC3

#define TC72_START_CONVERTION 0xEE
#define TC72_STOP_CONVERTION 0x22
#define TC72_CONTINUOUS_CONVERTION 0x40

unsigned char Spi_transfer(unsigned char byte)
{
    unsigned char data = 0x00;
    
    for(unsigned char mask = 0x80; mask; mask >>= 1)
    {
        TC72_SCK = 1;
        
        if(byte & mask) TC72_SDI = 1;
        else TC72_SDI = 0;
        
        TC72_SCK = 0;
        
        data <<= 1;
        if(TC72_SDO) data |= 0x01;
    }
    
	return ( data );
}

void TC72_Init(void)
{
    TC72_SCK_TRIS = 0;
    TC72_CE_TRIS = 0;
    TC72_SDI_TRIS = 0;
    TC72_SDO_TRIS = 1;
    
    TC72_CE = 0;
}

void TC72_Command(unsigned char command)
{
    TC72_CE = 1;
    Spi_transfer(0x80);
    Spi_transfer(command);
    TC72_CE = 0;
}

unsigned int TC72_Read_temp()
{
    unsigned char msb = 0;
    unsigned char lsb = 0;

    TC72_CE = 1;
    msb = Spi_transfer(0x02);
    lsb = Spi_transfer(0xFF);
    TC72_CE = 0;

    return ((unsigned int) ((msb << 8) | lsb));
}

#endif
