/****************************************************************************/
/*                                                                          */
/*   Softing GmbH          Richard-Reitzner-Allee 6       85540 Haar        */
/*                                                                          */
/****************************************************************************/
/*                                                                          */
/*   Copyright (C) by Softing GmbH, 1998, All rights reserved.              */
/*                                                                          */
/****************************************************************************/
/*                                                                          */
/*                               C A N . H                                                                      */
/*                                                                          */
/****************************************************************************/
/*                                                                          */
/* MODULE_DESCRIPTION  CAN.H                                                                                            */
/* VERSION             4.02                                                 */
/* DATE                11.09.98                                             */
/*                     include file for CAN Layer 2 Library                 */
/*                     function prototypes and return codes                 */
/*                     predefined for explicit linking                      */
/*                                                                                                                       */
/****************************************************************************/

// Defines and declaration for linking routine
#define ERROR_LINKING_DLL                                       -1
#define ERROR_LINKING_FCT                                       -2
#define LINK_CAN_API_OK                                         0
int LinkCanAPI(void);

// Defines for application
#define  CANPC_SOCKET_AUTO   0xFFFF    /* Socket automatically searched     */
#define  CANPC_NO_IRQ        0x0       /* no interrupt requested            */
#define  CANPC_IRQ_AUTO      0xFFFF    /* interrupt automatically assigned  */
#define  CANPC_BASE_AUTO     0x0L      /* DPR-Base automatically assigned   */
#define  CANPC_SIZE_AUTO     0x0L      /* DPR-Size automatically assigned   */
#define  CANPC_AI_AUTO       0x0       /* chip does no matter               */
#define  CANPC_AI_DB8        0x01      /* chip is Databook                  */

#define         Mbit1   0
#define         kbit500 1
#define         kbit250 2
#define         kbit125 3
#define         kbit100 4
#define         kbit50  5

#define         FIFO_MODE       0
#define         DOB_MODE        1
#define         SOB_MODE        2


typedef enum ChipTypeEnum
{   _82365SL_,
    _DB86082_
}  ChipType;

#pragma pack(1)                        /* pack alignment must be one        */

typedef struct canpc_ressources_s {
    unsigned short uSocket;
    unsigned short uInterrupt;
    unsigned long  ulDPRMemBase;
    unsigned long  ulDPRMemSize;
    ChipType       uChip;
    unsigned short uIOAdress;
    unsigned short uRegisterBase;
} CANPC_RESSOURCES;


typedef struct  {
                  unsigned long Ident;
                  int  DataLength;
                  int  RecOverrun_flag;
                  int  RCV_fifo_lost_msg;
         unsigned char  RCV_data[8];
                  int  AckOverrun_flag;
                  int  XMT_ack_fifo_lost_acks;
                  int  XMT_rmt_fifo_lost_remotes;
                  int  Bus_state;
                  int  Error_state;
                  int  Can;
         unsigned long  Time;
                } param_struct;


/* ---- FUNCTION TYPE DEFINITION  -----------------------------------------*/
typedef int (CALLBACK* CANPC_VOID_TYPE) (void);
typedef int (CALLBACK* INIPC_INIT_BOARD_TYPE) (CANPC_RESSOURCES*);
typedef int (CALLBACK* CANPC_GET_VERSION_TYPE) (int*, int*, int*, int*, int*);
typedef int (CALLBACK* CANPC_GET_SERIAL_NUMBER_TYPE) (unsigned long FAR *);

typedef int (CALLBACK* CANPC_INIT_CHIP_TYPE) (int, int, int, int, int);
typedef int (CALLBACK* CANPC_SET_MODE_TYPE) (int, int);
typedef int (CALLBACK* CANPC_SET_ACCEPTANCE_TYPE) (unsigned int, unsigned int, unsigned long, unsigned long);
typedef int (CALLBACK* CANPC_SET_OUTPUT_CONTROL_TYPE) (int);

typedef int (CALLBACK* CANPC_READ_AC_TYPE) (param_struct*);
typedef int (CALLBACK* CANPC_SEND_DATA_TYPE) (unsigned long, int, int , unsigned char*);
typedef int (CALLBACK* CANPC_SEND_REMOTE_TYPE) (unsigned long, int, int);

