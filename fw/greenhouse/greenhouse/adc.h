/*
 * adc.h
 *
 * Created: 08.12.2021 8:14:01
 *  Author: Martin
 */ 


#ifndef ADC_H_
#define ADC_H_

/** @brief Set prescaler 128 --> 111 */
#define ADC_set_prescaler_128()		ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
/** @brief Set prescaler 64 --> 110 */
#define ADC_set_prescaler_64()		ADCSRA &= ~(1<<ADPS0); ADCSRA |= (1<<ADPS1) | (1<<ADPS2);
/** @brief Set prescaler 32 --> 101 */
#define ADC_set_prescaler_32()		ADCSRA &= ~(1<<ADPS1); ADCSRA |= (1<<ADPS2) | (1<<ADPS0);
/** @brief Set prescaler 16 --> 100 */
#define ADC_set_prescaler_16()		ADCSRA &= ~((1<<ADPS1) | (1<<ADPS0)); ADCSRA |= (1<<ADPS2);
/** @brief Set prescaler 8 --> 011 */
#define ADC_set_prescaler_8()		ADCSRA &= ~(1<<ADPS2); ADCSRA |= (1<<ADPS1) | (1<<ADPS0);
/** @brief Set prescaler 4 --> 010 */
#define ADC_set_prescaler_4()		ADCSRA &= ~((1<<ADPS2) | (1<<ADPS0)); ADCSRA |= (1<<ADPS1);
/** @brief Set prescaler 2 --> 000 */
#define ADC_set_prescaler_2()		ADCSRA &= ~((1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0));


/** @brief Set reference to AREF pin */
#define ADC_set_reference_AREF()		ADMUX &= ~((1<<REFS1) | (1<<REFS0));
/** @brief Set reference to AVCC */
#define ADC_set_reference_AVCC()		ADMUX &= ~(1<<REFS1); ADMUX |= (1<<REFS0);
/** @brief Set reference to internal 1.1V */
#define ADC_set_reference_INTERNAL()	ADMUX |= (1<<REFS1) | (1<<REFS0);

/** @brief Enable ADC */
#define ADC_enable()		ADCSRA |= (1<<ADEN);
/** @brief Disable ADC */
#define ADC_disable()		ADCSRA &= ~(1<<ADEN);

/** @brief Select ADC channel 0 */
#define ADC_select_channel_0()	ADMUX &= ~((1<<MUX3) | (1<<MUX2) | (1<<MUX1) | (1<<MUX0));
/** @brief Select ADC channel 1 */
#define ADC_select_channel_1()	ADMUX &= ~((1<<MUX3) | (1<<MUX2) | (1<<MUX1)); ADMUX |= (1<<MUX0);
/** @brief Select ADC channel 2 */
#define ADC_select_channel_2() ADMUX &= ~((1<<MUX3) | (1<<MUX2) | (1<<MUX0)); ADMUX |= (1<<MUX1);
/** @brief Select ADC channel 3 */
#define ADC_select_channel_3()	ADMUX &= ~((1<<MUX3) | (1<<MUX2)); ADMUX |= (1<<MUX1) | (1<<MUX0);
/** @brief Select ADC channel 4 */
#define ADC_select_channel_4()	ADMUX &= ~((1<<MUX3) | (1<<MUX1) | (1<<MUX0)); ADMUX |= (1<<MUX2);
/** @brief Select ADC channel 5 */
#define ADC_select_channel_5()	ADMUX &= ~((1<<MUX3) | (1<<MUX1)); ADMUX |= (1<<MUX2) | (1<<MUX0);
/** @brief Select ADC channel 6 */
#define ADC_select_channel_6()	ADMUX &= ~((1<<MUX3) | (1<<MUX0)); ADMUX |= (1<<MUX2) | (1<<MUX1);
/** @brief Select ADC channel 7 */
#define ADC_select_channel_7()	ADMUX &= ~(1<<MUX3); ADMUX |= (1<<MUX2) | (1<<MUX1) | (1<<MUX0);
/** @brief Select ADC channel 8 */
#define ADC_select_channel_8()	ADMUX &= ~((1<<MUX2) | (1<<MUX1) | (1<<MUX0)); ADMUX |= (1<<MUX3);

/** @brief Enable interrupt after ADC conversion completed */
#define ADC_enable_conversion_complete_interrupt()		ADCSRA |= (1<<ADIE);
/** @brief Disable interrupt after ADC conversion completed */
#define ADC_disable_conversion_complete_interrupt()		ADCSRA &= ~(1<<ADIE);

/** @brief Start AD conversion */
#define ADC_start()		ADCSRA |= (1<<ADSC);

#endif /* ADC_H_ */