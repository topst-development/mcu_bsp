/*
***************************************************************************************************
*
*   FileName : can_porting.c
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

/**************************************************************************************************
*                                           INCLUDE FILES
**************************************************************************************************/

#include <bsp.h>
#include <gic.h>
#include <gpio.h>
#include <clock.h>
#include <clock_dev.h>

#include "can_config.h"
#include "can_reg.h"
#include "can.h"
#include "can_par.h"
#include "can_drv.h"
#include "can_porting.h"


/**************************************************************************************************
*                                            DEFINITIONS
**************************************************************************************************/


/**************************************************************************************************
*                                          LOCAL VARIABLES
**************************************************************************************************/


/**************************************************************************************************
*                                        FUNCTION PROTOTYPES
**************************************************************************************************/

void CAN_PortingDelay
(
    uint32                              uiMsDelay
)
{
#if (CAN_SAL_DELAY_SUPPORT == 1)
    SAL_TaskSleep( uiMsDelay );
#else
    uint32 i;
    uint32 uiCnt;

    uiCnt = 0;

    uiCnt = uiMsDelay * 10000UL;

    for( i = 0 ; i < uiCnt ; i++ )
    {
        BSP_NOP_DELAY();
    }
#endif
}

CANErrorType_t CAN_PortingInitHW
(
    const CANController_t *             psControllerInfo
)
{
    CANErrorType_t ret;

    ret = CAN_ERROR_NONE;

    if( psControllerInfo != NULL_PTR )
    {
        switch( psControllerInfo->cChannelHandle )
        {
            case 0:
            {
                PMIO_SetGPK(CAN_0_FS); //Set to normal k-port

                ( void ) GPIO_Config( CAN_0_TX,    ( uint32 ) ( GPIO_FUNC( 2U ) | GPIO_OUTPUT ) ); //can0 tx
                ( void ) GPIO_Config( CAN_0_RX,    ( uint32 ) ( GPIO_FUNC( 2U ) | GPIO_INPUT ) ); //can0 rx
                ( void ) GPIO_Config( CAN_0_STB,   ( uint32 ) ( GPIO_FUNC( 0U ) | GPIO_OUTPUT ) ); //can0 stb
                ( void ) GPIO_Config( CAN_0_INH,   ( uint32 ) ( GPIO_FUNC( 0U ) | GPIO_INPUT ) ); //can0 INH

                ( void ) GPIO_Set( CAN_0_STB, 0UL ); //Set to Low

                break;
            }

            case 1:
            {
                PMIO_SetGPK(CAN_1_FS); //Set to normal k-port

                ( void ) GPIO_Config( CAN_1_TX,    ( uint32 ) ( GPIO_FUNC( 2U ) | GPIO_OUTPUT ) ); //can1 tx
                ( void ) GPIO_Config( CAN_1_RX,    ( uint32 ) ( GPIO_FUNC( 2U ) | GPIO_INPUT ) ); //can1 rx

                /* //CAN_1_STB is not used on EVB
                ( void ) GPIO_Config( CAN_1_STB,   ( uint32 ) ( GPIO_FUNC( 0U ) | GPIO_OUTPUT ) ); //can1 stb

                ( void ) GPIO_Set( CAN_1_STB, 0UL ); //Set to Low
                */

                break;
            }

            case 2:
            {
                PMIO_SetGPK(CAN_2_FS); //Set to normal k-port

                ( void ) GPIO_Config( CAN_2_TX,     ( uint32 ) ( GPIO_FUNC( 2U ) | GPIO_OUTPUT ) ); //can2 tx
                ( void ) GPIO_Config( CAN_2_RX,     ( uint32 ) ( GPIO_FUNC( 2U ) | GPIO_INPUT ) ); //can2 rx

                /* //CAN_2_STB is not used on EVB
                ( void ) GPIO_Config( CAN_2_STB,    ( uint32 ) ( GPIO_FUNC( 0U ) | GPIO_OUTPUT ) ); //can2 stb

                ( void ) GPIO_Set( CAN_2_STB, 0UL ); //Set to Low
                */

                break;
            }

            default:
            {
                ret = CAN_ERROR_BAD_PARAM;

                break;
            }
        }
    }
    else
    {
        ret = CAN_ERROR_NOT_INIT;
    }

    return ret;
}

