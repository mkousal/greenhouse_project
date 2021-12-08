/*
 * adc.h
 *
 * Created: 08.12.2021 8:14:01
 *  Author: Martin
 */ 


#ifndef ADC_H_
#define ADC_H_


#define ADC_set_prescaler_128()		ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);

#define ADC_set_prescaler_64()		ADCSRA &= ~(1<<ADPS0); ADCSRA |= (1<<ADPS1) | (1<<ADPS2);

#define ADC_set_prescaler_32()		ADCSRA &= ~(1<<ADPS1); ADCSRA |= (1<<ADPS2) | (1<<ADPS0);

#define ADC_set_prescaler_16()		ADCSRA &= ~((1<<ADPS1) | (1<<ADPS0)); ADCSRA |= (1<<ADPS2);

#define ADC_set_prescaler_8()		ADCSRA &= ~(1<<ADPS2); ADCSRA |= (1<<ADPS1) | (1<<ADPS0);

#define ADC_set_prescaler_4()		ADCSRA &= ~((1<<ADPS2) | (1<<ADPS0)); ADCSRA |= (1<<ADPS1);

#define ADC_set_prescaler_2()		ADCSRA &= ~((1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0));



#define ADC_set_reference_AREF()		ADMUX &= ~((1<<REFS1) | (1<<REFS0));

#define ADC_set_reference_AVCC()		ADMUX &= ~(1<<REFS1); ADMUX |= (1<<REFS0);

#define ADC_set_reference_INTERNAL()	ADMUX |= (1<<REFS1) | (1<<REFS0);


#define ADC_enable()		ADCSRA |= (1<<ADEN);

#define ADC_disable()		ADCSRA &= ~(1<<ADEN);


#define ADC_select_channel_0()	ADMUX &= ~((1<<MUX3) | (1<<MUX2) | (1<<MUX1) | (1<<MUX0));

#define ADC_select_channel_1()	ADMUX &= ~((1<<MUX3) | (1<<MUX2) | (1<<MUX1)); ADMUX |= (1<<MUX0);

#define ADC_select_channel_2() ADMUX &= ~((1<<MUX3) | (1<<MUX2) | (1<<MUX0)); ADMUX |= (1<<MUX1);

#define ADC_select_channel_3()	ADMUX &= ~((1<<MUX3) | (1<<MUX2)); ADMUX |= (1<<MUX1) | (1<<MUX0);

#define ADC_select_channel_4()	ADMUX &= ~((1<<MUX3) | (1<<MUX1) | (1<<MUX0)); ADMUX |= (1<<MUX2);

#define ADC_select_channel_5()	ADMUX &= ~((1<<MUX3) | (1<<MUX1)); ADMUX |= (1<<MUX2) | (1<<MUX0);

#define ADC_select_channel_6()	ADMUX &= ~((1<<MUX3) | (1<<MUX0)); ADMUX |= (1<<MUX2) | (1<<MUX1);

#define ADC_select_channel_7()	ADMUX &= ~(1<<MUX3); ADMUX |= (1<<MUX2) | (1<<MUX1) | (1<<MUX0);

#define ADC_select_channel_8()	ADMUX &= ~((1<<MUX2) | (1<<MUX1) | (1<<MUX0)); ADMUX |= (1<<MUX3);

#define ADC_enable_conversion_complete_interrupt()		ADCSRA |= (1<<ADIE);

#define ADC_disable_conversion_complete_interrupt()		ADCSRA &= ~(1<<ADIE);

#endif /* ADC_H_ */