typedef int (CALLBACK* CANPC_INIT_INTERFACE_TYPE) (int, int, int, int, int, int, int, int, int, int);
typedef int (CALLBACK* CANPC_DEFINE_OBJECT_TYPE) (unsigned long, int*, int, int, int, int);
typedef int (CALLBACK* CANPC_DEFINE_CYCLIC_TYPE) (int, unsigned int, unsigned int);
typedef int (CALLBACK* CANPC_SUPPLY_OBJECT_DATA_TYPE) (int, int, unsigned char*);
typedef int (CALLBACK* CANPC_SUPPLY_RCV_OBJECT_DATA_TYPE) (int, int, unsigned char*);
typedef int (CALLBACK* CANPC_READ_RCV_DATA_TYPE) (unsigned long, unsigned char*,unsigned long*);
typedef int (CALLBACK* CANPC_READ_XMT_DATA_TYPE) (int, int*,unsigned char*);
typedef int (CALLBACK* CANPC_SEND_OBJECT_TYPE) (int, int);
typedef int (CALLBACK* CANPC_SEND_REMOTE_OBJECT_TYPE) (int, int);
typedef int (CALLBACK* CANPC_WRITE_OBJECT_TYPE) (unsigned long, int, unsigned char*);

typedef int (CALLBACK* CANPC_GET_TIME_TYPE) (unsigned long*);
typedef int (CALLBACK* CANPC_GET_BUS_STATE_TYPE) (int);
typedef int (CALLBACK* CANPC_SET_TRIGGER_TYPE) (int);
typedef int (CALLBACK* CANPC_SET_INTERRUPT_EVENT_TYPE) (void*);


/* ---- FUNCTION DECLARATION AND FUNCTION RETURN VALUES  --------------------*/
/* default return values -- valid for all functions                         */
#define  CANPC_OK                          0  /*  function successful       */
#define  CANPC_ACCESS_TIMEOUT             -4  /* timeout accessing dpram of 
                                                 CAN adapter                */

/* ---- INIPC_initialize_board   -------------------------------------------*/
extern INIPC_INIT_BOARD_TYPE   INIPC_initialize_board;

/* --  return codes for card services access with WINDOWS 3.11              */
#define  INIPC_IB_ERR_WINSYSRES       0xFFFF  /* not enough windows system 
                                                 resources                  */

/* --  return codes for card services access with DOS or WINDOWS 3.11       */

/* return values between 0x0201 and 0x3622: card services call failed       */

#define  INIPC_IB_ERR_NO_CARD_FOUND   0xFFEF  /* no pcmcia card found       */
#define  INIPC_IB_ERR_NO_CS_INSTALLED 0xFFEE  /* no card services installed */
#define  INIPC_IB_ERR_WRONG_VERSION   0xFFED  /* card services version not
                                                 supported                  */
#define  INIPC_IB_ERR_IRQ             0xFFEC  /* interrupt number invalid 
                                                 or in use                  */
#define  INIPC_IB_ERR_DPRAM           0xFFEB  /* failed allocating dpr-window: 
                                                 out of resources or in use */                           
#define  INIPC_IB_ERR_ACCESS_DPRAM    0xFFEA  /* DOS: invalid dpram address 
                                                      (above 1MB) 
                                                 WIN: failed allocating
                                                      selector              */

