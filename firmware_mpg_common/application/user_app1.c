/**********************************************************************************************************************
File: user_app1.c                                                                
Jiangzhaoyu
----------------------------------------------------------------------------------------------------------------------
To start a new task using this user_app1 as a template:
 1. Copy both user_app1.c and user_app1.h to the Application directory
 2. Rename the files yournewtaskname.c and yournewtaskname.h
 3. Add yournewtaskname.c and yournewtaskname.h to the Application Include and Source groups in the IAR project
 4. Use ctrl-h (make sure "Match Case" is checked) to find and replace all instances of "user_app1" with "yournewtaskname"
 5. Use ctrl-h to find and replace all instances of "UserApp1" with "YourNewTaskName"
 6. Use ctrl-h to find and replace all instances of "USER_APP1" with "YOUR_NEW_TASK_NAME"
 7. Add a call to YourNewTaskNameInitialize() in the init section of main
 8. Add a call to YourNewTaskNameRunActiveState() in the Super Loop section of main
 9. Update yournewtaskname.h per the instructions at the top of yournewtaskname.h
10. Delete this text (between the dashed lines) and update the Description below to describe your task
----------------------------------------------------------------------------------------------------------------------

Description:
This is a user_app1.c file template 

------------------------------------------------------------------------------------------------------------------------
API:

Public functions:


Protected System functions:
void UserApp1Initialize(void)
Runs required initialzation for the task.  Should only be called once in main init section.

void UserApp1RunActiveState(void)
Runs current task state.  Should only be called once in main loop.


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_UserApp1"
***********************************************************************************************************************/
/* New variables */
volatile u32 G_u32UserApp1Flags;                       /* Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemFlags;                  /* From main.c */
extern volatile u32 G_u32ApplicationFlags;             /* From main.c */

extern volatile u32 G_u32SystemTime1ms;                /* From board-specific source file */
extern volatile u32 G_u32SystemTime1s;                 /* From board-specific source file */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp1_" and be declared as static.
***********************************************************************************************************************/
static fnCode_type UserApp1_StateMachine;            /* The state machine function pointer */
//static u32 UserApp1_u32Timeout;                      /* Timeout counter used across states */


/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Public functions                                                                                                   */
/*--------------------------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------------------*/
/* Protected functions                                                                                                */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------
Function: UserApp1Initialize

Description:
Initializes the State Machine and its variables.

Requires:
  -

Promises:
  - 
*/
void UserApp1Initialize(void)
{
  /* If good initialization, set state to Idle */
  if( 1 )
  {
    UserApp1_StateMachine = UserApp1SM_Idle;
  }
  else
  {
    /* The task isn't properly initialized, so shut it down and don't run */
    UserApp1_StateMachine = UserApp1SM_FailedInit;
  }

} /* end UserApp1Initialize() */

  
/*----------------------------------------------------------------------------------------------------------------------
Function UserApp1RunActiveState()

Description:
Selects and runs one iteration of the current state in the state machine.
All state machines have a TOTAL of 1ms to execute, so on average n state machines
may take 1ms / n to execute.

Requires:
  - State machine function pointer points at current state

Promises:
  - Calls the function to pointed by the state machine function pointer
*/
void UserApp1RunActiveState(void)
{
  UserApp1_StateMachine();

} /* end UserApp1RunActiveState */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Private functions                                                                                                  */
/*--------------------------------------------------------------------------------------------------------------------*/


/**********************************************************************************************************************
State Machine Function Definitions
**********************************************************************************************************************/

/*-------------------------------------------------------------------------------------------------------------------*/
/* Wait for ??? */
static void UserApp1SM_Idle(void)
{
  static u8 au8State1[]="\n\rEntering state1\n\r";
  static u8 au8State2[]="\n\rEntering state2\n\r";
  static u8 au8Input[2]={0};
  static u8 u8Button=0;
  static u8 au8Message1[]="STATE 1";
  static u8 au8Message2[]="STATE 2";
  static u16 u16Counter=0;
  static bool bTime=FALSE;
 
  DebugScanf(au8Input);
 
  
  if(au8Input[0] == '1'||WasButtonPressed(BUTTON1))
  {
      u8Button=1;
      ButtonAcknowledge(BUTTON1);
      au8Input[0]=0;
      au8Input[1]=0;
  }
  
  if(u8Button == 1)
  {
      PWMAudioOff(BUZZER1);
      PWMAudioOff(BUZZER2);
      LedOff(WHITE);
      LedOff(PURPLE);
      LedOff(BLUE);
      LedOff(CYAN);
      LedOff(GREEN);
      LedOff(YELLOW);
      LedOff(ORANGE);
      LedOff(RED);
      LedOff(LCD_RED);
      LedOff(LCD_GREEN);
      LedOff(LCD_BLUE);
      LCDCommand(LCD_CLEAR_CMD);
      LCDMessage(LINE1_START_ADDR,au8Message1);
      ButtonAcknowledge(BUTTON1);
      DebugPrintf(au8State1);
      LedOn(WHITE);
      LedOn(PURPLE);
      LedOn(BLUE);
      LedOn(CYAN);
      LedOn(LCD_RED);
      LedOn(LCD_BLUE);
      u8Button=0;
      bTime=FALSE;
     
  }
   
  if(au8Input[0] == '2'||WasButtonPressed(BUTTON2))
  {
      u8Button=2;
      ButtonAcknowledge(BUTTON2);
      bTime=TRUE;
      au8Input[0]=0;
      au8Input[1]=0;
  }
 
  if(u8Button == 2)
  {
      LedOff(WHITE);
      LedOff(PURPLE);
      LedOff(BLUE);
      LedOff(CYAN);
      LedOff(GREEN);
      LedOff(YELLOW);
      LedOff(ORANGE);
      LedOff(RED);
      LedOff(LCD_RED);
      LedOff(LCD_GREEN);
      LedOff(LCD_BLUE);
      LedPWM(LCD_RED, LED_PWM_70);
      LedPWM(LCD_GREEN, LED_PWM_25);
      LedPWM(LCD_BLUE, LED_PWM_5);
      DebugPrintf(au8State2);
      LCDCommand(LCD_CLEAR_CMD);
      LCDMessage(LINE1_START_ADDR,au8Message2);
      LedBlink(GREEN, LED_1HZ);
      LedBlink(YELLOW, LED_2HZ);
      LedBlink(ORANGE, LED_4HZ);
      LedBlink(RED, LED_8HZ);
      LedOn(LCD_BLUE);
      PWMAudioOff(BUZZER1);
      PWMAudioOff(BUZZER2);
      PWMAudioSetFrequency(BUZZER1, 200);
      bTime=TRUE;
      u8Button=0;
      }
  
  if(bTime == TRUE)
  {
      u16Counter++;
      if(u16Counter<100)
      {
         PWMAudioOn(BUZZER1);
      }
     
      if(u16Counter == 100)
      {
          PWMAudioOff(BUZZER1);
      }
      if(u16Counter == 1000)
      {
          u16Counter=0;
          PWMAudioOn(BUZZER1);
          
      }
  }
 
  

} /* end UserApp1SM_Idle() */
     
#if 0
/*-------------------------------------------------------------------------------------------------------------------*/
/* Handle an error */
static void UserApp1SM_Error(void)          
{
  
} /* end UserApp1SM_Error() */
#endif


/*-------------------------------------------------------------------------------------------------------------------*/
/* State to sit in if init failed */
static void UserApp1SM_FailedInit(void)          
{
    
} /* end UserApp1SM_FailedInit() */


/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
