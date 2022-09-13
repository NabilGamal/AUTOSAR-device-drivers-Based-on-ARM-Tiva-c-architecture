 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Nabil Gamal
 ******************************************************************************/

#include "Port_Reg.h"
#include "Port.h"
#include "tm4c123gh6pm_registers.h"

#if (PORT_DEV_ERROR_DETECT == STD_ON)

#include "Det.h"
/* AUTOSAR Version checking between Det and Dio Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif

#endif

STATIC const Port_ConfigChannel * Port_Channels = NULL_PTR;
STATIC uint8 Port_Status = PORT_NOT_INITIALIZED;

/************************************************************************************
* Service Name: Port_Init
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): ConfigPtr - Pointer to configuration set.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Initializes the Port Driver module.
************************************************************************************/
void Port_Init (const Port_ConfigType* ConfigPtr)
{
    volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
    volatile uint32 delay = 0;
    uint8 counter = 0;
    
    #if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* check if the input configuration pointer is not a NULL_PTR */
	if (NULL_PTR == ConfigPtr)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_CONFIG);
                
                return;
	}
	else
#endif
          
        {
          
          Port_Channels = ConfigPtr->portChannels;
          
          for (counter = 0; counter < PORT_CONFIGURED_CHANNLES; counter++)
          {
            
    
    switch(Port_Channels[counter].portNum)
    {
        case  PORT_A: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
		 break;
	case  PORT_B: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
		 break;
	case  PORT_C: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
		 break;
	case  PORT_D: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
		 break;
        case  PORT_E: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
		 break;
        case  PORT_F: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
		 break;
    }
                 
       if (Port_Channels[counter].direction != DEFAULT)
       { 

         /* Checks if it reaches the PD7 or PF0, 
         *  then the LOCK Register must be unlocked */
         
         if (Port_Channels[counter].portNum == PORT_D && Port_Channels[counter].pinNum == PORTD_PIN7_ID || Port_Channels[counter].portNum == PORT_F && Port_Channels[counter].pinNum == PORTD_PIN0_ID)
         {
              
             *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = LOCK_REGISTER_UNLOCK;                     /* Unlock the GPIOCR register */   
             SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) , Port_Channels[counter].pinNum);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
              
         }
         
         else if (Port_Channels[counter].portNum == PORT_C && Port_Channels[counter].pinNum <= PORT_C_JTAG_PIN_3)
         {
           
            /* Do Nothing ...  this is the JTAG pins */
           continue;
           
         }
         
         else
         {
            
           /* Do Nothing ...  no locked Pins */
           
         }
         
         if (Port_Channels[counter].mode == ANALOG_MODE)
         {
           /* Set the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin 
           *  Enable Alternative function for this pin by Set the corresponding bit in GPIOAFSEL register 
           *  Clear Digital enable regesiter to disable the Digital mode*/
           
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_Channels[counter].pinNum);      
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Channels[counter].pinNum);     
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_Channels[counter].pinNum);      
         }
         
         else
         {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_Channels[counter].pinNum);
            
            
            if (Port_Channels[counter].mode == DIO_MODE)
            {
              /* If the PIN mode is DIO, Then disable the Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register
              *  Clear the PMCx bits for this pin*/
               CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Channels[counter].pinNum); 
               *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(PORT_CONTROL_MASK_VALUE << ( (Port_Channels[counter].pinNum) * PORT_CONTROL_BIT_NUMBERS) );
               
            }
            
            else
            {
              /* If the PIN mode is Any mode rather than DIO, Then enable the Alternative function for this pin by set the corresponding bit in GPIOAFSEL register
              *  Set the PMCx bits for this pin by do an OR logic with the Pin Mode from the Config structure and Shift it to the left with the PinNum*4 */
              
              SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Channels[counter].pinNum);
              *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= ( (Port_Channels[counter].mode) << ( (Port_Channels[counter].pinNum) * PORT_CONTROL_BIT_NUMBERS) );

            }
            
            
         }
         
         if (Port_Channels[counter].direction == OUTPUT)
             {
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_Channels[counter].pinNum);                /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
        
              if (Port_Channels[counter].initialValue == INITIAL_VALUE_HIGH)
                {
                  SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , Port_Channels[counter].pinNum);          /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
                }
              else
                {
                  CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , Port_Channels[counter].pinNum);        /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
                }
              
             }
    
        else if (Port_Channels[counter].direction == INPUT)
            {
              CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_Channels[counter].pinNum);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
        
              if(Port_Channels[counter].resistor == PULL_UP)
                {
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , Port_Channels[counter].pinNum);       /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
                }
              else if(Port_Channels[counter].resistor == PULL_DOWN)
                {
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , Port_Channels[counter].pinNum);     /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
                }
              
              else  
              {
                /* The pin neither Pull Up or Pull Down */
                
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , Port_Channels[counter].pinNum);     /* Clear the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , Port_Channels[counter].pinNum);       /* Clear the corresponding bit in the GPIOPUR register to enable the internal pull up pin */

              }
            
            }
                 
         else
         {
            /* Do Nothing */
         }
            
         
       //  SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_Channels[counter].pinNum);  
         if (!(Port_Channels[counter].mode == ANALOG_MODE))
         {
           /* Digital Mode 
            * Set The Digital enable register */
           
           SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_Channels[counter].pinNum);  
         }
         
       }
    
       else 
       {
                /* Hence the pin is not used, then nothing will happen to the registers */
    
                /* Clear the corresponding bit in AFSEL Register to go initial value (from the data sheet which is reset value) */
                CLEAR_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), Port_Channels[counter].pinNum);

                /* Clear the corresponding bit in PUR (Pull up) Register */
                CLEAR_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET), Port_Channels[counter].pinNum);

                /* Clear the corresponding bit in PDR (Pull down) Register */
                CLEAR_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET), Port_Channels[counter].pinNum);

                /* Clear the corresponding bit in DEN (Digital Enable) Register */
                CLEAR_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), Port_Channels[counter].pinNum);

                /* Do nothing to Lock & Commit register */

                /* Clear the corresponding bit in AMSEL (Analog Mode Selection) Register */
                CLEAR_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), Port_Channels[counter].pinNum);

                /* Clear the corresponding bits in PCTL (Port Control) Register (Responsible of Alternative function selection)*/
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(PORT_CONTROL_MASK_VALUE << ( (Port_Channels[counter].pinNum) * PORT_CONTROL_BIT_NUMBERS));

    
    
       }
   
        }
        
        Port_Status = PORT_INITIALIZED;
}
}