/* --  return codes for access with WIN32 (WINDOWS-NT 4.0 and WINDOWS 95)   */
/* return values between 0xFE0201 and 0x3622: card services call failed     */
#define  INIPC_IB_PNP_NO_DEVICE_FOUND  0xFE00 /* no can device found        */
#define  INIPC_IB_ERR_VC_INTERNALERROR 0xFE01 /* internal error             */
#define  INIPC_IB_ERR_VC_GENERALERROR  0xFE02 /* general error              */
#define  INIPC_IB_ERR_VC_TIMEOUT       0xFE03 /* Timeout                    */
#define  INIPC_IB_ERR_VC_IOPENDING     0xFE04 /* driver call pending        */
#define  INIPC_IB_ERR_VC_IOCANCELLED   0xFE05 /* driver call cancelled      */
#define  INIPC_IB_ERR_VC_ILLEGALCALL   0xFE06 /* illegal driver call        */
#define  INIPC_IB_ERR_VC_NOTSUPPORTED  0xFE07 /* driver call not supported  */
#define  INIPC_IB_ERR_VC_VERSIONERROR  0xFE08 /* wrong driver-dll version   */
#define  INIPC_IB_ERR_VC_DRIVERVERSIONERROR   0xFE09 /*wrong driver version */
#define  INIPC_IB_ERR_VC_DRIVERNOTFOUND   0xFE0A /* driver not found        */
#define  INIPC_IB_ERR_VC_NOTENOUGHMEMORY  0xFE0B /* not enough memory       */
#define  INIPC_IB_ERR_VC_TOOMANYDEVICES   0xFE0C /* too many devices        */
#define  INIPC_IB_ERR_VC_UNKNOWNDEVICE    0xFE0D /* unknown device          */
#define  INIPC_IB_ERR_VC_DEVICEALREADYEXISTS 0xFE0E /* Device ardy exists   */
#define  INIPC_IB_ERR_VC_DEVICEACCESSERROR   0xFE0F /* device ardy open     */
#define  INIPC_IB_ERR_VC_RESOURCEALREADYREGISTERED 0xFE10 /* Resource in use*/
#define  INIPC_IB_ERR_VC_RESOURCECONFLICT 0xFE11 /* Resource-conflict       */
#define  INIPC_IB_ERR_VC_RESOURCEACCESSERROR 0xFE12 /* Resource access error*/
#define  INIPC_IB_ERR_VC_PHYSMEMORYOVERRUN 0xFE13 /* invalid phys.mem-access*/
#define  INIPC_IB_ERR_VC_TOOMANYPORTS    0xFE14     /* too many I/O ports   */
#define  INIPC_IB_ERR_VC_UNKNOWNRESOURCE  0xFE15 /* unknown resource        */


/* +--- CANPC_reset_board        -------------------------------------------*/
extern CANPC_VOID_TYPE         CANPC_reset_board;
/* -- return values for access with DOS only                                */
#define  CANPC_RB_INI_FILE           -1  /* can't open IniFile              */              
#define  CANPC_RB_ERR_FMT_INI        -2  /* format error in INI-file        */    
#define  CANPC_RB_ERR_OP_BIN         -3  /* error opening binary-file       */    
#define  CANPC_RB_ERR_RD_BIN         -4  /* error reading binary-file       */    
#define  CANPC_RB_BIN_TOO_LONG       -5  /* binary-file too long            */    

/* -- return values for access with DOS and WINDOWS (WIN16, WIN32)          */
#define  CANPC_RB_ERR_BIN_FMT        -6  /* binary-data format error        */    
#define  CANPC_RB_ERR_BIN_CS         -7  /* binary-data checksum error      */    
#define  CANPC_RB_NO_CARD           -16  /* no card present                 */    
#define  CANPC_RB_NO_PHYS_MEM       -17  /* no physical memory              */    
#define  CANPC_RB_INVLD_IRQ         -18  /* invalid IRQ-number              */    
#define  CANPC_RB_ERR_DPRAM_ACCESS  -19  /* error accessing dpram           */    
#define  CANPC_RB_ERR_CRD_RESP      -20  /* bad response from card          */    
#define  CANPC_RB_ERR_SRAM          -21  /* sram seems to be damaged        */    
#define  CANPC_RB_ERR_PRG           -22  /* invalid program start address   */    
#define  CANPC_RB_ERR_REC           -23  /* invalid record type             */    
#define  CANPC_RB_ERR_NORESP        -24  /* no response after program start */    
#define  CANPC_RB_ERR_BADRESP       -25  /* bad response after program start*/    
#define  CANPC_RB_PCMCIA_NSUPP      -26  /* pcmcia chip not supported       */    
#define  CANPC_RB_ERR_RD_PCMCIA     -27  /* error reading ocmcia parameters */    
#define  CANPC_RB_INIT_CHIP         -38  /* error initializing chip         */    


