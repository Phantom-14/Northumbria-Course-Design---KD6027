//===============================
//Author: Yutong Zhu
//Data: 10/1/2022
//Descibtion: UART module source file
//Student Number: 18047451
//E-mail: w18047451@northumbria.ac.uk
//===============================
# include "uart.h"

void uart0_init(uint16_t baud_rate){
	
	SIM_SOPT2 |= SIM_SOPT2_UART0SRC(0x01);	//Set MCGFLLCLK as clock, 20.97Mhz
	SIM_SCGC4 |= SIM_SCGC4_UART0(0x1);			//Enable UART0 clock
	SIM_SCGC5 |= SIM_SCGC5_PORTA(0x1);
	
	PORTA_PCR1 |= PORT_PCR_MUX(0x02);
	PORTA_PCR2 |= PORT_PCR_MUX(0x02);				//Make PTA1->RX PTA2->TX ;
	
	UART0->C2 = 0; 													//Turn off uart0 before config
	
	uint16_t sbr = 20970000/(16 * baud_rate);//Calculate SBR
	
	UART0_BDH |= UART0_BDH_LBKDIE(0x0);
	UART0_BDH |= UART0_BDH_RXEDGIE(0x0);
	UART0_BDH |= UART0_BDH_SBNS(0x0);
	UART0_BDH |= (UART0_BDH_SBR_MASK & (sbr>>8));
	UART0_BDL = (uint8_t)(sbr & UART0_BDL_SBR_MASK); 
																					//Set Baud rate
	
	UART0_C1 = 0x00; 												//8-bit ,noparity
	UART0_C4 |= UART0_C4_OSR(0xF);					//over-sampling-ratio = 16
	UART0_C2 |= UART0_C2_TE(0x01);					//Transmit enable
	UART0_C2 |= UART0_C2_RE(0x01);					//Receiver enable
}

uint8_t uart0_sent_char(uint8_t ch){
		
	uint32_t i;
	
	for(i = 0 ; i < 0xffff ; i++){
		if(UART0_S1 & UART0_S1_TDRE_MASK){		//if Transmit Data Reg is Empty
			UART0_D = ch;
			break;															//break the check loop
		}
	}	if(i >= 0xffff){											//fail to sent the char
		return 0;
	}
	else
		return 1;															//sent successfully

}

uint8_t uart0_sent_string(char* str){
	
	uint8_t i ;
	
	for(i = 0; str[i] != '\0' ; i++)
	{
		if(!uart0_sent_char(str[i]))					//if fail sent a char,return 0
			return 0;
	}
	return 1;																//sent a string successfully
}

uint8_t uart0_reci_char(uint8_t* trigger){
	uint8_t  data;

	if (UART0_S1 & UART0_S1_RDRF_MASK){			//if Reciver Data Reg is Full
			data = UART0_D;
			*trigger = 1;												//Show recive a char
	}

	return data;
}

uint8_t uart0_reci_str(char* str){

	uint8_t reci_flag = 0;
	uint8_t ch;
	ch = uart0_reci_char(&reci_flag);
	if(reci_flag){														//if recive a character
		if(ch == 13){														//if recive a Enter
			uart0_sent_char('\r');
			uart0_sent_char('\n');
			return 1;															//when a string is end, return 1
		}
		else if(ch == 8){												//if recive a backspace
		
			if(strlen(str)>0){										//if the str is not empty, delate the last char
				str[strlen(str) - 1] = '\0';
			}
			
			uart0_sent_char('\b');								//HERE maybe need to be a function as backspace
			uart0_sent_char(' ');
			uart0_sent_char('\b');
		}
		else{
			str[strlen(str)] = ch;
			uart0_sent_char(ch);
		}
	}
	return 0;
}