/************************************************************************************
* Service Name: Port_SetPinDirection
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Pin - Port Pin ID number.
* Parameters (in): Direction - Port Pin Direction.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin direction.
************************************************************************************/
#if (PORT_SET_PIN_DIRECTION == STD_ON)
void Port_SetPinDirection (Port_PinType Pin, Port_PinDirectionType Direction)
{
    volatile uint32* PortGpio_Ptr = NULL_PTR;
    
    boolean error = FALSE;
    uint8 counter = 0;
    uint8 Id = 0;
    
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    
    if (Port_Status == PORT_NOT_INITIALIZED)
    {
       Det_ReportError (PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID, PORT_E_UNINIT);
       
       error = TRUE;
    }
    
    else
      
    {
      /* Do Nothing*/
    }
    

    
    if (PORT_CONFIGURED_CHANNLES <= Pin)
    {
      Det_ReportError (PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID, PORT_E_PARAM_PIN);
    }
    
    else
    {
        /* Do Nothing */
    }

#endif
    
    for (counter = 0; counter < PORT_CONFIGURED_CHANNLES; counter++)
    {
      if (Port_Channels[counter].pinNum == Pin)
      {
        Id = counter;
        
        break;
      }
    }
    
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    
    if (Port_Channels[Id].pinDirection_Changeable == PIN_DIRECTION_CHANGEABILITY_OFF)
    {
       Det_ReportError (PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID, PORT_E_DIRECTION_UNCHANGEABLE);
       
       error = TRUE;
    }
    
    else
    {
      /* Do Nothing */
    }
    
#endif
    
    if (error == FALSE)
    {
      
     
         switch(Port_Channels[Id].portNum)
          {
            case  PORT_A: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
                     break;
            case  PORT_B: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
                     break;
            case  PORT_C: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
                     break;
            case  PORT_D: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
                     break;
            case  PORT_E: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
                     break;
            case  PORT_F: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
                     break;
        }
        
         if (Port_Channels[Id].portNum == PORT_D && Port_Channels[Id].pinNum == PORTD_PIN7_ID || Port_Channels[Id].portNum == PORT_F && Port_Channels[Id].pinNum == PORTD_PIN0_ID)
         {
              
             *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = LOCK_REGISTER_UNLOCK;                     /* Unlock the GPIOCR register */   
             SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) , Port_Channels[Id].pinNum);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
              
         }
         
         else if (Port_Channels[Id].portNum == PORT_C && Port_Channels[Id].pinNum <= PORT_C_JTAG_PIN_3)
         {
           
            /* Do Nothing ...  this is the JTAG pins */           
         }
         
         else
         {
            
           /* Do Nothing ...  no locked Pins */
           
         }
         
         if (Direction == OUTPUT)
           {
             SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Pin);                /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
           }
         
         else if (Direction == INPUT)
         {
             CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Pin);                /* Clear the corresponding bit in the GPIODIR register to configure it as Input pin */            
         }
    
    }
    
    else
    {
      /* Do Nothing */
    }
    

}

