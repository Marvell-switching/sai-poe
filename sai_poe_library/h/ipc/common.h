/*******************************************************************************
   Copyright (C) Marvell International Ltd. and its affiliates
********************************************************************************
Marvell GNU General Public License FreeRTOS Exception

If you received this File from Marvell, you may opt to use, redistribute and/or
modify this File in accordance with the terms and conditions of the Lesser
General Public License Version 2.1 plus the following FreeRTOS exception.
An independent module is a module which is not derived from or based on
FreeRTOS.
Clause 1:
Linking FreeRTOS statically or dynamically with other modules is making a
combined work based on FreeRTOS. Thus, the terms and conditions of the GNU
General Public License cover the whole combination.
As a special exception, the copyright holder of FreeRTOS gives you permission
to link FreeRTOS with independent modules that communicate with FreeRTOS solely
through the FreeRTOS API interface, regardless of the license terms of these
independent modules, and to copy and distribute the resulting combined work
under terms of your choice, provided that:
1. Every copy of the combined work is accompanied by a written statement that
details to the recipient the version of FreeRTOS used and an offer by yourself
to provide the FreeRTOS source code (including any modifications you may have
made) should the recipient request it.
2. The combined work is not itself an RTOS, scheduler, kernel or related
product.
3. The independent modules add significant and primary functionality to
FreeRTOS and do not merely extend the existing functionality already present in
FreeRTOS.
Clause 2:
FreeRTOS may not be used for any competitive or comparative purpose, including
the publication of any form of run time or compile time metric, without the
express permission of Real Time Engineers Ltd. (this is the norm within the
industry and is intended to ensure information accuracy).
*******************************************************************************/

#ifndef COMMON_H

#define MV_CPU_LE

#define DEFAULT_DEV0_NUM    ( 0 )
#define DEFAULT_DEV1_NUM    ( 1 ) 

#define ENABLE_DCACHE		( 1 )
#define ENABLE_ICACHE		( 1 )
#ifndef MSYS_RUN_WITH_SRAM
#define ENABLE_L2			( 1 )
#define ENABLE_IOCC			( 1 )
#else
#define ENABLE_L2			( 0 )
#define ENABLE_IOCC			( 0 )
#endif

#define INTER_REGS_BASE		( 0xF1000000 )
#define MMU_SECTION_SHIFT	( 20 )
#define MMU_PTE_COUNT		( 4096 )
#define MMU_PTE_SIZE		( MMU_PTE_COUNT * 4 )
#define MMU_ORDERED_PT		( 0xF2000000 )
#define PTE_B				( 1 << 2 )
#define PTE_C				( 1 << 3 )
#define PTE_TEX0			( 1 << 12 )
#define PTE_INVALID			( 1 << 31 )
#define PTE_ORDERED			( 0 )
#define PTE_WB				( PTE_C | PTE_B )
#define PTE_WBWA			( PTE_WB | PTE_TEX0 )
#define PTE_MEMORY			( PTE_WBWA )
#define CPU_SVC_STACK_SIZE	( 0x300 )
#define CPU_IRQ_STACK_SIZE	( 0x300 )
#define CPU_ABT_STACK_SIZE	( 0x100 )
#define CPU_UND_STACK_SIZE	( 0x100 )
#define CPU_SUM_STACK_SIZE	( CPU_SVC_STACK_SIZE + CPU_IRQ_STACK_SIZE + \
							  CPU_ABT_STACK_SIZE + CPU_UND_STACK_SIZE )
#define SZ_1M				( 0x100000 )
#define SZ_16M				( 0x1000000 )

#ifndef __ASSEMBLY__
#define COMMON_H

#include <stdlib.h>
/*#include <FreeRTOS.h> */

extern unsigned long uCpuId;
extern unsigned long uBootParams;
extern unsigned long uPageTable;
extern unsigned long uKernelStart;
extern unsigned long uKernelEnd;

#define CPUID				( uCpuId )

/* Supported clocks */
#define MV_BOARD_TCLK_100MHZ	100000000
#define MV_BOARD_TCLK_125MHZ	125000000
#define MV_BOARD_TCLK_133MHZ	133333333
#define MV_BOARD_TCLK_150MHZ	150000000
#define MV_BOARD_TCLK_166MHZ	166666667
#define MV_BOARD_TCLK_200MHZ	200000000
#define MV_BOARD_TCLK_250MHZ	250000000

#ifndef CONFIG_MV_AMP_DISABLE
#define CONFIG_MV_AMP_ENABLE
#endif

#define MV88F78X60

#define NR_CPUS 4
#define MV_BOARD_REFCLK_25MHZ		( 25000000 )

/* Function wrappers */
#define whoAmI()				CPUID
#define master_cpu_id			CPUID	/* XXX only single core supported */
#define mvOsMemset( p, v, s )	memset(( void * )( p ), ( long )v, ( size_t )s )
#define udelay( us )			UDELAY( us )
#define mvOsPrintf				printf

#ifdef CONFIG_SHEEVA_ERRATA_ARM_CPU_6075
#define dmb()					__asm__ __volatile__ ("dsb" : : : "memory")
#else
#define dmb()					__asm__ __volatile__ ("dmb" : : : "memory")
#endif

