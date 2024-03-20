/*
 * FreeRTOS Kernel V10.3.1
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

//#include "xparameters.h"

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 *
 * See http://www.freertos.org/a00110.html
 *----------------------------------------------------------*/

/*
 * The FreeRTOS Cortex-A port implements a full interrupt nesting model.
 *
 * Interrupts that are assigned a priority at or below
 * configMAX_API_CALL_INTERRUPT_PRIORITY (which counter-intuitively in the ARM
 * generic interrupt controller [GIC] means a priority that has a numerical
 * value above configMAX_API_CALL_INTERRUPT_PRIORITY) can call FreeRTOS safe API
 * functions and will nest.
 *
 * Interrupts that are assigned a priority above
 * configMAX_API_CALL_INTERRUPT_PRIORITY (which in the GIC means a numerical
 * value below configMAX_API_CALL_INTERRUPT_PRIORITY) cannot call any FreeRTOS
 * API functions, will nest, and will not be masked by FreeRTOS critical
 * sections (although it is necessary for interrupts to be globally disabled
 * extremely briefly as the interrupt mask is updated in the GIC).
 *
 * FreeRTOS functions that can be called from an interrupt are those that end in
 * "FromISR".  FreeRTOS maintains a separate interrupt safe API to enable
 * interrupt entry to be shorter, faster, simpler and smaller.
 *
 * Setting this value to zero means that nesting interrupts are not used.
 */
#define configMAX_API_CALL_INTERRUPT_PRIORITY	0//(16 -2)

#define configCPU_CLOCK_HZ						100000000UL
#define configUSE_PORT_OPTIMISED_TASK_SELECTION	0
#define configUSE_TICKLESS_IDLE					0
#define configTICK_RATE_HZ						( ( TickType_t ) 1000UL )
#define configPERIPHERAL_CLOCK_HZ  				( 33333000UL )
#define configUSE_PREEMPTION					1
#define configUSE_IDLE_HOOK						0
#ifdef TCC_FREERTOS_DEMO
#define configUSE_TICK_HOOK						1 //TCC_DEMO
#else
#define configUSE_TICK_HOOK						0 //org
#endif
#define configMAX_PRIORITIES					( 16 )
#define configMINIMAL_STACK_SIZE				( ( unsigned short ) 250 ) /* Large in case configUSE_TASK_FPU_SUPPORT is 2 in which case all tasks have an FPU context. */
#ifdef TCC_FREERTOS_DEMO
#define configTOTAL_HEAP_SIZE					( 100 * 1024 )
#else
#define configTOTAL_HEAP_SIZE					( 1 * 1024 )
#endif
#define configMAX_TASK_NAME_LEN					( 30 )
#define configUSE_TRACE_FACILITY				0
#define configUSE_16_BIT_TICKS					0
#define configIDLE_SHOULD_YIELD					1
#define configUSE_MUTEXES						1
#define configQUEUE_REGISTRY_SIZE				8
#define configCHECK_FOR_STACK_OVERFLOW			2
#define configUSE_RECURSIVE_MUTEXES				1
#define configUSE_MALLOC_FAILED_HOOK			0
#define configUSE_APPLICATION_TASK_TAG			0
#define configUSE_COUNTING_SEMAPHORES			1
#define configUSE_QUEUE_SETS					1
#define configUSE_TASK_NOTIFICATIONS			1
#define configSUPPORT_STATIC_ALLOCATION			1 // for MICOM system. use static allocation for os resource
#define configSUPPORT_DYNAMIC_ALLOCATION        1
/* Defaults to uint16_t for backward compatibility, but can be overridden in FreeRTOSConfig.h if uint16_t is too restrictive. */
#define configSTACK_DEPTH_TYPE uint32_t

/* Co-routine definitions. */
#define configUSE_CO_ROUTINES 					0
#define configMAX_CO_ROUTINE_PRIORITIES 		( 2 )

/* Software timer definitions. */
#define configUSE_TIMERS						1
#define configTIMER_TASK_PRIORITY				( configMAX_PRIORITIES - 1 )
#define configTIMER_QUEUE_LENGTH				5
#define configTIMER_TASK_STACK_DEPTH			( configMINIMAL_STACK_SIZE * 2 )

/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */
#define INCLUDE_vTaskPrioritySet				1
#define INCLUDE_uxTaskPriorityGet				1
#define INCLUDE_vTaskDelete						1
#define INCLUDE_vTaskCleanUpResources			1
#define INCLUDE_vTaskSuspend					1
#define INCLUDE_vTaskDelayUntil					1
#define INCLUDE_vTaskDelay						1
#define INCLUDE_xTimerPendFunctionCall			1
#define INCLUDE_eTaskGetState					1
#define INCLUDE_xTaskAbortDelay					1
#define INCLUDE_xTaskGetHandle					1
#define INCLUDE_xSemaphoreGetMutexHolder		1

