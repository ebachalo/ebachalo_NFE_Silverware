
#include "project.h"
#include "drv_pwm.h"
#include "config.h"

#ifdef use_pwm_driver


#ifndef sys_clock_freq_hz
#define sys_clock_freq_hz 48000000
#warning sys_clock_freq_hz not present
#endif

#define pwm_divider 1
#define pwmtop (( sys_clock_freq_hz / pwmfreq ) - 1)

// pwm frequency checking macros
#if ( pwmtop< 1400 ) 
  // approx 34khz
	#undef pwmtop
	#define pwmtop 6000
	#warning pwm frequency too high
#endif

#if ( pwmtop> 65535 ) 
// under approx 732hz we add the divider by 4
	#undef pwmtop
	#define pwmtop (((sys_clock_freq_hz/4)/pwmfreq ) - 1)
	#undef pwm_divider
	#define pwm_divider 4
	//#warning pwm divide by 4 on
#endif

#if ( pwmtop> 65535 ) 
// approx 183hz is min frequency
	#undef pwmtop
	#undef pwm_divider
	#define pwmtop 6000
	#define pwm_divider 1
	#warning pwm frequency too low
#endif
// end pwm frequency macros


#ifdef pwm_pa0
#define pwm_pa0_pin gpio_pin_0
#define pwm_pa0_port gpioa
#define pwm_pa0_af gpio_af_2
#define pwm_pa0_pinsource gpio_pinsource0
#define pwm_pa0_timer tim2
#define pwm_pa0_channel ch1
#ifndef enable_tim2 
	#define enable_tim2
#endif
#endif

#ifdef pwm_pa1
#define pwm_pa1_pin gpio_pin_1
#define pwm_pa1_port gpioa
#define pwm_pa1_af gpio_af_2
#define pwm_pa1_pinsource gpio_pinsource1
#define pwm_pa1_timer tim2
#define pwm_pa1_channel ch2
#ifndef enable_tim2 
	#define enable_tim2
#endif
#endif


#ifdef pwm_pa2
#define pwm_pa2_pin gpio_pin_2
#define pwm_pa2_port gpioa
#define pwm_pa2_af gpio_af_2
#define pwm_pa2_pinsource gpio_pinsource2
#define pwm_pa2_timer tim2
#define pwm_pa2_channel ch3
#ifndef enable_tim2 
	#define enable_tim2
#endif
#endif


#ifdef pwm_pa3
#define pwm_pa3_pin gpio_pin_3
#define pwm_pa3_port gpioa
#define pwm_pa3_af gpio_af_2
#define pwm_pa3_pinsource gpio_pinsource3
#define pwm_pa3_timer tim2
#define pwm_pa3_channel ch4
#ifndef enable_tim2 
	#define enable_tim2
#endif
#endif


#ifdef pwm_pa4
#define pwm_pa4_pin gpio_pin_4
#define pwm_pa4_port gpioa
#define pwm_pa4_af gpio_af_4
#define pwm_pa4_pinsource gpio_pinsource4
#define pwm_pa4_timer tim14
#define pwm_pa4_channel ch1
#ifndef enable_tim14 
	#define enable_tim14
#endif
#endif

#ifdef pwm_pa5
#define pwm_pa5_pin gpio_pin_5
#define pwm_pa5_port gpioa
#define pwm_pa5_af gpio_af_2
#define pwm_pa5_pinsource gpio_pinsource5
#define pwm_pa5_timer tim2
#define pwm_pa5_channel ch1
#ifndef enable_tim2 
	#define enable_tim2
#endif
#endif


#ifdef pwm_pa6
#define pwm_pa6_pin gpio_pin_6
#define pwm_pa6_port gpioa
#define pwm_pa6_af gpio_af_1
#define pwm_pa6_pinsource gpio_pinsource6
#define pwm_pa6_timer tim3
#define pwm_pa6_channel ch1
#ifndef enable_tim3 
	#define enable_tim3
#endif
#endif