/* Register offsets */
#define MV_MBUS_REGS_OFFSET			( 0x20000 )
#define MV_CPUIF_LOCAL_REGS_OFFSET	( 0x21000 )
#define MV_CPUIF_REGS_OFFSET( cpu )	( 0x21800 + ( cpu ) * 0x100 )
#define MV_CPUIF_REGS_BASE( cpu )	( MV_CPUIF_REGS_OFFSET( cpu ))
#define MV_CNTMR_REGS_OFFSET		( 0x20300 )
#define MV_AURORA_L2_REGS_OFFSET	( 0x8000 )
#define MV_COHERENCY_FABRIC_OFFSET	( 0x20200 )

/* Common definitions */
#define BIT0					( 0x01 )
#define BIT1					( 0x02 )
#define BIT2					( 0x04 )
#define BIT3					( 0x08 )
#define BIT4					( 0x10 )
#define BIT5					( 0x20 )
#define BIT6					( 0x40 )
#define BIT7					( 0x80 )
#define BIT8		                        ( 0x00000100 )
#define BIT9		                        ( 0x00000200 )
#define BIT10		                        ( 0x00000400 )
#define BIT11		                        ( 0x00000800 )
#define BIT12		                        ( 0x00001000 )
#define BIT13		                        ( 0x00002000 )
#define BIT14		                        ( 0x00004000 )
#define BIT15		                        ( 0x00008000 )
#define BIT16		                        ( 0x00010000 )

/* The following is a list of Marvell status    */
#define MV_ERROR		    (-1)
#define MV_OK			    (0x00)  /* Operation succeeded                   */
#define MV_FAIL			    (0x01)	/* Operation failed                      */
#define MV_BAD_VALUE        (0x02)  /* Illegal value (general)               */
#define MV_OUT_OF_RANGE     (0x03)  /* The value is out of range             */
#define MV_BAD_PARAM        (0x04)  /* Illegal parameter in function called  */
#define MV_BAD_PTR          (0x05)  /* Illegal pointer value                 */
#define MV_BAD_SIZE         (0x06)  /* Illegal size                          */
#define MV_BAD_STATE        (0x07)  /* Illegal state of state machine        */
#define MV_SET_ERROR        (0x08)  /* Set operation failed                  */
#define MV_GET_ERROR        (0x09)  /* Get operation failed                  */
#define MV_CREATE_ERROR     (0x0A)  /* Fail while creating an item           */
#define MV_NOT_FOUND        (0x0B)  /* Item not found                        */
#define MV_NO_MORE          (0x0C)  /* No more items found                   */
#define MV_NO_SUCH          (0x0D)  /* No such item                          */
#define MV_TIMEOUT          (0x0E)  /* Time Out                              */
#define MV_NO_CHANGE        (0x0F)  /* Parameter(s) is already in this value */
#define MV_NOT_SUPPORTED    (0x10)  /* This request is not support           */
#define MV_NOT_IMPLEMENTED  (0x11)  /* Request supported but not implemented */
#define MV_NOT_INITIALIZED  (0x12)  /* The item is not initialized           */
#define MV_NO_RESOURCE      (0x13)  /* Resource not available (memory ...)   */
#define MV_FULL             (0x14)  /* Item is full (Queue or table etc...)  */
#define MV_EMPTY            (0x15)  /* Item is empty (Queue or table etc...) */
#define MV_INIT_ERROR       (0x16)  /* Error occured while INIT process      */
#define MV_HW_ERROR         (0x17)  /* Hardware error                        */
#define MV_TX_ERROR         (0x18)  /* Transmit operation not succeeded      */
#define MV_RX_ERROR         (0x19)  /* Recieve operation not succeeded       */
#define MV_NOT_READY	    (0x1A)	/* The other side is not ready yet       */
#define MV_ALREADY_EXIST    (0x1B)  /* Tried to create existing item         */
#define MV_OUT_OF_CPU_MEM   (0x1C)  /* Cpu memory allocation failed.         */
#define MV_NOT_STARTED      (0x1D)  /* Not started yet         */
#define MV_BUSY             (0x1E)  /* Item is busy.                         */
#define MV_TERMINATE        (0x1F)  /* Item terminates it's work.            */
#define MV_NOT_ALIGNED      (0x20)  /* Wrong alignment                       */
#define MV_NOT_ALLOWED      (0x21)  /* Operation NOT allowed                 */
#define MV_WRITE_PROTECT    (0x22)  /* Write protected                       */

/* Endianess macros.														*/
#if defined( MV_CPU_LE )
	#define MV_16BIT_LE( X )	( X )
	#define MV_32BIT_LE( X )	( X )
	#define MV_64BIT_LE( X )	( X )
	#define MV_16BIT_BE( X )	MV_BYTE_SWAP_16BIT( X )
	#define MV_32BIT_BE( X )	MV_BYTE_SWAP_32BIT( X )
	#define MV_64BIT_BE( X )	MV_BYTE_SWAP_64BIT( X )
