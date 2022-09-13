 /******************************************************************************
 *
 * Module: PORT
 *
 * File Name: Port_PBcfg.c
 *
 * Description: Post Build Configuration Source file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Nabil Gamal
 ******************************************************************************/

#include "Port.h"

/*
 * Module Version 1.0.0
 */
#define PORT_PBCFG_SW_MAJOR_VERSION              (1U)
#define PORT_PBCFG_SW_MINOR_VERSION              (0U)
#define PORT_PBCFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_PBCFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_PBCFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_PBCFG_AR_RELEASE_PATCH_VERSION     (3U)

/* AUTOSAR Version checking between Port_PBcfg.c and Port.h files */
#if ((PORT_PBCFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of PBcfg.c does not match the expected version"
#endif

/* Software Version checking between Port_PBcfg.c and Port.h files */
#if ((PORT_PBCFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_PBCFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_PBCFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of PBcfg.c does not match the expected version"
#endif

/* PB structure used with Dio_Init API */
const Port_ConfigType Port_Configuration = {
                                            
                                             /* Port A Pin Configuraion */
                                             PORTA_PIN0_ID, PORT_A, DEFAULT, DIO_MODE, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF,INITIAL_VALUE_LOW,
                                             
                                             PORTA_PIN1_ID, PORT_A, DEFAULT, DIO_MODE, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF,INITIAL_VALUE_LOW,
                                             
                                             PORTA_PIN2_ID, PORT_A, DEFAULT, DIO_MODE, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF,INITIAL_VALUE_LOW,
                                             
                                             PORTA_PIN3_ID, PORT_A, DEFAULT, DIO_MODE, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF,INITIAL_VALUE_LOW,
                                             
                                             PORTA_PIN4_ID, PORT_A, DEFAULT, DIO_MODE, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF,INITIAL_VALUE_LOW,
                                             
                                             PORTA_PIN5_ID, PORT_A, DEFAULT, DIO_MODE, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF,INITIAL_VALUE_LOW,
                                             
                                             PORTA_PIN6_ID, PORT_A, DEFAULT, DIO_MODE, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF,INITIAL_VALUE_LOW,
                                             
                                             PORTA_PIN7_ID, PORT_A, DEFAULT, DIO_MODE, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF,INITIAL_VALUE_LOW,
                                             
                                             /* ************************************************************************************************************************ */
                                             
                                             
                                             /* Port B Pin Configuraion */
                                             PORTB_PIN0_ID, PORT_B, DEFAULT, DIO_MODE, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF,INITIAL_VALUE_LOW,
                                             
                                             PORTB_PIN1_ID, PORT_B, DEFAULT, DIO_MODE, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF,INITIAL_VALUE_LOW,
                                             
                                             PORTB_PIN2_ID, PORT_B, DEFAULT, DIO_MODE, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF,INITIAL_VALUE_LOW,
                                             
                                             PORTB_PIN3_ID, PORT_B, DEFAULT, DIO_MODE, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF,INITIAL_VALUE_LOW,
                                             
                                             PORTB_PIN4_ID, PORT_B, DEFAULT, DIO_MODE, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF,INITIAL_VALUE_LOW,
                                             
                                             PORTB_PIN5_ID, PORT_B, DEFAULT, DIO_MODE, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF,INITIAL_VALUE_LOW,
                                             
                                             PORTB_PIN6_ID, PORT_B, DEFAULT, DIO_MODE, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF,INITIAL_VALUE_LOW,
                                             
                                             PORTB_PIN7_ID, PORT_B, DEFAULT, DIO_MODE, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF,INITIAL_VALUE_LOW,
                                             
                                             /* ************************************************************************************************************************ */
                                             
                                             
                                             /* Port C Pin Configuraion */
                                             PORTC_PIN4_ID, PORT_C, DEFAULT, DIO_MODE, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF,INITIAL_VALUE_LOW,
                                             
                                             PORTC_PIN5_ID, PORT_C, DEFAULT, DIO_MODE, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF,INITIAL_VALUE_LOW,
                                             
                                             PORTC_PIN6_ID, PORT_C, DEFAULT, DIO_MODE, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF,INITIAL_VALUE_LOW,
                                             
                                             PORTC_PIN7_ID, PORT_C, DEFAULT, DIO_MODE, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF,INITIAL_VALUE_LOW,
                                             
                                             /* ************************************************************************************************************************ */
                                             
                                             
                                             /* Port D Pin Configuraion */
                                             PORTD_PIN0_ID, PORT_D, DEFAULT, DIO_MODE, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF,INITIAL_VALUE_LOW,
                                             
                                             PORTD_PIN1_ID, PORT_D, DEFAULT, DIO_MODE, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF,INITIAL_VALUE_LOW,
                                             
                                             PORTD_PIN2_ID, PORT_D, DEFAULT, DIO_MODE, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF,INITIAL_VALUE_LOW,
                                             
                                             PORTD_PIN3_ID, PORT_D, DEFAULT, DIO_MODE, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF,INITIAL_VALUE_LOW,
                                             
                                             PORTD_PIN4_ID, PORT_D, DEFAULT, DIO_MODE, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF,INITIAL_VALUE_LOW,
                                             
                                             PORTD_PIN5_ID, PORT_D, DEFAULT, DIO_MODE, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF,INITIAL_VALUE_LOW,
                                             
                                             PORTD_PIN6_ID, PORT_D, DEFAULT, DIO_MODE, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF,INITIAL_VALUE_LOW,
                                             
                                             PORTD_PIN7_ID, PORT_D, DEFAULT, DIO_MODE, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF,INITIAL_VALUE_LOW,
                                             
                                             /* ************************************************************************************************************************ */
                                             
                                             
                                             
                                             /* Port E Pin Configuraion */
                                             PORTE_PIN0_ID, PORT_E, DEFAULT, DIO_MODE, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF,INITIAL_VALUE_LOW,
                                             
                                             PORTE_PIN1_ID, PORT_E, DEFAULT, DIO_MODE, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF,INITIAL_VALUE_LOW,
                                             
                                             PORTE_PIN2_ID, PORT_E, DEFAULT, DIO_MODE, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF,INITIAL_VALUE_LOW,
                                             
                                             PORTE_PIN3_ID, PORT_E, DEFAULT, DIO_MODE, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF,INITIAL_VALUE_LOW,
                                             
                                             PORTE_PIN4_ID, PORT_E, DEFAULT, DIO_MODE, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF,INITIAL_VALUE_LOW,
                                             
                                             PORTE_PIN5_ID, PORT_E, DEFAULT, DIO_MODE, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF,INITIAL_VALUE_LOW,
                                             
                                            /* ************************************************************************************************************************ */
                                             
                                              /* The Configured LED Pin in Port F */
                                              PortConf_LED1_PIN_NUM, PortConf_LED1_PORT_NUM,
                                             OUTPUT, DIO_MODE, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF,INITIAL_VALUE_LOW,
                                             
                                             /* The Configured SW Pin in Port F */
                                             PortConf_SW1_PIN_NUM, PortConf_SW1_PORT_NUM,
                                             INPUT, DIO_MODE, PULL_UP, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF,INITIAL_VALUE_LOW,
                                             
                                             /* The Rest Of Port F Pin Configuraion */
                                             PORTF_PIN0_ID, PORT_F, DEFAULT, DIO_MODE, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF,INITIAL_VALUE_LOW,
                                             
                                             PORTE_PIN2_ID, PORT_E, DEFAULT, DIO_MODE, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF,INITIAL_VALUE_LOW,
                                             
                                             PORTF_PIN3_ID, PORT_F, DEFAULT, DIO_MODE, OFF, PIN_DIRECTION_CHANGEABILITY_OFF, PIN_MODE_CHANGEABILITY_OFF,INITIAL_VALUE_LOW,
                                             
                                             
                                             
                                             
				         };