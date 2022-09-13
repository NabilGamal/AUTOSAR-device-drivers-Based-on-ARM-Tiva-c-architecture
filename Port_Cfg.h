 /******************************************************************************
 *
* Module: Port
 *
 * File Name: Port_Cfg.h
 *
 * Description: Pre-Compile Configuration Header file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Nabil Gamal
 ******************************************************************************/

#ifndef PORT_CFG_H
#define PORT_CFG_H

/*
 * Module Version 1.0.0
 */
#define PORT_CFG_SW_MAJOR_VERSION              (1U)
#define PORT_CFG_SW_MINOR_VERSION              (0U)
#define PORT_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION     (3U)

/* Pre-compile option for Development Error Detect */
#define PORT_DEV_ERROR_DETECT                (STD_ON)

/* Pre-compile option for presence of Port_SetPinDirection API */
#define PORT_SET_PIN_DIRECTION               (STD_ON)

/* Pre-compile option for presence of Port_SetPinMode API */
#define PORT_SET_PIN_MODE                     (STD_ON)

/* Number of the configured Dio Channels */
#define PORT_CONFIGURED_CHANNLES             (39U)

/* Pre-compile option for Version Info API */
#define PORT_VERSION_INFO                    (STD_ON)



#define PORT_PIN_DIRECTION_CHANGEABLE        (STD_OFF)

#define PORT_PIN_MODE_CHANGEABLE             (STD_OFF)

#define PORT_PIN_LEVEL_VALUE                 (STD_ON)

#if (PORT_PIN_LEVEL_VALUE == STD_ON)

    #define PORT_PIN_LEVEL_HIGH              (STD_HIGH)
    #define PORT_PIN_LEVEL_LOW               (STD_LOW)

#endif
   
/* Port Configured Port ID's  */
#define PortConf_LED1_PORT_NUM                  (Port_PortID)PORT_F
#define PortConf_SW1_PORT_NUM                   (Port_PortID)PORT_F

/* Port Configured Pins ID's  */
#define PortConf_LED1_PIN_NUM                   (Port_PinType)PORTF_PIN1_ID /* Pin 2 in PORTF */
#define PortConf_SW1_PIN_NUM                    (Port_PinType)PORTF_PIN4_ID /* Pin 4 in PORTF */
   

#define LOCK_REGISTER_UNLOCK                 (0x4C4F434B)
#define PORT_CONTROL_MASK_VALUE              (0x0000000F)
#define PORT_CONTROL_BIT_NUMBERS             (4U)
#define ANALOG_MODE                          (100)
#define PIN_NUM_MAX_CHECK                    (40U)