#elif defined( MV_CPU_BE )
	#define MV_16BIT_LE( X )	MV_BYTE_SWAP_16BIT( X )
	#define MV_32BIT_LE( X )	MV_BYTE_SWAP_32BIT( X )
	#define MV_64BIT_LE( X )	MV_BYTE_SWAP_64BIT( X )
	#define MV_16BIT_BE( X )	( X )
	#define MV_32BIT_BE( X )	( X )
	#define MV_64BIT_BE( X )	( X )
#else
	#error "CPU endianess isn't defined!\n"
#endif

#define MV_FALSE				( 0 )
#define MV_TRUE					( !( MV_FALSE ))
typedef unsigned char			MV_U8;
typedef unsigned short			MV_U16;
typedef unsigned long			MV_U32;
typedef long					MV_32;
typedef void					MV_VOID;
typedef long					MV_BOOL;
typedef long					MV_STATUS;

typedef MV_U32 					MV_KHZ;
typedef MV_U32 					MV_MHZ;
typedef MV_U32 					MV_HZ;

typedef enum { BC2_E, AC3_E, BOBK_E, ALDRIN_E} dev_type_ent;

#define MV_BOARD_TCLK           200000000
#define WRITE_FLASH_BUFF_SIZE   0x100           //256 bytes

/* The STM32 and IPC libraries already define the bool type */
/*
#if !defined(CONFIG_STM32) && !defined(CONFIG_MV_IPC_FREERTOS_DRIVER)
typedef long					bool;
#endif*/

#undef FALSE
#define FALSE					( 0 )
#undef TRUE
#define TRUE					( !FALSE )

/* Register access macros */
#define AXPREG( reg )					\
			( *(( volatile unsigned long * )( INTER_REGS_BASE | ( reg ))))
#define AXPREG_BYTE( reg )				\
			( *(( volatile unsigned char * )( INTER_REGS_BASE | ( reg ))))

#define MV_REG_BYTE_WRITE( offset, val )		\
						( AXPREG_BYTE( offset ) = ( val ))
#define MV_REG_BYTE_READ( offset )				\
						( AXPREG_BYTE( offset ))

#define MV_REG_WRITE( offset, val )		\
						( AXPREG( offset ) = ( val ))
#define MV_REG_READ( offset )			\
						( AXPREG( offset ))

#define MV_REG_BIT_SET( reg, bit )		\
						AXPREG( reg ) = AXPREG( reg ) | ( bit )
#define MV_REG_BIT_RESET( reg, bit )	\
						AXPREG( reg ) = AXPREG( reg ) & ~( bit )

/* Basic delay macros */
#define MDELAY( ms )	do {										\
							long j = ( ms );						\
							for ( ; j > 0; j-- )					\
								UDELAY( 1000 );						\
						} while ( 0 )

#define UDELAY( us )	do {											\
							unsigned long i;							\
							i = configCPU_CLOCK_HZ / 4000000 * us;		\
							asm volatile(	"1:		\n\t"				\
											"NOP				\n\t"	\
											"NOP				\n\t"	\
											"SUBS	%0, %0, #1	\n\t"	\
											"BNE	1b			\n\t"	\
											: "+r" ( i ) : );			\
						} while ( 0 )

/* DMA memory allocator */
void *pvPortMallocDMA( size_t xWantedSize, size_t xAlignment, unsigned long ulPTEFlags );

/* PTE handling functions (always built in ARM mode) */
void pte_map_section( unsigned long base_phys, unsigned long base_virt,
		unsigned long size, unsigned long pte_flags );

#define vPTEAddSection( base_virt, base_phys, size, flags )	\
						vPTEMapSection( base_phys, base_virt, size, flags )
#define vPTEDelSection( base_virt, size )		\
						vPTEMapSection( base_virt, base_virt, size, PTE_INVALID )
#define vPTEGetSection( base_virt )				\
		( * (( unsigned long * )( uPageTable + (( base_virt ) >> MMU_SECTION_SHIFT ) * 4 )))
#define vPTESetSection( base_virt, pte_value )	\
		vPTEGetSection( base_virt ) = pte_value

#ifdef THUMB_INTERWORK
void vPTEMapSection( unsigned long base_phys, unsigned long base_virt,
	unsigned long size, unsigned long pte_flags );
#else
#define vPTEMapSection				pte_map_section
#endif

/* Cache maintenance functions (always built in ARM mode) */
unsigned long wbinv_disable_idcache( void );
void enable_idcache( unsigned long mask );
void armv7_dcache_wbinv_range( unsigned long base, unsigned long size);

#ifdef THUMB_INTERWORK
unsigned long cpu_disable_idcache( void );
void cpu_enable_idcache( unsigned long mask );
void cpu_dcache_wbinv_range( unsigned long base, unsigned long size);
#else
#define cpu_disable_idcache()		wbinv_disable_idcache()
#define cpu_enable_idcache( mask )	enable_idcache( mask )
#define cpu_dcache_wbinv_range( base, size )	armv7_dcache_wbinv_range( base, size )
#endif

#endif
#endif
