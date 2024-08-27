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

    if (((i2c_flags.wr_prot == 1) || (protocolCMD == SEND_BYTE)) && (global_flags.comm_errors == 0) && (protocolCMD != BW_BR_PROC_CALL))
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
void TMR2_CallBack(void)
{
    // 定义需要更新的参数
    UpdateParams update_params[] = 
    {
        {115, READ_VOUT, LINEAR16, 9, READ_VOUT_COMMAND_0x8B},
        {115, READ_VIN, LINEAR11, 3, READ_VIN_COMMAND_0x88},
        // 可以继续添加更多的更新参数...
    };

    // 遍历并调用 Update_Martix_Buffer_Data
    for (int i = 0; i < sizeof(update_params) / sizeof(UpdateParams); i++) {
        Update_Martix_Buffer_Data(
            update_params[i].data,
            update_params[i].buffer,
            update_params[i].linear_select,
            update_params[i].exponent,
            update_params[i].pmbus_index
        );
    }
}

