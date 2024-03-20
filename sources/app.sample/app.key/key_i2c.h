/*
***************************************************************************************************
*
*   FileName : key_i2c.h
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

#ifndef I2CKEY_H
#define I2CKEY_H

/*
***************************************************************************************************
*                                             INCLUDE FILES
***************************************************************************************************
*/


#include <sal_internal.h>


/*
***************************************************************************************************
*                                             DEFINITIONS
***************************************************************************************************
*/

#define I2C_KEY_SCLK                    (400)
#define I2C_KEY_CHNL                    (0)
#define I2C_KEY_SADR                    (0x90)
#define I2C_KEY_BLEN                    (1)
#define I2C_KEY_RLEN                    (2)
#define I2C_KEY_WLEN1                   (3)
#define I2C_KEY_WLEN2                   (1)

#define I2C_KEY_NULL                    (NULL)

#define I2C_ADS_CNVT                    (0x00)
#define I2C_ADS_CONF                    (0x01)
#define I2C_ADS_LOTH                    (0x10)
#define I2C_ADS_HITH                    (0x10)
#define I2C_ADS_CONF                    (0x01)
#define I2C_ADS_MODE                    (0x01)
#define I2C_ADS_MUXB                    (0x40)
#define I2C_ADS_MUXC                    (0x70)

/* Key definition*/
#define I2C_KEY_MODE                    (0x20)
#define I2C_KEY_SEEKUP                  (0x21)
#define I2C_KEY_SEEKDOWN                (0x22)
#define I2C_KEY_MUTE                    (0x23)
#define I2C_KEY_PHONEON                 (0x24)
#define I2C_KEY_PHONEOFF                (0x25)
#define I2C_KEY_VOLUMEUP                (0x1e)
#define I2C_KEY_VOLUMEDOWN              (0x1f)

enum
{
    KEY_I2CKEY_READ                     = 1,
    KEY_IO_I2CKEY_MODE                  = 2,
    KEY_IO_I2CKEY_MUXX                  = 3,
};

enum {
    KEY_I2C_RELEASED                    = 0,
    KEY_I2C_CHECK,
    KEY_I2C_PRESSED,
    KEY_I2C_PRESSING,
};

typedef struct KEYI2cKeyType
{
    uint32                              uiI2cKeyStatus;
    uint32                              uiI2cOpenOptions;
} KEYI2cKeyType_t;



typedef struct KEYI2cButton
{
    int32                               ibSscancode;
    int32                               ibEscancode;
    uint16                              ibVkcode;
} KEYI2cButton_t;

typedef struct KEYI2cKeyinfo
{
    int32                               iOld_key;
    int32                               iCh;
    int32                               iKey_pressed;
    int32                               iKey_status;
    int32                               iKey_chk_cnt;
} KEYI2cKeyinfo_t;


/*
***************************************************************************************************
*                                         MODULE INTERFACES
***************************************************************************************************
*/
/*
***************************************************************************************************
*                                          KEY_I2cOpen
*
* @param    uiOptions [in]
* @return
*
* Notes
*
***************************************************************************************************
*/
SALRetCode_t KEY_I2cOpen
(
    void
);

/*
***************************************************************************************************
*                                          KEY_I2cRead
*
* @param    buff [in]
* @param    size [in]
* @param    regaddr [in]
* @return
*
* Notes
*
***************************************************************************************************
*/

SALRetCode_t KEY_I2cRead
(
    uint8 *                             puiBuff,
    uint32                              uiSize,
    uint8                               uiRegaddr
);

/*
***************************************************************************************************
*                                          KEY_I2cWrite
*
* @param    puiBuff [in]
* @param    uiSize [in]
* @param    uiRegaddr [in]
* @return
*
* Notes
*
***************************************************************************************************
*/
SALRetCode_t KEY_I2cWrite
(
    uint8 *                             puiBuff,
    uint32                              uiSize,
    uint8                               uiRegaddr
);


int32 KEY_I2cScan
(
    int32                               *piKeyVal,
    int32                               *piKeyPressed
);
#endif /* __HAL_I2CKEY_H__ */