/* +--- CANPC_reset_chip         -------------------------------------------*/
extern CANPC_VOID_TYPE         CANPC_reset_chip;

/* +--- CANPC_initialize_chip(2) -------------------------------------------*/
extern CANPC_INIT_CHIP_TYPE CANPC_initialize_chip;
extern CANPC_INIT_CHIP_TYPE CANPC_initialize_chip2;

/* +--- CANPC_set_mode(2)        -------------------------------------------*/
extern CANPC_SET_MODE_TYPE CANPC_set_mode;
extern CANPC_SET_MODE_TYPE CANPC_set_mode2;

/* +--- CANPC_set_acceptance(2)  -------------------------------------------*/
extern CANPC_SET_ACCEPTANCE_TYPE CANPC_set_acceptance;
extern CANPC_SET_ACCEPTANCE_TYPE CANPC_set_acceptance2;

/* +--- CANPC_set_output_control(2)  ---------------------------------------*/
extern CANPC_SET_OUTPUT_CONTROL_TYPE CANPC_set_output_control;
extern CANPC_SET_OUTPUT_CONTROL_TYPE CANPC_set_output_control2;

/* +--- CANPC_initialize_interface   ---------------------------------------*/
extern CANPC_INIT_INTERFACE_TYPE CANPC_initialize_interface;
#define  CANPC_II_REA_CONFLICT            -6  /* Parameter conflict: 
                                                 ReceiveEnableAll with dyn.
                                                 obj. buffer or fifo mode   */


/* +--- CANPC_define_object(2)          ------------------------------------*/
#define  CANPC_DO_PARAM_ERR               -1  /* Parameter error            */
#define  CANPC_DO_NO_DYNOBJ               -2  /* dyn. obj. buf. not enabled 
                                             (only CANPC_define_object2) */
#define  CANPC_DO_TOO_MANY_OBJECTS        -6  /* too many objects defined   */

extern CANPC_DEFINE_OBJECT_TYPE         CANPC_define_object;
extern CANPC_DEFINE_OBJECT_TYPE         CANPC_define_object2;


/* +--- CANPC_define_cyclic(2)        --------------------------------------*/
#define  CANPC_DC_INVLD_OBJ_NR            -1  /* invalid object number      */

extern CANPC_DEFINE_CYCLIC_TYPE         CANPC_define_cyclic;
extern CANPC_DEFINE_CYCLIC_TYPE         CANPC_define_cyclic2;


/* +--- CANPC_enable_fifo            ---------------------------------------*/
extern CANPC_VOID_TYPE CANPC_enable_fifo;


/* +--- CANPC_optimize_rcv_speed     ---------------------------------------*/
extern CANPC_VOID_TYPE                                  CANPC_optimize_rcv_speed;


/* +--- CANPC_enable_dyn_obj_buf     ---------------------------------------*/
extern CANPC_VOID_TYPE                                  CANPC_enable_dyn_obj_buf;


/* +--- CANPC_enable_timestamps      ---------------------------------------*/
extern CANPC_VOID_TYPE                                  CANPC_enable_timestamps;


/* +--- CANPC_enable_fifo_transmit_ack  ------------------------------------*/
extern CANPC_VOID_TYPE CANPC_enable_fifo_transmit_ack ;
extern CANPC_VOID_TYPE CANPC_enable_fifo_transmit_ack2;


/* +--- CANPC_get_version            ---------------------------------------*/
extern CANPC_GET_VERSION_TYPE                                   CANPC_get_version;


/* +--- CANPC_get_serial_number      ---------------------------------------*/
extern CANPC_GET_SERIAL_NUMBER_TYPE                     CANPC_get_serial_number;


/* +--- CANPC_start_chip             ---------------------------------------*/
extern CANPC_VOID_TYPE   CANPC_start_chip;


/* +--- CANPC_send_remote_object(2)  ---------------------------------------*/
#define  CANPC_SRO_PEND                   -1  /* last request still pending */    
#define  CANPC_SRO_TX_FIFO_FULL           -3  /* transmit fifo full         */    