CANErrorType_t CAN_PortingSetControllerClock
(
    CANController_t *                   psControllerInfo,
    uint32                              uiFreq
)
{
    CANErrorType_t ret;

    ret = CAN_ERROR_NONE;

    if( psControllerInfo != NULL_PTR )
    {
        switch( psControllerInfo->cChannelHandle )
        {
            case 0:
            {
                ( void ) CLOCK_SetPeriRate( ( sint32 ) CLOCK_PERI_CAN0, uiFreq );
                ( void ) CLOCK_EnablePeri( ( sint32 ) CLOCK_PERI_CAN0 );

                psControllerInfo->cFrequency = uiFreq;

                break;
            }

            case 1:
            {
                ( void ) CLOCK_SetPeriRate( ( sint32 ) CLOCK_PERI_CAN1, uiFreq );
                ( void ) CLOCK_EnablePeri( ( sint32 ) CLOCK_PERI_CAN1 );

                psControllerInfo->cFrequency = uiFreq;

                break;
            }
            case 2:
            {
                ( void ) CLOCK_SetPeriRate( ( sint32 ) CLOCK_PERI_CAN2, uiFreq );
                ( void ) CLOCK_EnablePeri( ( sint32 ) CLOCK_PERI_CAN2 );

                psControllerInfo->cFrequency = uiFreq;

                break;
            }

            default:
            {
                ret = CAN_ERROR_BAD_PARAM;

                break;
            }
        }
    }

    return ret;
}

CANErrorType_t CAN_PortingResetDriver
(
    const CANController_t *             psControllerInfo
)
{
    CANErrorType_t ret;

    ret = CAN_ERROR_NONE;

    if( psControllerInfo != NULL_PTR )
    {
        switch( psControllerInfo->cChannelHandle )
        {
            case 0:
            {
                CAN_BUS_CLK_MASK_REG_0 |= ( ( uint32 ) 1UL << CAN_CFG_REG_FIELD_CAN_0 );
                CAN_SW_RESET_REG_0 &= ( ~( ( uint32 ) 1UL << CAN_CFG_REG_FIELD_CAN_0 ) );
                CAN_PortingDelay( 1 );

                CAN_SW_RESET_REG_0 = CAN_BUS_CLK_MASK_REG_0 | ( ( uint32 ) 1UL << CAN_CFG_REG_FIELD_CAN_0 );

                break;
            }

            case 1:
            {
                CAN_BUS_CLK_MASK_REG_0 |= ( ( uint32 ) 1UL << CAN_CFG_REG_FIELD_CAN_1 );
                CAN_SW_RESET_REG_0 &= ( ~( ( uint32 ) 1UL << CAN_CFG_REG_FIELD_CAN_1 ) );
                CAN_PortingDelay( 1 );

                CAN_SW_RESET_REG_0 |= ( ( uint32 ) 1UL << CAN_CFG_REG_FIELD_CAN_1 );

                break;
            }

            case 2:
            {
                CAN_BUS_CLK_MASK_REG_0 |= ( ( uint32 ) 1UL << CAN_CFG_REG_FIELD_CAN_2 );
                CAN_SW_RESET_REG_0 &= ( ~( ( uint32 ) 1UL << CAN_CFG_REG_FIELD_CAN_2 ) );
                CAN_PortingDelay( 1 );

                CAN_SW_RESET_REG_0 |= ( ( uint32 ) 1UL << CAN_CFG_REG_FIELD_CAN_2 );

                break;
            }

            default:
            {
                ret = CAN_ERROR_BAD_PARAM;

                break;
            }
        }
    }

    return ret;
}

