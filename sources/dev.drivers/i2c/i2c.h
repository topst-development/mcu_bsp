/*
***************************************************************************************************
*
*   FileName : i2c.h
*
*   Copyright (c) Telechips Inc.
*
*   Description :
*
*
***************************************************************************************************
*
*   TCC Version 1.0
*
*   This source code contains confidential information of Telechips.
*
*   Any unauthorized use without a written permission of Telechips including not limited to
*   re-distribution in source or binary form is strictly prohibited.
*
*   This source code is provided "AS IS" and nothing contained in this source code shall constitute
*   any express or implied warranty of any kind, including without limitation, any warranty of
*   merchantability, fitness for a particular purpose or non-infringement of any patent, copyright
*   or other third party intellectual property right. No warranty is made, express or implied,
*   regarding the information's accuracy,completeness, or performance.
*
*   In no event shall Telechips be liable for any claim, damages or other liability arising from,
*   out of or in connection with this source code or the use in the source code.
*
*   This source code is provided subject to the terms of a Mutual Non-Disclosure Agreement between
*   Telechips and Company.
*   This source code is provided "AS IS" and nothing contained in this source code shall constitute
*   any express or implied warranty of any kind, including without limitation, any warranty
*   (of merchantability, fitness for a particular purpose or non-infringement of any patent,
*   copyright or other third party intellectual property right. No warranty is made, express or
*   implied, regarding the information's accuracy, completeness, or performance.
*   In no event shall Telechips be liable for any claim, damages or other liability arising from,
*   out of or in connection with this source code or the use in the source code.
*   This source code is provided subject to the terms of a Mutual Non-Disclosure Agreement
*   between Telechips and Company.
*
***************************************************************************************************
*/

#if !defined(I2C_HEADER)
#define I2C_HEADER

/*
***************************************************************************************************
*                                             INCLUDE FILES
***************************************************************************************************
*/

#include <bsp.h>
#include <clock.h>
#include <gic.h>
#include "gpio.h"
#include <sal_internal.h>
#include <debug.h>
/*
***************************************************************************************************
*                                             DEFINITIONS
***************************************************************************************************
*/

/* I2C Debug message control */

#if (DEBUG_ENABLE)
    #define I2C_D(fmt, args...)         {LOGD(DBG_TAG_I2C, fmt, ## args)}
    #define I2C_E(fmt, args...)         {LOGE(DBG_TAG_I2C, fmt, ## args)}
#else
    #define I2C_D(fmt, args...)
    #define I2C_E(fmt, args...)
#endif

/* I2C Safety Mechanism Test define */
#define I2C_PASSED                      (0UL)
#define I2C_FAILED                      (1UL)

/* I2C Port Array index info */
#define I2C_SCL                         (0UL)
#define I2C_SDA                         (1UL)
#define I2C_FUNC                        (2UL)

/* I2C Operation opionts */
#define I2C_USE_FILTER

/* I2C Event */
#define I2C_EVENT_XFER_COMPLETE         (0x00UL)
#define I2C_EVENT_XFER_ABORT            (0x01UL)
#define I2C_EVENT_NACK                  (0x02UL)

#define I2C_ADDRESS_MASK                (0x7fUL)
#define I2C_ADDRESS_SHIFT               (1UL)

#define I2C_PORT_SEL_MASK               (0x000000FFUL)

/* I2C machine state */
#define I2C_STATUS_IDLE                 (0UL)
#define I2C_STATUS_START                (1UL)
#define I2C_STATUS_WRITE                (3UL)
#define I2C_STATUS_READ                 (2UL)
#define I2C_STATUS_READ_AFTER_ACK       (4UL)
#define I2C_STATUS_WRITE_AFTER_ACK      (5UL)
#define I2C_STATUS_STOP                 (6UL)

#define I2C_SM_STATE_IDLE               (0UL)
#define I2C_SM_STATE_THD_DAT            (1UL)   /* Data hold state */
#define I2C_SM_STATE_TSU_DTA            (2UL)   /* Data Setup state */
#define I2C_SM_STATE_TSU_STA            (3UL)   /* Start Setup state */
#define I2C_SM_STATE_TSU_STO            (4UL)   /* Stop Setpu state */
#define I2C_SM_STATE_DAT_ACK_STD        (5UL)   /* DATA/ACK steady state */

#define I2C_CH_MASTER0                  (0UL)
#define I2C_CH_MASTER1                  (1UL)
#define I2C_CH_MASTER2                  (2UL)

/* I2C transfer state machine */
typedef enum I2CChannelState
{
    I2C_STATE_IDLE                      = 0,
    I2C_STATE_SEND                      = 1,
    I2C_STATE_RECV                      = 2,
    I2C_STATE_RECV_START                = 3,
    I2C_STATE_SEND_DONE                 = 4,
    I2C_STATE_RECV_DONE                 = 5,
    I2C_STATE_DISABLED                  = 6,
    I2C_STATE_RUNNING                   = 7
} I2CChannelState_t;

typedef void (*I2CCallback)
(
    uint8                               ucCh,
    uint32                              iEvent,
    void *                              pArg
);

typedef struct I2CCmdComplete
{
    I2CCallback                         ccCallBack;
    void *                              ccArg;
} I2CCmdComplete_t;

typedef struct I2CAsyncXfer
{
    uint8                               axSlaveAddr;
    uint8 *                             axCmdBuf;
    uint8                               axCmdLen;
    uint8 *                             axOutBuf;
    uint8                               axOutLen;
    uint8 *                             axInBuf;
    uint8                               axInLen;
    uint32                              axOpt;
} I2CAsyncXfer_t;

