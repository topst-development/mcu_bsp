/*
***************************************************************************************************
*
*   FileName : can_demo.h
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

#ifndef CAN_DEMO_HEADER
#define CAN_DEMO_HEADER

/**************************************************************************************************
*                                           INCLUDE FILES
**************************************************************************************************/

#include <can_config.h>
#include <can.h>


/**************************************************************************************************
*                                            DEFINITIONS
**************************************************************************************************/

#define CAN_DEMO_TASK_STK_SIZE          (2048)
#define CAN_MAX_TEST_MSG_NUM            (9UL)

//#define CAN_DEMO_RESPONSE_TEST          //for CAN response test

typedef struct CANDemoTestInfo
{
    uint8                               tiRecv;
    uint8                               tiSendRecv;
} CANDemoTestInfo_t;


/**************************************************************************************************
*                                          LOCAL VARIABLES
**************************************************************************************************/


/**************************************************************************************************
*                                        FUNCTION PROTOTYPES
**************************************************************************************************/

sint32 CAN_DemoInitialize
(
    void
);

void CAN_DemoTest
(
    uint8                               ucArgc,
    void *                              pArgv[]
);

void CAN_DemoCreateApp
(
    void
);

#endif // CAN_DEMO_HEADER