#ifdef pwm_pa7
#define pwm_pa7_pin gpio_pin_7
#define pwm_pa7_port gpioa
#define pwm_pa7_af gpio_af_1
#define pwm_pa7_pinsource gpio_pinsource7
#define pwm_pa7_timer tim3
#define pwm_pa7_channel ch2
#ifndef enable_tim3 
	#define enable_tim3
#endif
#endif


#ifdef pwm_pa8
#define pwm_pa8_pin gpio_pin_8
#define pwm_pa8_port gpioa
#define pwm_pa8_af gpio_af_2
#define pwm_pa8_pinsource gpio_pinsource8
#define pwm_pa8_timer tim1
#define pwm_pa8_channel ch1
#ifndef enable_tim1 
	#define enable_tim1
#endif
#endif

#ifdef pwm_pa9
#define pwm_pa9_pin gpio_pin_9
#define pwm_pa9_port gpioa
#define pwm_pa9_af gpio_af_2
#define pwm_pa9_pinsource gpio_pinsource9
#define pwm_pa9_timer tim1
#define pwm_pa9_channel ch2
#ifndef enable_tim1 
	#define enable_tim1
#endif
#endif


#ifdef pwm_pa10
#define pwm_pa10_pin gpio_pin_10
#define pwm_pa10_port gpioa
#define pwm_pa10_af gpio_af_2
#define pwm_pa10_pinsource gpio_pinsource10
#define pwm_pa10_timer tim1
#define pwm_pa10_channel ch3
#ifndef enable_tim1 
	#define enable_tim1
#endif
#endif

#ifdef pwm_pa11
#define pwm_pa11_pin gpio_pin_11
#define pwm_pa11_port gpioa
#define pwm_pa11_af gpio_af_2
#define pwm_pa11_pinsource gpio_pinsource11
#define pwm_pa11_timer tim1
#define pwm_pa11_channel ch4
#ifndef enable_tim1 
	#define enable_tim1
#endif
#endif



#ifdef pwm_pb0
#define pwm_pb0_pin gpio_pin_0
#define pwm_pb0_port gpiob
#define pwm_pb0_af gpio_af_1
#define pwm_pb0_pinsource gpio_pinsource0
#define pwm_pb0_timer tim3
#define pwm_pb0_channel ch3
#ifndef enable_tim3 
	#define enable_tim3
#endif
#endif

#ifdef pwm_pb1
#define pwm_pb1_pin gpio_pin_1
#define pwm_pb1_port gpiob
#define pwm_pb1_af gpio_af_1
#define pwm_pb1_pinsource gpio_pinsource1
#define pwm_pb1_timer tim3
#define pwm_pb1_channel ch4
#ifndef enable_tim3 
	#define enable_tim3
#endif
#endif

#ifdef pwm_pb8
#define pwm_pb8_pin gpio_pin_8
#define pwm_pb8_port gpiob
#define pwm_pb8_af gpio_af_2
#define pwm_pb8_pinsource gpio_pinsource8
#define pwm_pb8_timer tim16
#define pwm_pb8_channel ch1
#ifndef enable_tim16 
	#define enable_tim16
#endif
#endif

#ifndef disable_pwm_pins


void init_timer( tim_typedef* timx , int period);

tim_ocinittypedef  tim_ocinitstructure;

