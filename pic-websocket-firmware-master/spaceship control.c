#include <16F886.h>
#device ADC=10 *=16

#include <serialinput.h>

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES PUT                      //Power Up Timer
#FUSES NOMCLR                   //Master Clear pin not enabled
#FUSES NOPROTECT                //Code not protected from reading
#FUSES NOCPD                    //No EE protection
#FUSES BROWNOUT                 //Brownout reset
#FUSES IESO                     //Internal External Switch Over mode enabled
#FUSES FCMEN                    //Fail-safe clock monitor enabled
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NODEBUG                  //No Debug mode for ICD
#FUSES NOWRT                    //Program memory not write protected
#FUSES BORV40                   //Brownout reset at 4.0V
#FUSES RESERVED                 //Used to set the reserved FUSE bits
#FUSES INTRC_IO 

#use delay(clock=8M)

#use rs232(baud=115200,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)

#define RUN_BUTTON   PIN_B7

void main()
{


   int i=0;
   delay_ms(200);
   getch();
   initSerInput();
   
   while(1) {
//!      gets(cmd);
//!      printf("OK - %s\r\n", cmd);
      if (!input(PIN_B7) && i==0) {
         printf("on\n"); 
         
         i=1;
      } else if (input(PIN_B7) && i==1) {
         printf("off\n"); 
         //output_toggle(PIN_B6);
         i=0;
      } else if (gblSerInputNewValueAvailable) {
         S=atof(gblSerInputBuffer[0]);
         V=atof(gblSerInputBuffer[1]);
         printf("S=%f, V=%f\n", S,V);
         
         gblSerInputNewValueAvailable=0;
      }
      
      //printf("i=%u",gblSerInputIndex);
      delay_ms(1);
      
      
   }


}

#include <serialinput.c>