#ifndef __ADC_INCLUDED__

#define __ADC_INCLUDED__ 
#define ADC_VREF_TYPE_5V 0x40
#define ADC_MAX_INPUT_VOLTAGE 5.0f
#define ADC_START_CYCLES 20
#define ADC_DEFAULT_MEAS 0 
#define ADC_DEFAULT_CHANNEL 0 
#define ADC_DEFAULT_INTERVAL 0 
#define ADC_DEFAULT_AVERAGED 10 

unsigned int ADCRead(unsigned char adc_input);
double ADCMeasureVoltage(unsigned char adc_channel);
void ADCInit( void );

unsigned int ADCRead(unsigned char adc_input)
{
     ADMUX=adc_input|ADC_VREF_TYPE_5V;
     // Start the AD conversion
     ADCSRA|=0x40;
     // Wait for the AD conversion to complete
     while ((ADCSRA & 0x10)==0)
          ;
     ADCSRA|=0x10;
     return ADCW;
}

double ADCMeasureVoltage(unsigned char adc_channel)
{
     static unsigned char previous_channel = 0xFF;
     unsigned char i;
     double voltage;
     if( adc_channel != previous_channel)
     {
          for(i = 0; i<ADC_START_CYCLES; i++)
          {
               ADCRead(adc_channel);
          }
          previous_channel = adc_channel;
     }
     voltage = ADCRead(adc_channel) * ADC_MAX_INPUT_VOLTAGE / 1024.0; 
     return voltage;
}

void ADCInit( void )
{
     ADMUX = ADC_VREF_TYPE_5V;
     ADCSRA = 0x84;
}
#endif /* __ADC_INCLUDED__ */

