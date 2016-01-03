/*
 *  psd.h     OS/2 Platform Specific Driver Architecture and Structure.
 *
 *                          Open Watcom Project
 *
 * Based on psd.h from SMP Programming Addendum
 * Copyright (c) 2004-2009 The Open Watcom Contributors. All Rights Reserved.
 *
 * =========================================================================
 */


#include <stdint.h>

#ifndef ulong_t
typedef unsigned long   ulong_t;    // uint32_t
typedef unsigned short  ushort_t;   // uint16_t
typedef unsigned char   uchar_t;    // uint8_t
#endif

typedef int (*P_F_1)(uint32_t arg);
typedef int (*P_F_2)(uint32_t arg1, uint32_t arg2);

#define PSDHelp(router, function, arg) ((*router)((function), (uint32_t)(arg)))


// XLATON

/* ASM

P_F_1 struc
	dd ?
P_F_1 ends

P_F_2 struc
   dd ?
P_F_2 ends

*/

#define WARM_REBOOT_VECTOR_SEG  0x40
#define WARM_REBOOT_VECTOR_OFF  0x67


/* PSD Info structure */
typedef struct info_s {                      /* psd */
   uint32_t  flags;                          /* PSD flags */
   uint32_t  version;                        /* PSD version */
   uint32_t  hmte;                           /* MTE handle of PSD */
   uint8_t   *pParmString;                   /* Pointer to ASCIIZ PSD parameter*/
   uint32_t  IRQ_IPI;                        /* IRQ for IPI */
   uint32_t  IRQ_LSI;                        /* IRQ for LSI */
   uint32_t  IRQ_SPI;                        /* IRQ for SPI */
} PSDINFO;


/* PSD flags definition */
#define PSD_ADV_INT_MODE        0x20000000  /* PSD is in adv int mode #81531 */
#define PSD_INSTALLED           0x40000000  /* PSD has been installed */
#define PSD_INITIALIZED         0x80000000  /* PSD has been initialized */


/* PSD function numbers-structures */
#define PSD_INSTALL             0x00000000  /* Install PSD */


// install structure passed to Install
typedef struct install_s {                  /* install */
   P_F_2    pPSDHlpRouter;                  /* Address of PSDHlpRouter */
   char     *pParmString;                   /* Pointer to parameter string */
   void     *pPSDPLMA;                      /* Pointer to PSD's PLMA */
   uint32_t  sizePLMA;                      /* Size of PLMA in bytes */
} INSTALL;


#define PSD_DEINSTALL           0x00000001  /* DeInstall PSD */
#define PSD_INIT                0x00000002  /* Initialize PSD */


typedef struct init_s {                      /* init */
   uint32_t flags;                           /* Init flags */
   uint32_t version;                         /* PSD Version number */
} INIT;


#define INIT_GLOBAL_IRQ_ACCESS  0x00000001  /* Platform has global IRQ access */
#define INIT_USE_FPERR_TRAP     0x00000002  /* Use Trap 16 to report FP err's */
#define INIT_EOI_IRQ13_ON_CPU0  0x00000004  /* eoi IRQ 13 only if on cpu 0    */
#define INIT_TIMER_CPU0         0x00000008  /* system timer is on CPU 0       */
#define PSD_PROC_INIT           0x00000003  /* Initialize processor */
#define PSD_START_PROC          0x00000004  /* Start processor */
#define PSD_GET_NUM_OF_PROCS    0x00000005  /* Get number of processors */
#define PSD_GEN_IPI             0x00000006  /* Generate an IPI */
#define PSD_END_IPI             0x00000007  /* End an IPI */
#define PSD_PORT_IO             0x00000008  /* Port I/O */


typedef struct port_io_s {                  /* port_io */
   uint32_t port;                           /* Port number to access */
   uint32_t data;                           /* Data read, or data to write */
   uint32_t flags;                          /* IO Flags */
} PORT_IO;


#define IO_READ_BYTE    0x0000              /* Read a byte from the port */
#define IO_READ_WORD    0x0001              /* Read a word from the port */
#define IO_READ_DWORD   0x0002              /* Read a dword from the port */
#define IO_WRITE_BYTE   0x0003              /* Write a byte to the port */
#define IO_WRITE_WORD   0x0004              /* Write a word to the port */
#define IO_WRITE_DWORD  0x0005              /* Write a dword to the port */
#define IO_FLAGMASK     0x0007              /* Flag mask */
#define PSD_IRQ_MASK    0x00000009          /* Mask/Unmask IRQ levels */


typedef struct psd_irq_s {                  /* psd_irq */
   uint32_t flags;                           /* IRQ flags */
   uint32_t data;                            /* IRQ data */
											/* depending on type of irq */
											/* operation, the data field */
											/* can contain any of the */
											/* following info: */
											/*   1) Mask or UNMasking data */
											/*   2) IRR or ISR reg values */
											/*   3) IRQ # for EOI operations   */
	uint32_t   procnum ;                     /* Processor   number   */
}   PSD_IRQ ;