void pwm_init(void)
{
	
	gpio_inittypedef gpio_initstructure;
  
  gpio_initstructure.gpio_mode = gpio_mode_af;
  gpio_initstructure.gpio_speed = gpio_speed_50mhz;
  gpio_initstructure.gpio_otype = gpio_otype_pp;
  gpio_initstructure.gpio_pupd = gpio_pupd_nopull ;

	
// timer clock enable 
#ifdef enable_tim1	
  rcc_apb2periphclockcmd(rcc_apb2periph_tim1 , enable);  // pa8 , pa9
	
	init_timer( tim1 , pwmtop);
	
#endif	
#ifdef enable_tim2
	rcc_apb1periphclockcmd(rcc_apb1periph_tim2 , enable);		// pa0 , pa1
		
	init_timer( tim2 , pwmtop);
#endif

#ifdef enable_tim3
	rcc_apb1periphclockcmd(rcc_apb1periph_tim3 , enable); // pa6 , 7 , pb1
		
	init_timer( tim3 , pwmtop);
#endif


#ifdef enable_tim14
	rcc_apb1periphclockcmd(rcc_apb1periph_tim14 , enable);
	init_timer( tim14 , pwmtop);
#endif

#ifdef enable_tim16
    rcc_apb2periphclockcmd(rcc_apb2periph_tim16 , enable);  // pb8
	init_timer( tim16 , pwmtop);
#endif

	//rcc_apb1periphclockcmd(rcc_apb1periph_tim6 , enable);
	//rcc_apb1periphclockcmd(rcc_apb1periph_tim7 , enable);

  tim_ocinitstructure.tim_ocmode = tim_ocmode_pwm1;
  tim_ocinitstructure.tim_outputstate = tim_outputstate_enable;
  tim_ocinitstructure.tim_ocpolarity = tim_ocpolarity_high;
  tim_ocinitstructure.tim_ocidlestate = tim_ocidlestate_set;

  tim_ocinitstructure.tim_pulse = 0;
	

#ifdef pwm_pa0
  gpio_initstructure.gpio_pin = pwm_pa0_pin;
	gpio_init(pwm_pa0_port, &gpio_initstructure);

  gpio_pinafconfig(pwm_pa0_port, pwm_pa0_pinsource, pwm_pa0_af);
	
#if (pwm_pa0_channel==ch1) 
  tim_oc1init(pwm_pa0_timer, &tim_ocinitstructure);
#elif (pwm_pa0_channel==ch2) 
  tim_oc2init(pwm1_timer, &tim_ocinitstructure);
#elif (pwm_pa0_channel==ch3) 
  tim_oc3init(pwm_pa0_timer, &tim_ocinitstructure);
#elif (pwm_pa0_channel==ch4) 
  tim_oc4init(pwm_pa0_timer, &tim_ocinitstructure);
#endif

#endif


#ifdef pwm_pa1
  gpio_initstructure.gpio_pin = pwm_pa1_pin;
	gpio_init(pwm_pa1_port, &gpio_initstructure);

  gpio_pinafconfig(pwm_pa1_port, pwm_pa1_pinsource, pwm_pa1_af);
	
#if (pwm_pa1_channel==ch1) 
  tim_oc1init(pwm_pa1_timer, &tim_ocinitstructure);
#elif (pwm_pa1_channel==ch2) 
  tim_oc2init(pwm_pa1_timer, &tim_ocinitstructure);
#elif (pwm_pa1_channel==ch3) 
  tim_oc3init(pwm_pa1_timer, &tim_ocinitstructure);
#elif (pwm_pa1_channel==ch4) 
  tim_oc4init(pwm_pa1_timer, &tim_ocinitstructure);
#endif
#endif


#ifdef pwm_pa2
  gpio_initstructure.gpio_pin = pwm_pa2_pin;
	gpio_init(pwm_pa2_port, &gpio_initstructure);

  gpio_pinafconfig(pwm_pa2_port, pwm_pa2_pinsource, pwm_pa2_af);
	
#if (pwm_pa2_channel==ch1) 
  tim_oc1init(pwm_pa2_timer, &tim_ocinitstructure);
#elif (pwm_pa2_channel==ch2) 
  tim_oc2init(pwm_pa2_timer, &tim_ocinitstructure);
#elif (pwm_pa2_channel==ch3) 
  tim_oc3init(pwm_pa2_timer, &tim_ocinitstructure);
#elif (pwm_pa2_channel==ch4) 
  tim_oc4init(pwm_pa2_timer, &tim_ocinitstructure);
#endif
#endif


#ifdef pwm_pa3
  gpio_initstructure.gpio_pin = pwm_pa3_pin;
	gpio_init(pwm_pa3_port, &gpio_initstructure);

  gpio_pinafconfig(pwm_pa3_port, pwm_pa3_pinsource, pwm_pa3_af);
	
#if (pwm_pa3_channel==ch1) 
  tim_oc1init(pwm_pa3_timer, &tim_ocinitstructure);
#elif (pwm_pa3_channel==ch2) 
  tim_oc2init(pwm_pa3_timer, &tim_ocinitstructure);
#elif (pwm_pa3_channel==ch3) 
  tim_oc3init(pwm_pa3_timer, &tim_ocinitstructure);
#elif (pwm_pa3_channel==ch4) 
  tim_oc4init(pwm_pa3_timer, &tim_ocinitstructure);
#endif
#endif


#ifdef pwm_pa4
  gpio_initstructure.gpio_pin = pwm_pa4_pin;
	gpio_init(pwm_pa4_port, &gpio_initstructure);

  gpio_pinafconfig(pwm_pa4_port, pwm_pa4_pinsource, pwm_pa4_af);
	
#if (pwm_pa4_channel==ch1) 
  tim_oc1init(pwm_pa4_timer, &tim_ocinitstructure);
#elif (pwm_pa4_channel==ch2) 
  tim_oc2init(pwm_pa4_timer, &tim_ocinitstructure);
#elif (pwm_pa4_channel==ch3) 
  tim_oc3init(pwm_pa4_timer, &tim_ocinitstructure);
#elif (pwm_pa4_channel==ch4) 
  tim_oc4init(pwm_pa4_timer, &tim_ocinitstructure);
#endif
#endif


#ifdef pwm_pa5
  gpio_initstructure.gpio_pin = pwm_pa5_pin;
	gpio_init(pwm_pa5_port, &gpio_initstructure);

  gpio_pinafconfig(pwm_pa5_port, pwm_pa5_pinsource, pwm_pa5_af);
	
#if (pwm_pa5_channel==ch1) 
  tim_oc1init(pwm_pa5_timer, &tim_ocinitstructure);
#elif (pwm_pa5_channel==ch2) 
  tim_oc2init(pwm_pa5_timer, &tim_ocinitstructure);
#elif (pwm_pa5_channel==ch3) 
  tim_oc3init(pwm_pa5_timer, &tim_ocinitstructure);
#elif (pwm_pa5_channel==ch4) 
  tim_oc4init(pwm_pa5_timer, &tim_ocinitstructure);
#endif
#endif


#ifdef pwm_pa6
  gpio_initstructure.gpio_pin = pwm_pa6_pin;
	gpio_init(pwm_pa6_port, &gpio_initstructure);

  gpio_pinafconfig(pwm_pa6_port, pwm_pa6_pinsource, pwm_pa6_af);
	
#if (pwm_pa6_channel==ch1) 
  tim_oc1init(pwm_pa6_timer, &tim_ocinitstructure);
#elif (pwm_pa6_channel==ch2) 
  tim_oc2init(pwm_pa6_timer, &tim_ocinitstructure);
#elif (pwm_pa6_channel==ch3) 
  tim_oc3init(pwm_pa6_timer, &tim_ocinitstructure);
#elif (pwm_pa6_channel==ch4) 
  tim_oc4init(pwm_pa6_timer, &tim_ocinitstructure);
#endif

#endif



#ifdef pwm_pa7
  gpio_initstructure.gpio_pin = pwm_pa7_pin;
	gpio_init(pwm_pa7_port, &gpio_initstructure);

  gpio_pinafconfig(pwm_pa7_port, pwm_pa7_pinsource, pwm_pa7_af);
	
#if (pwm_pa7_channel==ch1) 
  tim_oc1init(pwm_pa7_timer, &tim_ocinitstructure);
#elif (pwm_pa7_channel==ch2) 
  tim_oc2init(pwm_pa7_timer, &tim_ocinitstructure);
#elif (pwm_pa7_channel==ch3) 
  tim_oc3init(pwm_pa7_timer, &tim_ocinitstructure);
#elif (pwm_pa7_channel==ch4) 
  tim_oc4init(pwm_pa7_timer, &tim_ocinitstructure);
#endif

#endif


#ifdef pwm_pa8
  gpio_initstructure.gpio_pin = pwm_pa8_pin;
	gpio_init(pwm_pa8_port, &gpio_initstructure);

  gpio_pinafconfig(pwm_pa8_port, pwm_pa8_pinsource, pwm_pa8_af);
	
#if (pwm_pa8_channel==ch1) 
  tim_oc1init(pwm_pa8_timer, &tim_ocinitstructure);
#elif (pwm_pa8_channel==ch2) 
  tim_oc2init(pwm_pa8_timer, &tim_ocinitstructure);
#elif (pwm_pa8_channel==ch3) 
  tim_oc3init(pwm_pa8_timer, &tim_ocinitstructure);
#elif (pwm_pa8_channel==ch4) 
  tim_oc4init(pwm_pa8_timer, &tim_ocinitstructure);
#endif
#endif


#ifdef pwm_pa9
  gpio_initstructure.gpio_pin = pwm_pa9_pin;
	gpio_init(pwm_pa9_port, &gpio_initstructure);

  gpio_pinafconfig(pwm_pa9_port, pwm_pa9_pinsource, pwm_pa9_af);
	
#if (pwm_pa9_channel==ch1) 
  tim_oc1init(pwm_pa9_timer, &tim_ocinitstructure);
#elif (pwm_pa9_channel==ch2) 
  tim_oc2init(pwm_pa9_timer, &tim_ocinitstructure);
#elif (pwm_pa9_channel==ch3) 
  tim_oc3init(pwm_pa9_timer, &tim_ocinitstructure);
#elif (pwm_pa9_channel==ch4) 
  tim_oc4init(pwm_pa9_timer, &tim_ocinitstructure);
#endif
#endif



#ifdef pwm_pa10
  gpio_initstructure.gpio_pin = pwm_pa10_pin;
	gpio_init(pwm_pa10_port, &gpio_initstructure);

  gpio_pinafconfig(pwm_pa10_port, pwm_pa10_pinsource, pwm_pa10_af);
	
#if (pwm_pa10_channel==ch1) 
  tim_oc1init(pwm_pa10_timer, &tim_ocinitstructure);
#elif (pwm_pa10_channel==ch2) 
  tim_oc2init(pwm_pa10_timer, &tim_ocinitstructure);
#elif (pwm_pa10_channel==ch3) 
  tim_oc3init(pwm_pa10_timer, &tim_ocinitstructure);
#elif (pwm_pa10_channel==ch4) 
  tim_oc4init(pwm_pa10_timer, &tim_ocinitstructure);
#endif
#endif



#ifdef pwm_pa11
  gpio_initstructure.gpio_pin = pwm_pa11_pin;
	gpio_init(pwm_pa11_port, &gpio_initstructure);

  gpio_pinafconfig(pwm_pa11_port, pwm_pa11_pinsource, pwm_pa11_af);
	
#if (pwm_pa11_channel==ch1) 
  tim_oc1init(pwm_pa11_timer, &tim_ocinitstructure);
#elif (pwm_pa11_channel==ch2) 
  tim_oc2init(pwm_pa11_timer, &tim_ocinitstructure);
#elif (pwm_pa11_channel==ch3) 
  tim_oc3init(pwm_pa11_timer, &tim_ocinitstructure);
#elif (pwm_pa11_channel==ch4) 
  tim_oc4init(pwm_pa11_timer, &tim_ocinitstructure);
#endif
#endif


#ifdef pwm_pb0
  gpio_initstructure.gpio_pin = pwm_pb0_pin;
	gpio_init(pwm_pb0_port, &gpio_initstructure);

  gpio_pinafconfig(pwm_pb0_port, pwm_pb0_pinsource, pwm_pb0_af);
	
#if (pwm_pb0_channel==ch1) 
  tim_oc1init(pwm_pb0_timer, &tim_ocinitstructure);
#elif (pwm_pb0_channel==ch2) 
  tim_oc2init(pwm_pb0_timer, &tim_ocinitstructure);
#elif (pwm_pb0_channel==ch3) 
  tim_oc3init(pwm_pb0_timer, &tim_ocinitstructure);
#elif (pwm_pb0_channel==ch4) 
  tim_oc4init(pwm_pb0_timer, &tim_ocinitstructure);
#endif

#endif



#ifdef pwm_pb1
  gpio_initstructure.gpio_pin = pwm_pb1_pin;
	gpio_init(pwm_pb1_port, &gpio_initstructure);

  gpio_pinafconfig(pwm_pb1_port, pwm_pb1_pinsource, pwm_pb1_af);
	
#if (pwm_pb1_channel==ch1) 
  tim_oc1init(pwm_pb1_timer, &tim_ocinitstructure);
#elif (pwm_pb1_channel==ch2) 
  tim_oc2init(pwm_pb1_timer, &tim_ocinitstructure);
#elif (pwm_pb1_channel==ch3) 
  tim_oc3init(pwm_pb1_timer, &tim_ocinitstructure);
#elif (pwm_pb1_channel==ch4) 
  tim_oc4init(pwm_pb1_timer, &tim_ocinitstructure);
#endif

#endif

#ifdef pwm_pb8
  gpio_initstructure.gpio_pin = pwm_pb8_pin;
	gpio_init(pwm_pb8_port, &gpio_initstructure);

  gpio_pinafconfig(pwm_pb8_port, pwm_pb8_pinsource, pwm_pb8_af);
	
#if (pwm_pb8_channel==ch1) 
  tim_oc1init(pwm_pb8_timer, &tim_ocinitstructure);
#elif (pwm_pb8_channel==ch2) 
  tim_oc2init(pwm_pb8_timer, &tim_ocinitstructure);
#elif (pwm_pb8_channel==ch3) 
  tim_oc3init(pwm_pb8_timer, &tim_ocinitstructure);
#elif (pwm_pb8_channel==ch4) 
  tim_oc4init(pwm_pb8_timer, &tim_ocinitstructure);
#endif

#endif



	
#ifdef enable_tim1	
	tim_cmd(tim1, enable);
  tim_ctrlpwmoutputs(tim1, enable);
#endif 


#ifdef enable_tim2
  tim_cmd(tim2, enable);
  tim_ctrlpwmoutputs(tim2, enable);
#endif


#ifdef enable_tim3
  tim_cmd(tim3, enable);
  tim_ctrlpwmoutputs(tim3, enable);
#endif


#ifdef enable_tim14
  tim_cmd(tim14, enable);
  // t14 does not support pwm out enable
  //tim_ctrlpwmoutputs(tim14, enable);
#endif

#ifdef enable_tim16
  tim_cmd(tim16, enable);
  tim_ctrlpwmoutputs(tim16, enable);
#endif

}