#endif


/************************************************************************************
* Service Name: Port_RefreshPortDirection
* Service ID[hex]: 0x02
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Refreshes port direction.
************************************************************************************/
void Port_RefreshPortDirection (void)
{
volatile uint32* PortGpio_Ptr = NULL_PTR;
    
    boolean error = FALSE;
    uint8 counter = 0;
    
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    
    if (Port_Status == PORT_NOT_INITIALIZED)
    {
       Det_ReportError (PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_REFRESH_PORT_DIRECTION_SID, PORT_E_UNINIT);
       
       error = TRUE;
    }
    
    else
      
    {
      /* Do Nothing*/
    }
#endif
    
     if (error == FALSE)
    {
       for(counter = 0; counter <= PORT_CONFIGURED_CHANNLES; counter++)
        {
         switch(Port_Channels[counter].portNum)
          {
            case  PORT_A: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
                     break;
            case  PORT_B: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
                     break;
            case  PORT_C: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
                     break;
            case  PORT_D: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
                     break;
            case  PORT_E: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
                     break;
            case  PORT_F: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
                     break;
        }
        
         if (Port_Channels[counter].portNum == PORT_D && Port_Channels[counter].pinNum == PORTD_PIN7_ID || Port_Channels[counter].portNum == PORT_F && Port_Channels[counter].pinNum == PORTD_PIN0_ID)
         {
              
             *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = LOCK_REGISTER_UNLOCK;                     /* Unlock the GPIOCR register */   
             SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) , Port_Channels[counter].pinNum);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
              
         }
         
         else if (Port_Channels[counter].portNum == PORT_C && Port_Channels[counter].pinNum <= PORT_C_JTAG_PIN_3)
         {
           
            /* Do Nothing ...  this is the JTAG pins */
           continue;
           
         }
         
         else
         {
            
           /* Do Nothing ...  no locked Pins */
           
         }
         
         if (Port_Channels[counter].pinDirection_Changeable == PIN_DIRECTION_CHANGEABILITY_ON)
         {
             if (Port_Channels[counter].direction == OUTPUT)
             {
                 SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_Channels[counter].pinNum);                /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
               }
             
             else if (Port_Channels[counter].direction == INPUT)
             {
                 CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_Channels[counter].pinNum);                /* Clear the corresponding bit in the GPIODIR register to configure it as Input pin */            
             }
         }
}
    }

    else  
    {
      /* Do Nothing */
    }

}
/************************************************************************************
* Service Name: Port_GetVersionInfo
* Service ID[hex]: 0x03
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): Versioninfo - Pointer to where to store the version information of this module.
* Return value: None
* Description: Returns the version information of this module.
************************************************************************************/
#if (PORT_VERSION_INFO == STD_ON)

void Port_GetVersionInfo (Std_VersionInfoType* VersionInfo)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
  
  if(NULL_PTR == VersionInfo)
    {
        /* Report to DET  */
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
                PORT_GET_VERSION_INFO_SID, PORT_E_PARAM_POINTER);
    }
    else
    {
        /* Do nothing */
    }
    
    if (Port_Status == PORT_NOT_INITIALIZED)
    {
       Det_ReportError (PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_REFRESH_PORT_DIRECTION_SID, PORT_E_UNINIT);
       
    }
    
    else     
#endif /* (PORT_DEV_ERROR_DETECT == STD_ON) */
    {
        VersionInfo->vendorID = (uint16)PORT_VENDOR_ID;

        VersionInfo->moduleID = (uint16)PORT_MODULE_ID;

        VersionInfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;

        VersionInfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;

        VersionInfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
    }

}
#endif