typedef struct I2CDev
{
    uint32                              dClk;       /* TCC i2c channel */
    uint32                              dBase;      /* i2c base address */
    uint32                              dCfgAddr;   /* i2c configuration address */
    uint32                              dPeriName;  /* peri clock number */
    uint32                              dIobusName; /* iobus number */
    uint32                              dSda;       /* GPIO pins */
    uint32                              dScl;
    uint32                              dPort;
    I2CCmdComplete_t                    dComplete;
    I2CAsyncXfer_t                      dAsync;
    I2CChannelState_t                   dState;
} I2CDev_t;

/*
***************************************************************************************************
*                                         FUNCTION PROTOTYPES
***************************************************************************************************
*/

/*
***************************************************************************************************
*                                          I2C_Xfer
*
* Function to transfer data.
*
* @param    ucCh [in]       : Value of channel to control
* @param    ucSlaveAddr [in]: specific slave address to transfer
* @param    ucOutLen  [in]  : out data length
* @param    ucpOutBuf [out] : out data buffer
* @param    ucInLen   [in]  : in data length (read data legnth)
* @param    ucpInBuf  [in]  : in data buffer (data store after I2C READ)
* @param    uiOpt     [in]  : I2C transfer option
* @param    ucAsync   [in]  : I2C transfer mode
* @return   SAL_RET_SUCCESS or SAL_ERR
* Notes
*           : This function can be called by application to transfer data via I2C.
*
***************************************************************************************************
*/

SALRetCode_t I2C_Xfer
(
    const uint8                         ucCh,
    const uint8                         ucSlaveAddr,
    const uint8                         ucOutLen,
    uint8 *                             ucpOutBuf,
    const uint8                         ucInLen,
    uint8 *                             ucpInBuf,
    uint32                              uiOpt,
    uint8                               ucAsync
);

/*
***************************************************************************************************
*                                          I2C_XferCmd
*
* Function to transfer data with command.
*
* @param    ucCh [in]       : Value of channel to control
* @param    ucSlaveAddr [in]: specific slave address to transfer
* @param    ucCmdLen [in]   : command data length
* @param    ucpCmdBuf [out] : command buffer
* @param    ucOutLen  [in]  : out data length
* @param    ucpOutBuf [out] : out data buffer
* @param    ucInLen   [in]  : in data length (read data legnth)
* @param    ucpInBuf  [in]  : in data buffer (data store after I2C READ)
* @param    uiOpt     [in]  : I2C transfer option
* @param    ucAsync   [in]  : I2C transfer mode
* @return   SAL_RET_SUCCESS or SAL_ERR
* Notes
*
***************************************************************************************************
*/

SALRetCode_t I2C_XferCmd
(
    const uint8                         ucCh,
    const uint8                         ucSlaveAddr,
    const uint8                         ucCmdLen,
    uint8 *                             ucpCmdBuf,
    const uint8                         ucOutLen,
    uint8 *                             ucpOutBuf,
    const uint8                         ucInLen,
    uint8 *                             ucpInBuf,
    uint32                              uiOpt,
    uint8                               ucAsync
);

/*
***************************************************************************************************
*                                          I2C_Open
*
* Function to initialize I2C Channel
*
* @param    ucCh [in]         : Value of channel to control
* @param    iGpioScl [in]     : Index of scl gpio
* @param    iGpioSda [in]     : Index of sda gpio
* @param    uiSpeedInKHz [in] : Value of SCLK speed
* @param    fnCallback [in]   : Fucntion poionter of callback
* @param    pArg
* @return   SAL_RET_SUCCESS or SAL_ERR
* Notes
*
***************************************************************************************************
*/

SALRetCode_t I2C_Open
(
    uint8                               ucCh,
    uint32                              iGpioScl,
    uint32                              iGpioSda,
    uint32                              uiSpeedInKHz,
    I2CCallback                         fnCallback,
    void *                              pArg
);

/*
***************************************************************************************************
*                                          I2C_Close
*
* Function to deinitialize I2C Channel
* @param    ucCh [in]         : Value of channel to control
* @return   SAL_RET_SUCCESS or SAL_ERR
* Notes
*
***************************************************************************************************
*/

SALRetCode_t I2C_Close
(
    uint8                               ucCh
);

/*
***************************************************************************************************
*                                          I2C_Init
*
* Function to register I2C interrupt
*
* @return   SAL_RET_SUCCESS or SAL_ERR
* Notes
*
***************************************************************************************************
*/

void I2C_Init
(
    void
);

/*
***************************************************************************************************
*                                          I2C_Deinit
*
* Function to unregister I2C interrupt
*
* @return
* Notes
*
***************************************************************************************************
*/

void I2C_Deinit
(
    void
);

/*
***************************************************************************************************
*                                          I2C_GetMachineState
*
* Function to get machine state value
*
* @param    ucCh [in]       : Value of channel to control
* @return   Value of I2C channel machine state.
* Notes
*
***************************************************************************************************
*/

uint32 I2C_GetMachineState
(
    uint8                               ucCh
);

/*
***************************************************************************************************
*                                          I2C_ScanSlave
*
* Function to scan slave device address received ACK about selected channel.
*
* @param    ucCh [in]       : Value of channel to control
* @return   Second slave address searched.
* Notes
*
***************************************************************************************************
*/

uint32 I2C_ScanSlave
(
    uint8                               ucCh
);

#endif