void init_timer( tim_typedef* timx , int period)
{
	tim_timebaseinittypedef  tim_timebasestructure;
	
	tim_timebasestructure.tim_prescaler = pwm_divider - 1;
  tim_timebasestructure.tim_countermode = tim_countermode_up;
  tim_timebasestructure.tim_period = period;
  tim_timebasestructure.tim_clockdivision = 0;
  tim_timebasestructure.tim_repetitioncounter = 0;

  tim_timebaseinit( timx, &tim_timebasestructure);
	
}


extern int failsafe;
unsigned long motorbeeptime = 0;
int beepon = 0;
#include "drv_time.h"

#ifndef motor_beeps_timeout
// default value if not defined elsewhere
#define motor_beeps_timeout 30e6
#endif

#define motor_beeps_pwm_on 0.2
#define motor_beeps_pwm_off 0.0

void motorbeep( void)
{
	if (failsafe)
	{
		unsigned long time = gettime();
		if (!motorbeeptime)
				motorbeeptime = time;
		else
			if ( time - motorbeeptime > motor_beeps_timeout)
			{
				if (!beepon&&(time%2000000 < 125000))
				{
				for ( int i = 0 ; i <= 3 ; i++)
					{
					pwm_set( i , motor_beeps_pwm_on);
					beepon=1;				
					}
				}
				else
				{
				for ( int i = 0 ; i <= 3 ; i++)
					{
					pwm_set( i , motor_beeps_pwm_off);
					beepon=0;				
					}
					
				}
				
			}
	}
	else
		motorbeeptime = 0;
}


