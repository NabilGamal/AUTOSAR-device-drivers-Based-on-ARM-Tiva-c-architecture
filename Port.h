 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Nabil Gamal 
 ******************************************************************************/

#ifndef PORT_H
#define PORT_H

/* Id for the company in the AUTOSAR
 * for example Mohamed Tarek's ID = 1000 :) */
#define PORT_VENDOR_ID    (1000U)

/* Dio Module Id */
#define PORT_MODULE_ID    (120U)

/* Dio Instance Id */
#define PORT_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION           (1U)
#define PORT_SW_MINOR_VERSION           (0U)
#define PORT_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION   (3U)

/*
 * Macros for PORT Status
 */
#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)

/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and Dio Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/* PORT Pre-Compile Configuration Header file */
#include "PORT_Cfg.h"

/* AUTOSAR Version checking between Dio_Cfg.h and Dio.h files */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of PORT_Cfg.h does not match the expected version"
#endif

/* Software Version checking between PORT_Cfg.h and PORT.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of PORT_Cfg.h does not match the expected version"
#endif

   
/* Non AUTOSAR files */
#include "Common_Macros.h"

/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/
/* Service ID for Port Initialization */
#define PORT_INIT_SID                       (uint8)0x00

/* Service ID for Port Set Pin Direction */
#define PORT_SET_PIN_DIRECTION_SID          (uint8)0x01

/* Service ID for Port Refresh Port Direction */
#define PORT_REFRESH_PORT_DIRECTION_SID     (uint8)0x02

/* Service ID for Port Get Version Info */
#define PORT_GET_VERSION_INFO_SID           (uint8)0x03

/* Service ID for Port Set Pin Mode */
#define PORT_SET_PIN_MODE_SID               (uint8)0x04


/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/
/* DET code to report Incorrect Port Pin ID passed */
#define PORT_E_PARAM_PIN                  (uint8)0x0A

/* DET code to report Port Pin not configured as changeable */
#define PORT_E_DIRECTION_UNCHANGEABLE     (uint8)0x0B

/* DET code to report Port_Init service called with wrong parameter */
#define PORT_E_PARAM_CONFIG               (uint8)0x0D

/* DET code to report Incorrect Port Pin ID passed */
#define PORT_E_PARAM_PIN                  (uint8)0x1F

/* DET code to report Port Pin Mode passed not valid */
#define PORT_E_PARAM_INVALID_MODE         (uint8)0x1B
   
/* DET code to report Port_SetPinMode service called when the mode is unchangeable */
#define PORT_E_MODE_UNCHANGEABLE          (uint8)0x1C
   
/*
 * The API service shall return immediately without any further action,
 * beside reporting this development error.
 */
#define PORT_E_PARAM_POINTER              (uint8)0x20

/*
 * API service used without module initialization is reported using following
 * error code
 */
#define PORT_E_UNINIT                     (uint8)0xF0
   
   
/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

/* Type definition for Port_PinType used by the Port APIs */
typedef uint8 Port_PinType;

/* Type definition for Port_PinModeType used by the Port APIs */
typedef uint8 Port_PinModeType;



/* Structure for Port_ConfigChannel */
typedef struct{

    Port_PinID                  pinNum;                   /* The Pin number of the configured Pin */

    Port_PortID                 portNum;                   /* The Port number of the configured Pin */

    Port_PinDirectionType       direction;                 /* The Port Initial direction for the Pin (Input / Output) */

    PORT_PIN_MODE                mode;                     /* The Port Initial mode for the Pin */

    Port_InternalResistor       resistor;                  /* The Pull Up / Down Resistor for configured Input Pins */

    uint8                       pinDirection_Changeable;   /* Configuration for the Changability of the Pin Direction During Run time */

    
    uint8                       pinMode_Changeable;        /* Configuration for the Changability of the Pin Mode During Run time */
                                                             

    uint8                       initialValue;             /* Initial Value For configured Output Pins */

}Port_ConfigChannel;


/* Structure for Port_ConfigType */
typedef struct{

    Port_ConfigChannel          portChannels [PORT_CONFIGURED_CHANNLES]; /*Array of structures from the Port_ConfigChannel */
    
}Port_ConfigType;

/* Define used to decide pin direction changeability on run time */
#define PIN_DIRECTION_CHANGEABILITY_ON      STD_ON
#define PIN_DIRECTION_CHANGEABILITY_OFF     STD_OFF

/* Defines used to decide Pin mode changeability during run time */
#define PIN_MODE_CHANGEABILITY_ON           STD_ON
#define PIN_MODE_CHANGEABILITY_OFF          STD_OFF

/* Defines used to set initial value for output pins             */
#define INITIAL_VALUE_HIGH                  STD_HIGH
#define INITIAL_VALUE_LOW                   STD_LOW

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/* Function for Port Initialization API */
void Port_Init (const Port_ConfigType* ConfigPtr);


#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
/* Function for Set Pin Direction API */
void Port_SetPinDirection (Port_PinType Pin, Port_PinDirectionType Direction);
#endif 


/* Function for Port Refresh Port Direction API */
void Port_RefreshPortDirection (void);

/* Function for Port Set Pin Mode API */
void Port_SetPinMode (Port_PinType Pin, Port_PinModeType Mode);

/* Function for Port Get Version Info API */
#if (DIO_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo (Std_VersionInfoType* VersionInfo);
#endif

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern PB structures to be used by Dio and other modules */
extern const Port_ConfigType Port_Configuration;

#endif /* PORT_H */