#define PSD_IRQ_REG              0x0000000A    /* Access IRQ related regs */
#define PSD_IRQ_EOI              0x0000000B    /* Issue an EOI */
#define IRQ_MASK                 0x00000001    /* Turn on IRQ   mask   bits   */
#define IRQ_UNMASK               0x00000002    /* Turn off   IRQ   mask   bits   */
#define IRQ_GETMASK              0x00000004    /* Get IRQ   mask   bits   */
#define IRQ_NEWMASK              0x00000010    /* Set and / or   Reset   all   masks   */
#define IRQ_READ_IRR             0x00000100    /* Read the IRR reg   */
#define IRQ_READ_ISR             0x00000200    /* Read the ISR reg */
#define PSD_APP_COMM             0x0000000C    /* PSD/APP Communication */
#define PSD_SET_ADV_INT_MODE     0x0000000D    /* Set advanced int mode */
#define PSD_SET_PROC_STATE       0x0000000E    /* Set proc   state ;   idle ,   or   busy   */
#define PROC_STATE_IDLE          0x00000000    /* Processor is idle   */
#define PROC_STATE_BUSY          0x00000001    /* Processor   is   busy   */
#define PSD_QUERY_SYSTEM_TIMER   0x0000000F    /* Query   Value   of   System   Timer   0   */


typedef struct psd_qrytmr_s   {                /* psd_qrytmr   */
	uint32_t qw_ulLo_psd ;                      /* Timer   count   */
	uint32_t   qw_ulHi_psd ;                    /* Timer   count   */
	uint32_t   pqwTmr ;                         /* 16 : 16   ptr   to   qwTmr   */
} PSD_QRYTMR ;


#define   PSD_SET_SYSTEM_TIMER   0x00000010    /* Set System Timer 0 counter */

typedef   struct   psd_settmr_s   {            /* psd_settmr   */
	uint32_t   NewRollOver ;                    /* NewRollover */
	uint32_t   pqwTmrRollover ;                 /* 16:16 ptr to qwTmrRollover   */
}   PSD_SETTMR ;


// VMALLOC structure used with PSDHLP PSDHLP_VMALLOC function
typedef   struct   vmalloc_s   {   /* vmalloc */
	uint32_t  addr ;                /* Physical address to map if VMALLOC_ PHYS */
								   /* Lin addr to alloc at if VMALLOC_LOCSPECIFIC */
								   /* on return, addr of allocation   */
	uint32_t  cbsize ;              /* Size of mapping in bytes   */
	uint32_t   flags ;              /* Allocation flags */
} VMALLOC ;


typedef   struct   set_irq_s   {                /* set_irq   */
	uint16_t   irq ;                            /* IRQ level   */
	uint16_t   flags ;                          /* Set IRQ   flags   */
	uint32_t   vector ;                         /* IRQ interrupt   vector   */
	P_F_2      handler ;                        /* IRQ handler   */
} SET_IRQ ;


#define  IRQf_IPI    0x0020                     /* IRQ for IPI   */
#define  IRQf_LSI    0x0040                     /* IRQ for LSI   */
#define  IRQf_SPI    0x0080                     /* IRQ for SPI   */

typedef   struct   call_real_mode_s   {         /* call_real_mode   */
	uint32_t   function ;                       /* Function address   */
	uint32_t   pdata ;                          /* Pointer to data area   */
} CALL_REAL_MODE ;


typedef   struct  _pagerange_s   {             /* pagerange   */
	uint32_t   lastframe ;                     /* Last valid page in range   */
	uint32_t   firstframe ;                    /* First valid page in range   */
} ;



typedef struct adj_pg_ranges_s {               /* adj_pg_ranges   */
	struct _pagerange_s   *pprt ;              /* Pointer to page range table   */
	uint32_t nranges ;                         /* Num of ranges in range table   */
}   ADJ_PG_RANGES;


/*   PSD   helper   function   numbers - structures   */
#define   PSDHLP_VMALLOC          0x00000000    /* Allocate   memory   */
#define   VMALLOC_FIXED           0x00000001    /* Allocate resident memory   */
#define   VMALLOC_CONTIG          0x00000002    /* Allocate contiguous memory   */
#define   VMALLOC_LOCSPECIFIC     0x00000004    /* Alloc at a specific lin address   */
#define   VMALLOC_PHYS            0x00000008    /* Map physical address   */
#define   VMALLOC_1M              0x00000010    /* Allocate below 1M   */
#define   VMALLOC_FLAGMASK        0x0000001f    /* Valid flag mask   */
#define   PSDHLP_VMFREE           0x00000001    /* Free memory   */
#define   PSDHLP_SET_IRQ          0x00000002    /* Set up an IRQ   */
#define   PSDHLP_CALL_REAL_MODE   0x00000003    /* Call a function in real mode   */
#define   PSDHLP_VMLINTOPHYS      0x00000004    /* Convert linear addr to phys   */
#define   PSDHLP_ADJ_PG_RANGES    0x00000005    /* Adjust page ranges   */

/* PSD   function   prototypes   */
extern void PSDEnter( uint32_t function, uint32_t arg, P_F_2 altEntry );