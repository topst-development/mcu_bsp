/*
***************************************************************************************************
*
*   FileName : hsm_log.h
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

#ifndef HSM_LOG_HEADER
#define HSM_LOG_HEADER

#include <stdio.h>

#define TLOG_VERBOS (5)
#define TLOG_DEBUG (4)
#define TLOG_INFO (3)
#define TLOG_WARNING (2)
#define TLOG_ERROR (1)

#ifndef TLOG_LEVEL
#define TLOG_LEVEL (TLOG_INFO)
#endif

#ifndef TLOG_TAG
#define TLOG_TAG (__func__)
#endif

// #define COLOR_TAG	(1)
/* clang-format off */
#define GRAY_COLOR             "\033[1;30m"
#define NORMAL_COLOR           "\033[0m"
#define RED_COLOR              "\033[1;31m"
#define GREEN_COLOR            "\033[1;32m"
#define MAGENTA_COLOR          "\033[1;35m"
#define YELLOW_COLOR           "\033[1;33m"
#define BLUE_COLOR             "\033[1;34m"
#define DBLUE_COLOR            "\033[0;34m"
#define WHITE_COLOR            "\033[1;37m"
#define COLORERR_COLOR         "\033[1;37;41m"
#define COLORWRN_COLOR         "\033[0;31m"
#define BROWN_COLOR            "\033[0;40;33m"
#define CYAN_COLOR             "\033[0;40;36m"
#define LIGHTGRAY_COLOR        "\033[1;40;37m"
#define BRIGHTRED_COLOR        "\033[0;40;31m"
#define BRIGHTBLUE_COLOR       "\033[0;40;34m"
#define BRIGHTMAGENTA_COLOR    "\033[0;40;35m"
#define BRIGHTCYAN_COLOR       "\033[0;40;36m"
/* clang-format on */

/* no logging */
#define _NLOG(...)               \
    do {                         \
        if (0) {                 \
            mcu_printf(__VA_ARGS__); \
        }                        \
    } while (0)

/* logging */
#ifdef NDEBUG
#define _TLOG(...) _NLOG(__VA_ARGS__)
#else
#define _TLOG(...) mcu_printf(__VA_ARGS__)
#endif

/* Verbose logging */
#if (TLOG_LEVEL >= TLOG_VERBOS)
#define _VLOG(...) _TLOG(__VA_ARGS__)
#else
#define _VLOG(...) _NLOG(__VA_ARGS__)
#endif

/* Debug logging */
#if (TLOG_LEVEL >= TLOG_DEBUG)
#define _DLOG(...) _TLOG(__VA_ARGS__)
#else
#define _DLOG(...) _NLOG(__VA_ARGS__)
#endif

/* Informational logging */
#if (TLOG_LEVEL >= TLOG_INFO)
#define _ILOG(...) _TLOG(__VA_ARGS__)
#else
#define _ILOG(...) _NLOG(__VA_ARGS__)
#endif

/* Warning logging */
#if (TLOG_LEVEL >= TLOG_WARNING)
#define _WLOG(...) _TLOG(__VA_ARGS__)
#else
#define _WLOG(...) _NLOG(__VA_ARGS__)
#endif

/* Error logging */
#if (TLOG_LEVEL >= TLOG_ERROR)
#define _ELOG(...) _TLOG(__VA_ARGS__)
#else
#define _ELOG(...) _NLOG(__VA_ARGS__)
#endif

#ifdef COLOR_TAG
/* color tagging */
#define TRACE _DLOG(NORMAL_COLOR "[%s:%d]\n", TLOG_TAG, __LINE__)
#define VLOG(fmt, ...) \
    _VLOG(BLUE_COLOR "[VERBOSE][%s][%d]" NORMAL_COLOR " " fmt, TLOG_TAG, __LINE__, ##__VA_ARGS__)

#define DLOG(fmt, ...) \
    _DLOG(GREEN_COLOR "[DEBUG][%s][%d]" NORMAL_COLOR " " fmt, TLOG_TAG, __LINE__, ##__VA_ARGS__)

#define ILOG(fmt, ...) \
    _ILOG(YELLOW_COLOR "[INFO][%s][%d]" NORMAL_COLOR " " fmt, TLOG_TAG, __LINE__, ##__VA_ARGS__)

#define WLOG(fmt, ...) \
    _WLOG(COLORWRN_COLOR "[WARN][%s][%d]" NORMAL_COLOR " " fmt, TLOG_TAG, __LINE__, ##__VA_ARGS__)

#define ELOG(fmt, ...) \
    _ELOG(COLORERR_COLOR "[ERROR][%s][%d]" NORMAL_COLOR " " fmt, TLOG_TAG, __LINE__, ##__VA_ARGS__)

#else
/* No color tagging (To avoid Codesonar warning )*/
#define TRACE _DLOG("[%s:%d]\n", TLOG_TAG, __LINE__)
#define VLOG(fmt, ...)      \
    _VLOG(                  \
        "[VERBOSE][%s][%d]" \
        " " fmt,            \
        TLOG_TAG, __LINE__, ##__VA_ARGS__)

#define DLOG(fmt, ...)    \
    _DLOG(                \
        "[DEBUG][%s][%d]" \
        " " fmt,          \
        TLOG_TAG, __LINE__, ##__VA_ARGS__)

#define ILOG(fmt, ...)   \
    _ILOG(               \
        "[INFO][%s][%d]" \
        " " fmt,         \
        TLOG_TAG, __LINE__, ##__VA_ARGS__)

#define WLOG(fmt, ...)   \
    _WLOG(               \
        "[WARN][%s][%d]" \
        " " fmt,         \
        TLOG_TAG, __LINE__, ##__VA_ARGS__)

#define ELOG(fmt, ...)    \
    _ELOG(                \
        "[ERROR][%s][%d]" \
        " " fmt,          \
        TLOG_TAG, __LINE__, ##__VA_ARGS__)
#endif

#endif // HSM_LOG_HEADER