#include  <math.h>

void pwm_set( uint8_t number , float pwmf)
{
	
int pwm = pwmf * pwmtop ;
	
if ( pwm < 0 ) pwm = 0;
if ( pwm > pwmtop ) pwm = pwmtop;

	
  switch( number)
	{
		case 0:
			#ifdef motor0_pin_pa0
			tim2->ccr1 = (uint16_t) pwm;
			#endif
			#ifdef motor0_pin_pa1
			tim2->ccr2 = (uint16_t) pwm;
			#endif
            #ifdef motor0_pin_pa2
			tim2->ccr3 = (uint16_t) pwm;
			#endif
            #ifdef motor0_pin_pa3
			tim2->ccr4 = (uint16_t) pwm;
			#endif
            #ifdef motor0_pin_pa4
			tim14->ccr1 = (uint16_t) pwm;
			#endif
            #ifdef motor0_pin_pa5
			tim2->ccr1 = (uint16_t) pwm;
			#endif
            #ifdef motor0_pin_pa6
			tim3->ccr1 = (uint16_t) pwm;
			#endif
            #ifdef motor0_pin_pa7
			tim3->ccr2 = (uint16_t) pwm;
			#endif
			#ifdef motor0_pin_pa8
			tim1->ccr1 = (uint16_t) pwm;
			#endif
			#ifdef motor0_pin_pa9
			tim1->ccr2 = (uint16_t) pwm;
			#endif	
			#ifdef motor0_pin_pa10
			tim1->ccr3 = (uint16_t) pwm;
			#endif	
			#ifdef motor0_pin_pa11
			tim1->ccr4 = (uint16_t) pwm;
			#endif
            #ifdef motor0_pin_pb0
			tim3->ccr3 = (uint16_t) pwm;
			#endif	
            #ifdef motor0_pin_pb1
			tim3->ccr4 = (uint16_t) pwm;
			#endif		
            #ifdef motor0_pin_pb8
			tim16->ccr1 = (uint16_t) pwm;
			#endif	            
		break;
		
		case 1:
			#ifdef motor1_pin_pa0
			tim2->ccr1 = (uint16_t) pwm;
			#endif
			#ifdef motor1_pin_pa1
			tim2->ccr2 = (uint16_t) pwm;
            #endif
            #ifdef motor1_pin_pa2
			tim2->ccr3 = (uint16_t) pwm;
			#endif
            #ifdef motor1_pin_pa3
			tim2->ccr4 = (uint16_t) pwm;
			#endif
            #ifdef motor1_pin_pa4
			tim14->ccr1 = (uint16_t) pwm;
			#endif
            #ifdef motor1_pin_pa5
			tim2->ccr1 = (uint16_t) pwm;
			#endif
            #ifdef motor1_pin_pa6
			tim3->ccr1 = (uint16_t) pwm;
			#endif
            #ifdef motor1_pin_pa7
			tim3->ccr2 = (uint16_t) pwm;
			#endif
			#ifdef motor1_pin_pa8
			tim1->ccr1 = (uint16_t) pwm;
			#endif
			#ifdef motor1_pin_pa9
			tim1->ccr2 = (uint16_t) pwm;
			#endif		
            #ifdef motor1_pin_pa10
			tim1->ccr3 = (uint16_t) pwm;
			#endif	
			#ifdef motor1_pin_pa11
			tim1->ccr4 = (uint16_t) pwm;
			#endif	
            #ifdef motor1_pin_pb0
			tim3->ccr3 = (uint16_t) pwm;
			#endif	
            #ifdef motor1_pin_pb1
			tim3->ccr4 = (uint16_t) pwm;
            #endif
            #ifdef motor1_pin_pb8
			tim16->ccr1 = (uint16_t) pwm;
			#endif	      
		break;
		
		case 2:
			#ifdef motor2_pin_pa0
			tim2->ccr1 = (uint16_t) pwm;
			#endif
			#ifdef motor2_pin_pa1
			tim2->ccr2 = (uint16_t) pwm;
			#endif
            #ifdef motor2_pin_pa2
			tim2->ccr3 = (uint16_t) pwm;
			#endif
            #ifdef motor2_pin_pa3
			tim2->ccr4 = (uint16_t) pwm;
			#endif
            #ifdef motor2_pin_pa4
			tim14->ccr1 = (uint16_t) pwm;
			#endif
			#ifdef motor2_pin_pa5
			tim2->ccr1 = (uint16_t) pwm;
			#endif
            #ifdef motor2_pin_pa6
			tim3->ccr1 = (uint16_t) pwm;
			#endif
            #ifdef motor2_pin_pa7
			tim3->ccr2 = (uint16_t) pwm;
			#endif
			#ifdef motor2_pin_pa8
			tim1->ccr1 = (uint16_t) pwm;
			#endif
			#ifdef motor2_pin_pa9
			tim1->ccr2 = (uint16_t) pwm;
			#endif	
			#ifdef motor2_pin_pa10
			tim1->ccr3 = (uint16_t) pwm;
			#endif	
			#ifdef motor2_pin_pa11
			tim1->ccr4 = (uint16_t) pwm;
			#endif	
            #ifdef motor2_pin_pb0
			tim3->ccr3 = (uint16_t) pwm;
			#endif	
            #ifdef motor2_pin_pb1
			tim3->ccr4 = (uint16_t) pwm; 
            #endif  
            #ifdef motor2_pin_pb8
			tim16->ccr1 = (uint16_t) pwm;
			#endif	      
		break;
		
		case 3: 
			#ifdef motor3_pin_pa0
			tim2->ccr1 = (uint16_t) pwm;
			#endif
			#ifdef motor3_pin_pa1
			tim2->ccr2 = (uint16_t) pwm;
			#endif
            #ifdef motor3_pin_pa2
			tim2->ccr3 = (uint16_t) pwm;
			#endif
            #ifdef motor3_pin_pa3
			tim2->ccr4 = (uint16_t) pwm;
			#endif
            #ifdef motor3_pin_pa4
			tim14->ccr1 = (uint16_t) pwm;
			#endif
            #ifdef motor3_pin_pa5
			tim2->ccr1 = (uint16_t) pwm;
			#endif
            #ifdef motor3_pin_pa6
			tim3->ccr1 = (uint16_t) pwm;
			#endif
            #ifdef motor3_pin_pa7
			tim3->ccr2 = (uint16_t) pwm;
			#endif
			#ifdef motor3_pin_pa8
			tim1->ccr1 = (uint16_t) pwm;
			#endif
			#ifdef motor3_pin_pa9
			tim1->ccr2 = (uint16_t) pwm;
			#endif		
            #ifdef motor3_pin_pa10
			tim1->ccr3 = (uint16_t) pwm;
			#endif	
			#ifdef motor3_pin_pa11
			tim1->ccr4 = (uint16_t) pwm;
            #endif
            #ifdef motor3_pin_pb0
			tim3->ccr3 = (uint16_t) pwm;
			#endif	
            #ifdef motor3_pin_pb1
			tim3->ccr4 = (uint16_t) pwm;
			#endif	
            #ifdef motor3_pin_pb8
			tim16->ccr1 = (uint16_t) pwm;
			#endif	
		break;
		
		default:
			// handle error;
			//
		break;	
				
	}
	
}







#else
// pwm pins disabled
void pwm_init(void)
{
}

void pwm_set( uint8_t number , float pwm)
{
}

#endif 

#endif // end use_pwm_driver