CANErrorType_t CAN_PortingSetInterruptHandler
(
    CANController_t *                   psControllerInfo,
    GICIsrFunc                          fnIsr
)
{
    CANErrorType_t ret;

    ret = CAN_ERROR_BAD_PARAM;

    if( ( psControllerInfo != NULL_PTR ) && ( fnIsr != NULL_PTR ) )
    {
#if (CAN_INTERRUPT_LINE == 0)
        ( void ) GIC_IntVectSet( ( uint32 ) GIC_CAN0_0 + ( ( uint32 ) psControllerInfo->cChannelHandle * 2UL ), GIC_PRIORITY_NO_MEAN, GIC_INT_TYPE_LEVEL_HIGH, fnIsr, ( void * ) &( psControllerInfo->cChannelHandle ) );
#elif (CAN_INTERRUPT_LINE == 1)
        ( void ) GIC_IntVectSet( ( uint32 ) GIC_CAN0_1 + ( ( uint32 ) psControllerInfo->cChannelHandle * 2UL ), GIC_PRIORITY_NO_MEAN, GIC_INT_TYPE_LEVEL_HIGH, fnIsr, ( void * ) &( psControllerInfo->cChannelHandle ) );
#else
        ##### ERROR - Select CAN Interrupt Line #####
#endif
        ret = CAN_ERROR_NONE;
    }

    return ret;
}

CANErrorType_t CAN_PortingDisableControllerInterrupts
(
    uint8                               ucCh
)
{
    CANErrorType_t ret;

    ret = CAN_ERROR_BAD_PARAM;

    if( ucCh < CAN_CONTROLLER_NUMBER )
    {
#if (CAN_INTERRUPT_LINE == 0)
        ( void ) GIC_IntSrcDis( ( uint32 ) GIC_CAN0_0 + ( ( uint32 ) ucCh * 2UL ) );
#elif (CAN_INTERRUPT_LINE == 1)
        ( void ) GIC_IntSrcDis( ( uint32 ) GIC_CAN0_1 + ( ( uint32 ) ucCh * 2UL ) );
#else
        ##### ERROR - Select CAN Interrupt Line #####
#endif
        ret = CAN_ERROR_NONE;
    }

    return ret;
}

CANErrorType_t CAN_PortingEnableControllerInterrupts
(
    uint8                               ucCh
)
{
    CANErrorType_t ret;

    ret = CAN_ERROR_BAD_PARAM;

    if( ucCh < CAN_CONTROLLER_NUMBER )
    {
#if (CAN_INTERRUPT_LINE == 0)
        ( void ) GIC_IntSrcEn( ( uint32 ) GIC_CAN0_0 + ( ( uint32 ) ucCh * 2UL ) );
#elif (CAN_INTERRUPT_LINE == 1)
        ( void ) GIC_IntSrcEn( ( uint32 ) GIC_CAN0_1 + ( ( uint32 ) ucCh * 2UL ) );
#else
        ##### ERROR - Select CAN Interrupt Line #####
#endif
        ret = CAN_ERROR_NONE;
    }

    return ret;
}

uint32 CAN_PortingGetSizeofStandardIDFilterList
(
    uint8                               ucCh
)
{
    uint32 uiSize;

    uiSize = 0;

    if( ucCh < CAN_CONTROLLER_NUMBER )
    {
        uiSize = CAN_STANDARD_ID_FILTER_NUMBER_MAX * CAN_STANDARD_ID_FILTER_SIZE;
    }

    return uiSize;
}

uint32 CAN_PortingGetSizeofExtendedIDFilterList
(
    uint8                               ucCh
)
{
    uint32 uiSize;

    uiSize = 0;

    if( ucCh < CAN_CONTROLLER_NUMBER )
    {
        uiSize = CAN_EXTENDED_ID_FILTER_NUMBER_MAX * CAN_EXTENDED_ID_FILTER_SIZE;
    }

    return uiSize;
}

uint32 CAN_PortingGetSizeofRxFIFO0
(
    uint8                               ucCh
)
{
    uint32 uiSize;

    uiSize = 0;

    if( ucCh < CAN_CONTROLLER_NUMBER )
    {
        uiSize = CAN_RX_FIFO_0_MAX * CAN_BUFFER_SIZE;
    }

    return uiSize;
}

