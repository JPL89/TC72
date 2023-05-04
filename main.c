// @File		MAIN.C		 		
// @Author		JOSIMAR PEREIRA LEITE
// @country		BRAZIL
// @Date		01/05/23
//
//
// Copyright (C) 2023 JOSIMAR PEREIRA LEITE
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
#include "utils.h"
#include "ks0066.h"
#include "tc72.h"

void main(void)
{
    __delay_ms(500);

    PIC18F2520();   
    
    KS0066_Init();    

    KS0066_Clear(0);    

    KS0066_Clear(1);    
    
    KS0066_Goto(0, 0);
        
    TC72_Init();
    
    unsigned char t = 0;
    
    TC72_Command(TC72_CONTINUOUS_CONVERTION);
    
    while(1)
    {               
        t = TC72_Read_temp();
        
        KS0066_Clear(0);    
    
        KS0066_Goto(0, 0);
        
        KS0066_Int( t );
        
        __delay_ms(500);
    }
    
    return;
}