/* Pre-compile Options For Port Pin Mode */
typedef enum {
  
 /* PORT_PIN_MODE_DIO,
  PORT_PIN_MODE_UART0,
  PORT_PIN_MODE_UART1 = (1U),
  PORT_PIN_MODE_UART2 = (1U),
  PORT_PIN_MODE_UART3 = (1U),
  PORT_PIN_MODE_UART4 = (1U),
  PORT_PIN_MODE_UART5 = (1U),
  PORT_PIN_MODE_UART6 = (1U),
  PORT_PIN_MODE_UART7 = (1U),
  PORT_PIN_MODE_SSI1  = (2U),
  PORT_PIN_MODE_SSI2  = (2U),
  PORT_PIN_MODE_I2C1, 
  PORT_PIN_MODE_I2C2  = (3U),
  PORT_PIN_MODE_CAN0  = (3U),
  PORT_PIN_MODE_PWM0,
  PORT_PIN_MODE_PWM1,
  PORT_PIN_MODE_PhA,  
  PORT_PIN_MODE_PhB   = (6U),
  PORT_PIN_MODE_DIO_GPT,
  PORT_PIN_MODE_CAN1
  PORT_PIN_MODE_USB   = (8U)    
  PORT_PIN_MODE_C0o   = (9U),
  PORT_PIN_MODE_C1o   = (9U),
  PORT_PIN_MODE_TR    = (14U)*/
  
  
                  /******** AMFSEL 0 (GPIO)*******/
    DIO_MODE                    = 0, 

                  /******** AMFSEL 1*******/
    PORT_A_PIN_0_AF1_U0RX       = 1,  
    PORT_A_PIN_1_AF1_U0TX       = 1,  

    PORT_B_PIN_0_AF1_U1RX       = 1,  
    PORT_B_PIN_1_AF1_U1TX       = 1,  

    PORT_C_PIN_4_AF1_U4RX       = 1,  
    PORT_C_PIN_5_AF1_U4TX       = 1,  
    PORT_C_PIN_6_AF1_U3RX       = 1,  
    PORT_C_PIN_7_AF1_U3TX       = 1, 

    PORT_D_PIN_0_AF1_SSI3CLK    = 1, 
    PORT_D_PIN_1_AF1_SSI3FSS    = 1,
    PORT_D_PIN_2_AF1_SSI3RX     = 1, 
    PORT_D_PIN_3_AF1_SSI3TX     = 1, 
    PORT_D_PIN_4_AF1_U6RX       = 1, 
    PORT_D_PIN_5_AF1_U6TX       = 1, 
    PORT_D_PIN_6_AF1_U2RX       = 1,
    PORT_D_PIN_7_AF1_U2TX       = 1, 

    PORT_E_PIN_0_AF1_U7RX       = 1, 
    PORT_E_PIN_1_AF1_U7TX       = 1, 
    PORT_E_PIN_4_AF1_U5RX       = 1, 
    PORT_E_PIN_5_AF1_U5TX       = 1, 

    PORT_F_PIN_0_AF1_U1RTS      = 1, 
    PORT_F_PIN_1_AF1_U1CTS      = 1, 

                  /******** AMFSEL 2*******/
    PORT_A_PIN_2_AF2_SSI0CLK    = 2, 
    PORT_A_PIN_3_AF2_SSI0FSS    = 2, 
    PORT_A_PIN_4_AF2_SSI0RX     = 2,
    PORT_A_PIN_5_AF2_SSI0TX     = 2, 

    PORT_B_PIN_4_AF2_SSI2CLK    = 2, 
    PORT_B_PIN_5_AF2_SSI2FSS    = 2, 
    PORT_B_PIN_6_AF2_SSI2RX     = 2, 
    PORT_B_PIN_7_AF2_SSI2TX     = 2, 

    PORT_C_PIN_4_AF2_U1RX       = 2, 
    PORT_C_PIN_5_AF2_U1TX       = 2, 

    PORT_D_PIN_0_AF2_SSI1CLK    = 2, 
    PORT_D_PIN_1_AF2_SSI1FSS    = 2, 
    PORT_D_PIN_2_AF2_SSI1RX     = 2, 
    PORT_D_PIN_3_AF2_SSI1TX     = 2, 

    PORT_F_PIN_0_AF2_SSI1RX     = 2, 
    PORT_F_PIN_1_AF2_SSI1TX     = 2, 
    PORT_F_PIN_2_AF2_SSI1CLK    = 2, 
    PORT_F_PIN_3_AF2_SSI1FSS    = 2, 

                  /******** AMFSEL 3*******/
    PORT_A_PIN_6_AF3_I2C1SCL    = 3, 
    PORT_A_PIN_7_AF3_I2C1SDA    = 3, 

    PORT_B_PIN_2_AF3_I2C0SCL    = 3, 
    PORT_B_PIN_3_AF3_I2C0SDA    = 3,


    PORT_D_PIN_0_AF3_I2C3SCL    = 3, 
    PORT_D_PIN_1_AF3_I2C3SDA    = 3, 

    PORT_E_PIN_4_AF3_I2C2SCL    = 3, 
    PORT_E_PIN_5_AF3_I2C2SDA    = 3, 

    PORT_F_PIN_0_AF3_CAN0RX     = 3, 
    PORT_F_PIN_3_AF3_CAN0TX     = 3, 

                  /******** AMFSEL 4*******/
    PORT_B_PIN_4_AF4_M0PWM2     = 4, 
    PORT_B_PIN_5_AF4_M0PWM3     = 4, 
    PORT_B_PIN_6_AF4_M0PWM0     = 4, 
    PORT_B_PIN_7_AF4_M0PWM1     = 4, 

    PORT_C_PIN_4_AF4_M0PWM6     = 4, 
    PORT_C_PIN_5_AF4_M0PWM7     = 4, 

    PORT_D_PIN_0_AF4_M0PWM6     = 4, 
    PORT_D_PIN_1_AF4_M0PWM7     = 4, 
    PORT_D_PIN_2_AF4_M0FAULT0   = 4, 
    PORT_D_PIN_6_AF4_M0FAULT0   = 4, 

    PORT_E_PIN_4_AF4_M0PWM4     = 4, 
    PORT_E_PIN_5_AF4_M0PWM5     = 4, 

    PORT_F_PIN_2_AF4_M0FAULT0   = 4,

                  /******** AMFSEL 5*******/
    PORT_A_PIN_6_AF5_M1PWM2     = 5, 
    PORT_A_PIN_7_AF5_M1PWM3     = 5, 

    PORT_D_PIN_0_AF5_M1PWM0     = 5, 
    PORT_D_PIN_1_AF5_M1PWM1     = 5, 

    PORT_E_PIN_4_AF5_M1PWM2     = 5, 
    PORT_E_PIN_5_AF5_M1PWM3     = 5, 

    PORT_F_PIN_0_AF5_M1PWM4     = 5, 
    PORT_F_PIN_1_AF5_M1PWM5     = 5,
    PORT_F_PIN_2_AF5_M1PWM6     = 5, 
    PORT_F_PIN_3_AF5_M1PWM7     = 5, 
    PORT_F_PIN_4_AF5_M1FAULT0   = 5, 

                  /******** AMFSEL 6*******/
    PORT_C_PIN_4_AF6_IDX1       = 6, 
    PORT_C_PIN_5_AF6_PHA1       = 6, 
    PORT_C_PIN_6_AF6_PHB1       = 6, 

    PORT_D_PIN_3_AF6_IDX0       = 6, 
    PORT_D_PIN_6_AF6_PHA0       = 6, 
    PORT_D_PIN_7_AF6_PHB0       = 6, 

    PORT_F_PIN_0_AF6_PHA0       = 6,
    PORT_F_PIN_1_AF6_PHB0       = 6, 
    PORT_F_PIN_4_AF6_IDX0       = 6, 

                  /******** AMFSEL 7*******/
    PORT_B_PIN_0_AF7_T2CCP0     = 7, 
    PORT_B_PIN_1_AF7_T2CCP1     = 7, 
    PORT_B_PIN_2_AF7_T3CCP0     = 7, 
    PORT_B_PIN_3_AF7_T3CCP1     = 7, 
    PORT_B_PIN_4_AF7_T1CCP0     = 7, 
    PORT_B_PIN_5_AF7_T1CCP1     = 7, 
    PORT_B_PIN_6_AF7_T0CCP0     = 7, 
    PORT_B_PIN_7_AF7_T0CCP1     = 7, 

    PORT_C_PIN_4_AF7_WT0CCP0    = 7,  
    PORT_C_PIN_5_AF7_WT0CCP1    = 7,  
    PORT_C_PIN_6_AF7_WT1CCP0    = 7,  
    PORT_C_PIN_7_AF7_WT1CCP1    = 7,  

    PORT_D_PIN_0_AF7_WT2CCP0    = 7,  
    PORT_D_PIN_1_AF7_WT2CCP1    = 7, 
    PORT_D_PIN_2_AF7_WT3CCP0    = 7,  
    PORT_D_PIN_3_AF7_WT3CCP1    = 7,  
    PORT_D_PIN_4_AF7_WT4CCP0    = 7,  
    PORT_D_PIN_5_AF7_WT4CCP1    = 7,  
    PORT_D_PIN_6_AF7_WT5CCP0    = 7,  
    PORT_D_PIN_7_AF7_WT5CCP1    = 7,  

    PORT_F_PIN_0_AF7_T0CCP0     = 7,  
    PORT_F_PIN_1_AF7_T0CCP1     = 7,  
    PORT_F_PIN_2_AF7_T1CCP0     = 7,  
    PORT_F_PIN_3_AF7_T1CCP1     = 7,  
    PORT_F_PIN_4_AF7_T2CCP0     = 7,  


                  /******** AMFSEL 8*******/
    PORT_A_PIN_0_AF8_CAN1RX     = 8,  
    PORT_A_PIN_1_AF8_CAN1TX     = 8,  

    PORT_B_PIN_4_AF8_CAN0RX     = 8,  
    PORT_B_PIN_5_AF8_CAN0TX     = 8,  

    PORT_C_PIN_4_AF8_U1RTS      = 8,  
    PORT_C_PIN_5_AF8_U1CTS      = 8,  
    PORT_C_PIN_6_AF8_USB0EPEN   = 8,  
    PORT_C_PIN_7_AF8_USB0PFLT   = 8,  

    PORT_D_PIN_2_AF8_USB0EPEN   = 8, 
    PORT_D_PIN_3_AF8_USB0PFLT   = 8,  
    PORT_D_PIN_7_AF8_NMI        = 8,  

    PORT_E_PIN_4_AF8_CAN0RX     = 8,  
    PORT_E_PIN_5_AF8_CAN0TX     = 8,  

    PORT_F_PIN_0_AF8_NMI        = 8,  
    PORT_F_PIN_4_AF8_USB0EPEN   = 8,  

                  /******** AMFSEL 9*******/
    PORT_F_PIN_0_AF9_C0O        = 9,  
    PORT_F_PIN_1_AF9_C01        = 9,  

                  /******** AMFSEL 14*******/
    PORT_F_PIN_1_AF14_TRD1      = 14,
    PORT_F_PIN_2_AF14_TRD0      = 14,
    PORT_F_PIN_3_AF14_TRCLK     = 14
    
}PORT_PIN_MODE;


 /* Pre-compile Port Pin Number */