extern CANPC_SEND_REMOTE_OBJECT_TYPE    CANPC_send_remote_object;
extern CANPC_SEND_REMOTE_OBJECT_TYPE    CANPC_send_remote_object2
;

/* +--- CANPC_supply_object_data(2)  ---------------------------------------*/
#define  CANPC_SOD_REQ_OVR                -1  /* request overrun            */    

extern CANPC_SUPPLY_OBJECT_DATA_TYPE    CANPC_supply_object_data;
extern CANPC_SUPPLY_OBJECT_DATA_TYPE    CANPC_supply_object_data2;


/* +--- CANPC_supply_rcv_object_data(2)-------------------------------------*/

extern CANPC_SUPPLY_RCV_OBJECT_DATA_TYPE        CANPC_supply_rcv_object_data;
extern CANPC_SUPPLY_RCV_OBJECT_DATA_TYPE        CANPC_supply_rcv_object_data2;


/* +--- CANPC_send_object(2)         ---------------------------------------*/
#define  CANPC_SO_REQ_OVR                 -1  /* request overrun            */    
#define  CANPC_SO_FIFO_FULL               -3  /* job fifo full              */    

extern CANPC_SEND_OBJECT_TYPE   CANPC_send_object;
extern CANPC_SEND_OBJECT_TYPE   CANPC_send_object2;


/* +--- CANPC_write_object(2)        ---------------------------------------*/
#define  CANPC_WO_REQ_OVR                 -1  /* request overrun            */    
#define  CANPC_WO_FIFO_FULL               -3  /* transmit fifo full         */    

extern CANPC_WRITE_OBJECT_TYPE CANPC_write_object;
extern CANPC_WRITE_OBJECT_TYPE CANPC_write_object2;


/* +--- CANPC_read_rcv_data(2)       ---------------------------------------*/
#define  CANPC_RRD_NO_DATA                 0  /* no new data received       */    
#define  CANPC_RRD_DATAFRAME               1  /* data frame received        */    
#define  CANPC_RRD_REMOTEFRAME             2  /* remote frame received      */    
#define  CANPC_RRD_RCV_OVR                -1  /* receive data overrun       */    
#define  CANPC_RRD_RF_OVR                 -2  /* rec. rem. frame overrun    */    
#define  CANPC_RRD_OBJ_INACTIVE           -3  /* object not active          */    

extern CANPC_READ_RCV_DATA_TYPE CANPC_read_rcv_data;
extern CANPC_READ_RCV_DATA_TYPE CANPC_read_rcv_data2;


/* +--- CANPC_read_xmt_data(2)       ---------------------------------------*/
#define  CANPC_RXD_NO_DATA                 0  /* no message was transmitted */    
#define  CANPC_RXD_DATAFRAME               1  /* message was transmitted    */    

extern CANPC_READ_XMT_DATA_TYPE CANPC_read_xmt_data;
extern CANPC_READ_XMT_DATA_TYPE CANPC_read_xmt_data2;


/* +--- CANPC_read_ac                ---------------------------------------*/
extern CANPC_READ_AC_TYPE CANPC_read_ac;

#define  CANPC_RA_NO_DATA                 0  /* no new data received        */    
#define  CANPC_RA_DATAFRAME               1  /* std. data frame received    */    
#define  CANPC_RA_REMOTEFRAME             2  /* std. remote frame received  */    
#define  CANPC_RA_TX_DATAFRAME            3  /* transmission of std. data-
                                                frame is confirmed          */    
#define  CANPC_RA_TX_FIFO_OVR             4  /* remote tx fifo overrun      */    
#define  CANPC_RA_CHG_BUS_STATE           5  /* change of bus status        */    
#define  CANPC_RA_ERR_ADD                 7  /* additional error causes     */    
#define  CANPC_RA_TX_REMOTEFRAME          8  /* transmission of std. data-
                                                frame is confirmed          */    