/************************************************************************************
* Service Name: Port_SetPinMode
* Service ID[hex]: 0x04
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Pin - Port Pin ID number.
* Parameters (in): Mode - New Port Pin mode to be set on port pin.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin mode.
************************************************************************************/
void Port_SetPinMode (Port_PinType Pin, Port_PinModeType Mode)
{
volatile uint32* PortGpio_Ptr = NULL_PTR;
    
    boolean error = FALSE;
    uint8 counter = 0;
    uint8 Id = PIN_NUM_MAX_CHECK;

#if (PORT_DEV_ERROR_DETECT == STD_ON)
    
    if (Port_Status == PORT_NOT_INITIALIZED)
    {
       Det_ReportError (PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_UNINIT);
       
       error = TRUE;
    }  
    
    else 
    {
      /* Do Nothing */
    }
    
#endif
  
    for (counter = 0; counter < PORT_CONFIGURED_CHANNLES; counter++)
    {
      if (Port_Channels[counter].pinNum == Pin)
      {
        Id = 0;
        
        Id = counter;
        
        break;
      }
      
      else
      {
        /* Do Nothing */
      }
    }
    
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    
    if (Id == PIN_NUM_MAX_CHECK)
    {
      Det_ReportError (PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_PARAM_PIN);
      
      error = TRUE;
    }
    
    else 
    {
      /* Do Nothing */
    }
    
    if (Mode > PORT_F_PIN_3_AF14_TRCLK)
    {
      Det_ReportError (PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_PARAM_INVALID_MODE);
      
      error = TRUE;
    }
    
    else
    {
      /* Do Nothing */
    }
    
    if (Port_Channels[counter].pinMode_Changeable == PIN_MODE_CHANGEABILITY_OFF)
    {
      Det_ReportError (PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_MODE_UNCHANGEABLE);
      
      error = TRUE;
    }
    
    else
    {
      /* Do Nothing */
    }
    
#endif
     if (error == FALSE)
    {
     
         switch(Port_Channels[Id].portNum)
          {
            case  PORT_A: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
                     break;
            case  PORT_B: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
                     break;
            case  PORT_C: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
                     break;
            case  PORT_D: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
                     break;
            case  PORT_E: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
                     break;
            case  PORT_F: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
                     break;
        }
        
         if (Port_Channels[Id].portNum == PORT_D && Port_Channels[Id].pinNum == PORTD_PIN7_ID || Port_Channels[Id].portNum == PORT_F && Port_Channels[Id].pinNum == PORTD_PIN0_ID)
         {
              
             *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = LOCK_REGISTER_UNLOCK;                     /* Unlock the GPIOCR register */   
             SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) , Port_Channels[Id].pinNum);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
              
         }
         
         else if (Port_Channels[Id].portNum == PORT_C && Port_Channels[Id].pinNum <= PORT_C_JTAG_PIN_3)
         {
           
            /* Do Nothing ...  this is the JTAG pins */
           
         }
         
         else
         {
            
           /* Do Nothing ...  no locked Pins */
           
         }
         
   if (Mode == ANALOG_MODE)
         {
           /* Set the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin 
           *  Enable Alternative function for this pin by Set the corresponding bit in GPIOAFSEL register 
           *  Clear Digital enable regesiter to disable the Digital mode*/
           
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_Channels[counter].pinNum);      
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Channels[counter].pinNum);     
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_Channels[counter].pinNum);      
         }
         
         else
         {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_Channels[counter].pinNum);
            
            
            if (Mode == DIO_MODE)
            {
              /* If the PIN mode is DIO, Then disable the Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register
              *  Clear the PMCx bits for this pin*/
              
               CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Channels[counter].pinNum); 
               *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(PORT_CONTROL_MASK_VALUE << ( (Port_Channels[counter].pinNum) * PORT_CONTROL_BIT_NUMBERS) );
               
            }
            
            else
            {
              /* If the PIN mode is Any mode rather than DIO, Then enable the Alternative function for this pin by set the corresponding bit in GPIOAFSEL register
              *  Set the PMCx bits for this pin by do an OR logic with the Pin Mode from the Config structure and Shift it to the left with the PinNum*4 */
              
              SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Channels[counter].pinNum);
              *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= ( (Port_Channels[counter].mode) << ( (Port_Channels[counter].pinNum) * PORT_CONTROL_BIT_NUMBERS) );

            }
         }
          if (!(Port_Channels[counter].mode == ANALOG_MODE))
         {
           /* Digital Mode 
            * Set The Digital enable register */
           
           SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_Channels[counter].pinNum);  
         }
         
         else
         {
          /* Do Nothing */
         }
         


}
}