/* This demo makes use of one or more example stats formatting functions.  These
format the raw data provided by the uxTaskGetSystemState() function in to human
readable ASCII form.  See the notes in the implementation of vTaskList() within
FreeRTOS/Source/tasks.c for limitations. */
#define configUSE_STATS_FORMATTING_FUNCTIONS	1

/* The private watchdog is used to generate run time stats. */
//#include "xscuwdt.h"
//extern XScuWdt xWatchDogInstance;
extern void vInitialiseTimerForRunTimeStats( void );
#define configGENERATE_RUN_TIME_STATS 0 // because use sprintf
#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS() vInitialiseTimerForRunTimeStats()
#define portGET_RUN_TIME_COUNTER_VALUE() (1)//( ( 0xffffffffUL - XScuWdt_ReadReg( xWatchDogInstance.Config.BaseAddr, XSCUWDT_COUNTER_OFFSET ) ) >> 1 ) //hskim temp

/* The size of the global output buffer that is available for use when there
are multiple command interpreters running at once (for example, one on a UART
and one on TCP/IP).  This is done to prevent an output buffer being defined by
each implementation - which would waste RAM.  In this case, there is only one
command interpreter running. */
#define configCOMMAND_INT_MAX_OUTPUT_SIZE 2096

/* Normal assert() semantics without relying on the provision of an assert.h
header file. */
//void vAssertCalled( const char * pcFile, unsigned long ulLine );
//#define configASSERT( x ) if( ( x ) == 0 ) vAssertCalled( __FILE__, __LINE__ );
#define configASSERT( x )	if( ( x ) == 0 ) { /*taskDISABLE_INTERRUPTS();*/ for( ;; ); }

/* If configTASK_RETURN_ADDRESS is not defined then a task that attempts to
return from its implementing function will end up in a "task exit error"
function - which contains a call to configASSERT().  However this can give GCC
some problems when it tries to unwind the stack, as the exit error function has
nothing to return to.  To avoid this define configTASK_RETURN_ADDRESS to 0.  */
#define configTASK_RETURN_ADDRESS	NULL


/****** Hardware specific settings. *******************************************/

/*
 * The application must provide a function that configures a peripheral to
 * create the FreeRTOS tick interrupt, then define configSETUP_TICK_INTERRUPT()
 * in FreeRTOSConfig.h to call the function.  This file contains a function
 * that is suitable for use on the Zynq MPU.  FreeRTOS_Tick_Handler() must
 * be installed as the peripheral's interrupt handler.
 */
void vConfigureTickInterrupt( void );
#define configSETUP_TICK_INTERRUPT() vConfigureTickInterrupt()

void vClearTickInterrupt( void );
#define configCLEAR_TICK_INTERRUPT() vClearTickInterrupt()

//#define  BSP_INT_GIC_CBUS_DIST_REG    ((ARM_REG_GIC_DIST_PTR)(0x17300000 + 0x1000u))
//#define  BSP_INT_GIC_CBUS_IF_REG      ((ARM_REG_GIC_IF_PTR)(0x17300000 + 0x2000u))
//#define  BSP_INT_GIC_DIST_REG         ((ARM_REG_GIC_DIST_PTR)(0x17F00000 + 0x1000u))
//#define  BSP_INT_GIC_IF_REG           ((ARM_REG_GIC_IF_PTR)(0x17F00000 + 0x2000u))
#if defined(TCC803x)||defined(TCC805x)
#define configINTERRUPT_CONTROLLER_BASE_ADDRESS 		(0x1B900000 + 0x1000u) //hskim temp
#define configINTERRUPT_CONTROLLER_CPU_INTERFACE_OFFSET ( 0x1000u )
#define configUNIQUE_INTERRUPT_PRIORITIES				32 // tcc8030 32 supported levels bit[2.0]= 0b000 on GICC_PMR
#else//TCC802x
#define configINTERRUPT_CONTROLLER_BASE_ADDRESS 		(0x17F00000 + 0x1000u) //hskim temp
#define configINTERRUPT_CONTROLLER_CPU_INTERFACE_OFFSET ( 0x1000u )
#define configUNIQUE_INTERRUPT_PRIORITIES				16//32
#endif


#endif /* FREERTOS_CONFIG_H */

