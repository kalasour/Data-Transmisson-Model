#include <16F886.h>
#device ADC = 10 *= 16

#include <serialinput.h>
#include <stdio.h>
#include <string.h>
#FUSES NOWDT     //No Watch Dog Timer
#FUSES PUT       //Power Up Timer
#FUSES NOMCLR    //Master Clear pin not enabled
#FUSES NOPROTECT //Code not protected from reading
#FUSES NOCPD     //No EE protection
#FUSES BROWNOUT  //Brownout reset
#FUSES IESO      //Internal External Switch Over mode enabled
#FUSES FCMEN     //Fail-safe clock monitor enabled
#FUSES NOLVP     //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NODEBUG   //No Debug mode for ICD
#FUSES NOWRT     //Program memory not write protected
#FUSES BORV40    //Brownout reset at 4.0V
#FUSES RESERVED  //Used to set the reserved FUSE bits
#FUSES INTRC_IO

#use delay(clock = 8M)

#use rs232(baud = 115200, parity = N, xmit = PIN_C6, rcv = PIN_C7, bits = 8)

#define RUN_BUTTON PIN_B7
char text[50];
int ct = 0;
void main()
{
   int dec = 0;
   setup_adc_ports(sAN0); // setup PIN A0 as analog input
   setup_adc(ADC_CLOCK_INTERNAL);
   delay_ms(2000);
   printf("Program started!\n");
   set_adc_channel(0); // set the ADC chaneel to read
   // wait for the sensor reading to finish
   int count = 0;
   int start = 0;
   memset(&text[0], '\0', sizeof(text));
   printf("Auto carribrate  started!\n");
   unsigned long value, max, min, i = 0, time = 0;

   for (i = 0; i < 1000; i++)
   {
      value = read_adc();
      if (i == 0)
      {
         max = value;
         min = value;
      }
      else
      {
         if (value > max)
            max = value;
         if (value < min)
            min = value;
      }
      delay_ms(5);
      //!         printf("Sensor value = %Lu\r\n", value);
   }
   printf("Auto carribrate  End max = %Lu ,min = %Lu\nmid = %Lu\n", max, min, (max + min) / 2);
    delay_ms(1000);
   while (1)
   {
      dec = 0;
      if (start == 1)
         time = time + 1;
      if (read_adc() >= (max + min) / 2)
      {
         start = 1;
         delay_ms(75);
         for (count = 0; count < 8; count++)
         {
            if (read_adc() >= (max + min) / 2)
            {
               dec = (dec * 2) + 1;
            }
            else
            {
               dec = dec * 2;
            }
            delay_ms(50);
         }
         text[ct] = dec;
         if (text[ct] == '\n' || time >= 30000)
         {
            printf("%s", text);
            if (time >= (30000))
               printf("- TIME OUT (%Lu)\n", time);
            memset(&text[0], '\0', sizeof(text));
            start = 0;
            time = 0;
            ct = 0;
         }
         else
         {
            ct++;
         }
      }
   }
}

#include <serialinput.c>