#define  CANPC_RA_XTD_DATAFRAME           9  /* xtd. data frame received    */    
#define  CANPC_RA_XTD_TX_DATAFRAME       10  /* transmission of xtd. data-
                                                frame is confirmed          */    
#define  CANPC_RA_XTD_TX_REMOTEFRAME     11  /* transmission of xtd. remote-
                                                frame is confirmed          */    
#define  CANPC_RA_XTD_REMOTEFRAME        12  /* xtd. remote frame received  */    

#define  CANPC_RA_ERRORFRAME             15  /* error frame detected        */    


/* +--- CANPC_send_data              ---------------------------------------*/
#define  CANPC_SD_FIFO_FULL               -1  /* transmit fifo full         */    

extern CANPC_SEND_DATA_TYPE CANPC_send_data;
extern CANPC_SEND_DATA_TYPE CANPC_send_data2;


/* +--- CANPC_send_remote            ---------------------------------------*/
#define  CANPC_SR_FIFO_FULL               -1  /* transmit fifo full         */    
extern CANPC_SEND_REMOTE_TYPE   CANPC_send_remote;
extern CANPC_SEND_REMOTE_TYPE   CANPC_send_remote2;


/* +--- CANPC_reinitialize           ---------------------------------------*/
extern CANPC_VOID_TYPE  CANPC_reinitialize;


/* +--- CANPC_get_time               ---------------------------------------*/
extern CANPC_GET_TIME_TYPE      CANPC_get_time;


/* +--- CANPC_get_bus_state          ---------------------------------------*/
#define  CANPC_GBS_ERROR_ACTIVE            0  /* error active               */    
#define  CANPC_GBS_ERROR_PASSIVE           1  /* error passive              */    
#define  CANPC_GBS_ERROR_BUS_OFF           2  /* bus off                    */    

extern CANPC_GET_BUS_STATE_TYPE CANPC_get_bus_state;


/* +--- CANPC_reset_rcv_fifo         ---------------------------------------*/
extern CANPC_VOID_TYPE  CANPC_reset_rcv_fifo;

/* +--- CANPC_reset_xmt_fifo         ---------------------------------------*/
extern CANPC_VOID_TYPE  CANPC_reset_xmt_fifo;

/* +--- CANPC_reset_lost_msg_counter  --------------------------------------*/
extern CANPC_VOID_TYPE  CANPC_reset_lost_msg_counter;

/* +--- extern CANPC_read_rcv_fifo_level    ---------------------------------------*/
/* returns number of items in receive fifo   */
extern CANPC_VOID_TYPE  CANPC_read_rcv_fifo_level;

/* +--- CANPC_read_xmt_fifo_level    ---------------------------------------*/
/* returns number of items in transmit fifo  */
extern CANPC_VOID_TYPE  CANPC_read_xmt_fifo_level;

/* +--- INIPC_close_board            ---------------------------------------*/
extern CANPC_VOID_TYPE INIPC_close_board;
#define  INIPC_CB_ERR                     -1  /* error unlocking rerssources*/    

/* +--- CANPC_enable_error_frame_detection  --------------------------------*/
extern CANPC_VOID_TYPE  CANPC_enable_error_frame_detection;

/* +--- CANPC_set_trigger  --------------------------------*/
extern CANPC_SET_TRIGGER_TYPE   CANPC_set_trigger;
extern CANPC_SET_TRIGGER_TYPE   CANPC_set_trigger2;

extern CANPC_SET_INTERRUPT_EVENT_TYPE CANPC_set_interrupt_event;