uint32 CAN_PortingGetSizeofRxFIFO1
(
    uint8                               ucCh
)
{
    uint32 uiSize;

    uiSize = 0;

    if( ucCh < CAN_CONTROLLER_NUMBER )
    {
        uiSize = CAN_RX_FIFO_1_MAX * CAN_BUFFER_SIZE;
    }

    return uiSize;
}

uint32 CAN_PortingGetSizeofRxBuffer
(
    uint8                               ucCh
)
{
    uint32 uiSize;

    uiSize = 0;

    if( ucCh < CAN_CONTROLLER_NUMBER )
    {
        uiSize = CAN_RX_BUFFER_MAX * CAN_BUFFER_SIZE;
    }

    return uiSize;
}

uint32 CAN_PortingGetSizeofTxEventBuffer
(
    uint8                               ucCh
)
{
    uint32 uiSize;

    uiSize = 0;

    if( ucCh < CAN_CONTROLLER_NUMBER )
    {
        uiSize = CAN_TX_EVENT_FIFO_MAX * CAN_TX_EVENT_SIZE;
    }

    return uiSize;
}

uint32 CAN_PortingGetSizeofTxBuffer
(
    uint8                               ucCh
)
{
    uint32 uiSize;

    uiSize = 0;

    if( ucCh < CAN_CONTROLLER_NUMBER )
    {
        uiSize = CAN_TX_BUFFER_MAX * CAN_BUFFER_SIZE;
    }

    return uiSize;
}

uint8 CAN_PortingGetBitRateSwitchEnable
(
    uint8                               ucCh
)
{
    uint8 ret;

    ret = FALSE;

    if( ucCh < CAN_CONTROLLER_NUMBER )
    {
        ret = TRUE;
    }

    return ret;
}

uint8 CAN_PortingGetFDEnable
(
    uint8                               ucCh
)
{
    uint8 ret;

    ret = FALSE;

    if( ucCh < CAN_CONTROLLER_NUMBER )
    {
        ret = TRUE;
    }

    return ret;
}

uint8 CAN_PortingGetStandardIDFilterEnable
(
    uint8                               ucCh
)
{
    uint8 ret;

    ret = FALSE;

    if( ucCh < CAN_CONTROLLER_NUMBER )
    {
        ret = TRUE;
    }

    return ret;
}

uint8 CAN_PortingGetExtendedIDFilterEnable
(
    uint8                               ucCh
)
{
    uint8 ret;

    ret = FALSE;

    if( ucCh < CAN_CONTROLLER_NUMBER )
    {
        ret = TRUE;
    }

    return ret;
}

uint8 CAN_PortingGetStandardIDRemoteRejectEnable
(
    uint8                               ucCh
)
{
    uint8 ret;

    ret = FALSE;

    if( ucCh < CAN_CONTROLLER_NUMBER )
    {
        ret = TRUE;
    }

    return ret;
}

uint8 CAN_PortingGetExtendedIDRemoteRejectEnable
(
    uint8                               ucCh
)
{
    uint8 ret;

    ret = FALSE;

    if( ucCh < CAN_CONTROLLER_NUMBER )
    {
        ret = TRUE;
    }

    return ret;
}

uint8 CAN_PortingGetTxEventFIFOEnable
(
    uint8                               ucCh
)
{
    uint8 ret;

    ret = FALSE;

    if( ucCh < CAN_CONTROLLER_NUMBER )
    {
        ret = TRUE;
    }

    return ret;
}

uint8 CAN_PortingGetWatchDogEnable
(
    uint8                               ucCh
)
{
    uint8 ret;

    ret = FALSE;

    if( ucCh < CAN_CONTROLLER_NUMBER )
    {
        ret = TRUE;
    }

    return ret;
}