typedef enum {
  
 PORTA_PIN0_ID   = 0,
 PORTA_PIN1_ID   = 1,
 PORTA_PIN2_ID   = 2,
 PORTA_PIN3_ID   = 3,
 PORTA_PIN4_ID   = 4,
 PORTA_PIN5_ID   = 5,
 PORTA_PIN6_ID   = 6,
 PORTA_PIN7_ID   = 7,


 PORTB_PIN0_ID   = 0,
 PORTB_PIN1_ID   = 1,
 PORTB_PIN2_ID   = 2,
 PORTB_PIN3_ID   = 3,
 PORTB_PIN4_ID   = 4,
 PORTB_PIN5_ID   = 5,
 PORTB_PIN6_ID   = 6,
 PORTB_PIN7_ID   = 7,


/* JTag Pins that must be removed or ignored in the intialization */
/* #define PORTC_PIN0_ID   (uint16)0x16
*  #define PORTC_PIN1_ID   (uint16)0x17
*  #define PORTC_PIN2_ID   (uint16)0x18
*  #define PORTC_PIN3_ID   (uint16)0x19 */


 PORTC_PIN4_ID   = 4,
 PORTC_PIN5_ID   = 5,
 PORTC_PIN6_ID   = 6,
 PORTC_PIN7_ID   = 7,


 PORTD_PIN0_ID   = 0,
 PORTD_PIN1_ID   = 1,
 PORTD_PIN2_ID   = 2,
 PORTD_PIN3_ID   = 3,
 PORTD_PIN4_ID   = 4,
 PORTD_PIN5_ID   = 5,
 PORTD_PIN6_ID   = 6,
 PORTD_PIN7_ID   = 7,


 PORTE_PIN0_ID   = 0,
 PORTE_PIN1_ID   = 1,
 PORTE_PIN2_ID   = 2,
 PORTE_PIN3_ID   = 3,
 PORTE_PIN4_ID   = 4,
 PORTE_PIN5_ID   = 5,


 PORTF_PIN0_ID   = 0,
 PORTF_PIN1_ID   = 1,
 PORTF_PIN2_ID   = 2,
 PORTF_PIN3_ID   = 3,
 PORTF_PIN4_ID   = 4

}Port_PinID;


#define PORT_C_JTAG_PIN_0                   (300U)
#define PORT_C_JTAG_PIN_1                   (301U)
#define PORT_C_JTAG_PIN_2                   (302U)
#define PORT_C_JTAG_PIN_3                   (303U)


typedef enum{

    PORT_A,
    PORT_B,
    PORT_C, 
    PORT_D, 
    PORT_E, 
    PORT_F  

}Port_PortID;

/* Description: Enum to hold PIN direction */
typedef enum
{
    INPUT,OUTPUT,DEFAULT
}Port_PinDirectionType;

/* Description: Enum to hold internal resistor type for PIN */
typedef enum
{
    OFF,PULL_UP,PULL_DOWN
}Port_InternalResistor;

#endif /* PORT_CFG_H */