struct st_canlay2lib {
INIPC_INIT_BOARD_TYPE   INIPC_initialize_board;
CANPC_VOID_TYPE         CANPC_reset_board;
CANPC_VOID_TYPE         CANPC_reset_chip;
CANPC_INIT_CHIP_TYPE CANPC_initialize_chip;
CANPC_INIT_CHIP_TYPE CANPC_initialize_chip2;
CANPC_SET_MODE_TYPE CANPC_set_mode;
CANPC_SET_MODE_TYPE CANPC_set_mode2;
CANPC_SET_ACCEPTANCE_TYPE CANPC_set_acceptance;
CANPC_SET_ACCEPTANCE_TYPE CANPC_set_acceptance2;
CANPC_SET_OUTPUT_CONTROL_TYPE CANPC_set_output_control;
CANPC_SET_OUTPUT_CONTROL_TYPE CANPC_set_output_control2;
CANPC_INIT_INTERFACE_TYPE CANPC_initialize_interface;
CANPC_DEFINE_OBJECT_TYPE                CANPC_define_object;
CANPC_DEFINE_OBJECT_TYPE                CANPC_define_object2;
CANPC_DEFINE_CYCLIC_TYPE                CANPC_define_cyclic;
CANPC_DEFINE_CYCLIC_TYPE                CANPC_define_cyclic2;
CANPC_VOID_TYPE CANPC_enable_fifo;
CANPC_VOID_TYPE                                 CANPC_optimize_rcv_speed;
CANPC_VOID_TYPE                                 CANPC_enable_dyn_obj_buf;
CANPC_VOID_TYPE                                 CANPC_enable_timestamps;
CANPC_VOID_TYPE CANPC_enable_fifo_transmit_ack ;
CANPC_VOID_TYPE CANPC_enable_fifo_transmit_ack2;
CANPC_GET_VERSION_TYPE                                  CANPC_get_version;
CANPC_GET_SERIAL_NUMBER_TYPE                    CANPC_get_serial_number;
CANPC_VOID_TYPE  CANPC_start_chip;
CANPC_SEND_REMOTE_OBJECT_TYPE   CANPC_send_remote_object;
CANPC_SEND_REMOTE_OBJECT_TYPE   CANPC_send_remote_object2;
CANPC_SUPPLY_OBJECT_DATA_TYPE   CANPC_supply_object_data;
CANPC_SUPPLY_OBJECT_DATA_TYPE   CANPC_supply_object_data2;
CANPC_SUPPLY_RCV_OBJECT_DATA_TYPE       CANPC_supply_rcv_object_data;
CANPC_SUPPLY_RCV_OBJECT_DATA_TYPE       CANPC_supply_rcv_object_data2;
CANPC_SEND_OBJECT_TYPE  CANPC_send_object;
CANPC_SEND_OBJECT_TYPE  CANPC_send_object2;
CANPC_WRITE_OBJECT_TYPE CANPC_write_object;
CANPC_WRITE_OBJECT_TYPE CANPC_write_object2;
CANPC_READ_RCV_DATA_TYPE CANPC_read_rcv_data;
CANPC_READ_RCV_DATA_TYPE CANPC_read_rcv_data2;
CANPC_READ_XMT_DATA_TYPE        CANPC_read_xmt_data;
CANPC_READ_XMT_DATA_TYPE        CANPC_read_xmt_data2;
CANPC_READ_AC_TYPE CANPC_read_ac;
CANPC_SEND_DATA_TYPE CANPC_send_data;
CANPC_SEND_DATA_TYPE CANPC_send_data2;
CANPC_SEND_REMOTE_TYPE  CANPC_send_remote;
CANPC_SEND_REMOTE_TYPE  CANPC_send_remote2;
CANPC_VOID_TYPE CANPC_reinitialize;
CANPC_GET_TIME_TYPE     CANPC_get_time;
CANPC_GET_BUS_STATE_TYPE        CANPC_get_bus_state;
CANPC_VOID_TYPE CANPC_reset_rcv_fifo;
CANPC_VOID_TYPE CANPC_reset_xmt_fifo;
CANPC_VOID_TYPE CANPC_reset_lost_msg_counter;
CANPC_VOID_TYPE CANPC_read_rcv_fifo_level;
CANPC_VOID_TYPE CANPC_read_xmt_fifo_level;
CANPC_VOID_TYPE CANPC_enable_error_frame_detection;
CANPC_SET_TRIGGER_TYPE  CANPC_set_trigger;
CANPC_SET_TRIGGER_TYPE  CANPC_set_trigger2;
CANPC_SET_INTERRUPT_EVENT_TYPE CANPC_set_interrupt_event;
CANPC_VOID_TYPE         INIPC_close_board;
};



/*_CANLAY2_H */