uint8 CAN_PortingGetTimeOutEnable
(
    uint8                               ucCh
)
{
    uint8 ret;

    ret = FALSE;

    if( ucCh < CAN_CONTROLLER_NUMBER )
    {
        ret = TRUE;
    }

    return ret;
}

uint8 CAN_PortingGetTimeStampEnable
(
    uint8                               ucCh
)
{
    uint8 ret;

    ret = FALSE;

    if( ucCh < CAN_CONTROLLER_NUMBER )
    {
        ret = TRUE;
    }

    return ret;
}

uint32 CAN_PortingAllocateNonCacheMemory
(
    uint8                               ucCh,
    uint32                              uiMemSize
)
{
    uint32 uiMemAddr;
    uint32 uiAlignedMemSize;

    uiMemAddr           = NULL;
    uiAlignedMemSize    = 0;

    if( ucCh < CAN_CONTROLLER_NUMBER )
    {
        uiAlignedMemSize = uiMemSize & 0xFFFFF000UL;

        if( ( uiMemSize & 0xFFFUL ) != 0UL )
        {
            uiAlignedMemSize += 0x1000UL;
        }

        uiMemAddr = CAN_NON_CACHE_MEMORY_START + ( uiAlignedMemSize * ucCh );
    }

    return uiMemAddr;
}

void CAN_PortingDeallocateNonCacheMemory
(
    uint8                               ucCh,
    uint32 *                            puiMemAddr
)
{
    if( ucCh < CAN_CONTROLLER_NUMBER )
    {
        *puiMemAddr = ( uint32 ) 0;
    }
}

uint32 CAN_PortingGetControllerRegister
(
    uint8                               ucCh
)
{
    uint32 uiControllerAddr;

    uiControllerAddr = NULL;

    if( ucCh < CAN_CONTROLLER_NUMBER )
    {
        uiControllerAddr = MCU_BSP_CAN_FD_BASE + ( CAN_CHANNEL_ADDR_OFFSET * ( uint32 ) ucCh );
    }

    return uiControllerAddr;
}

uint32 CAN_PortingGetConfigBaseAddr
(
    void
)
{
    uint32 uiAddr;

    uiAddr = CAN_CONFIG_ADDR;

    return uiAddr;
}

uint32 CAN_PortingGetMessageRamBaseAddr
(
    uint8                               ucCh
)
{
    uint32 uiAddr;

    uiAddr = NULL;

    if( ucCh < CAN_CONTROLLER_NUMBER )
    {
        uiAddr = CAN_CONFIG_BASE_ADDR + ( ( uint32 ) 0x4UL * ( uint32 ) ucCh );
    }

    return uiAddr;
}

uint32 CAN_PortingGetConfigEXTS0Addr
(
    uint8                               ucCh
)
{
    uint32 uiAddr;

    uiAddr = NULL;

    if( ucCh < CAN_CONTROLLER_NUMBER )
    {
        uiAddr = CAN_CONFIG_EXTS_CTRL0_ADDR;
    }

    return uiAddr;
}

uint32 CAN_PortingGetConfigEXTS1Addr
(
    uint8                               ucCh
)
{
    uint32 uiAddr;

    uiAddr = NULL;

    if( ucCh < CAN_CONTROLLER_NUMBER )
    {
        uiAddr = CAN_CONFIG_EXTS_CTRL1_ADDR;
    }

    return uiAddr;
}

uint32 CAN_PortingGetConfigWritePasswordAddr
(
    uint8                               ucCh
)
{
    uint32 uiAddr;

    uiAddr = NULL;

    if( ucCh < CAN_CONTROLLER_NUMBER )
    {
        uiAddr = CAN_CONFIG_WR_PW_ADDR;
    }

    return uiAddr;
}

uint32 CAN_PortingGetConfigWriteLockAddr
(
    uint8                               ucCh
)
{
    uint32 uiAddr;

    uiAddr = NULL;

    if( ucCh < CAN_CONTROLLER_NUMBER )
    {
        uiAddr = CAN_CONFIG_WR_LOCK_ADDR;
    }

    return uiAddr;
}

