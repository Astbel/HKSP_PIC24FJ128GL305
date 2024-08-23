/************************************************/
/*   Include    Files                           */
/************************************************/
#include <stdio.h>
#include"../inc/Gernirc_Type.h"
#include "../inc/pmbus_stack.h"
#include "../mcc_generated_files/i2c1.h"
#include "../mcc_generated_files/tmr1.h"
#include "../inc/pmbus_stack.h"

/********************************************************************
 * Function:        Timer1 ISR
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This interruput service routine determines when a
 *				           stop condition has occured and enables buffer to ram
 *				           copy if the command was a write protocol.
 *
 * Note:            None
 *******************************************************************/
void __attribute__((weak)) TMR1_CallBack(void)
{
  IFS0bits.T1IF = 0;
  TMR1 = 0;
  if ((I2C1STATbits.P == 1) && (IFS1bits.SI2C1IF == 0))
  {
    T1CONbits.TON = 0;

    if (((i2c_flags.wr_prot == 1) || (protocolCMD == 0x0)) && (global_flags.comm_errors == 0) && (protocolCMD != 0x4))
    {
      if (codeCMD == 0x3) /* Example of call to an APP function */
      {
        Clear_faults();
      }

      global_flags.ready_to_copy = 1; /* If command was write transaction setting this flag allows
                          data to be copied from buffer to RAM */
      if (global_flags.ready_to_copy == 1)
      {
        global_flags.ready_to_copy = 0;
        CopyBufferInRam();
      }
    }

    i2c_flags.flag_rw = 0;

    I2C1CONLbits.SCLREL = 1; /* Release SCL Clock */
  }
}

/********************************************************************
 * Function:        Timer2 ISR
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This interruput service routine determines when a
 *				           stop condition has occured and enables buffer to ram
 *				           copy if the command was a write protocol.
 *
 * Note:            None
 *******************************************************************/
void __attribute__ ((weak)) TMR2_CallBack(void)
{
   
    Update_Martix_Buffer_Data(115,READ_VOUT,LINEAR16,9,READ_VOUT_COMMAND_0x8B);
    Update_Martix_Buffer_Data(115,READ_VIN,LINEAR11,3,READ_VIN_COMMAND_0x88);
}

