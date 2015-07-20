#ifndef __USB_HID_H__
#define __USB_HID_H__
/**
* @addtogroup USB_HID
* @brief CIAA HID driver
*
* @{ */

#include <stdint.h>

#include "usb.h"


#define	HID_MAX_DEVICES  1


typedef enum _hid_protocol_t
{
	HID_PROTO_NONE  = 0,
	HID_PROTO_KEYB  = 1,
	HID_PROTO_MOUSE = 2,
} hid_protocol_t;

typedef enum _hid_desc_type_t
{
	HID_DESC_TYPE_HID      = 0x21,
	HID_DESC_TYPE_REPORT   = 0x22,
	HID_DESC_TYPE_PHYSICAL = 0x23
} hid_desc_type_t;

typedef enum _hid_dev_state_t
{
	HID_STATE_IDLE,
	HID_STATE_SET_IDLE,
	HID_STATE_INIT,
	HID_STATE_INIT2,
	HID_STATE_RUNNING,
} hid_state_t;

typedef struct _hid_desc_hid_t
{
	uint8_t  bLength;              /**< Total size of HID descriptor.        */
	uint8_t  bDescriptorType;      /**< Type of HID descriptor.              */
	uint16_t bcdHID;               /**< HID Class specification release.     */
	uint8_t  bCountryCode;         /**< Country code, see _hid_ctrycode_t.   */
	uint8_t  bNumDescriptors;      /**< Number of class descriptors.         */
	uint8_t  bClassDescriptorType; /**< Type of class descriptor.            */
	uint16_t wDescriptorLength;    /**< Total size of the Report descriptor. */
	/* Optional descriptors type/length pairs start from here onwards. */
} __attribute__ ((__packed__)) hid_desc_hid_t;
#define HID_DESC_HID_SIZE  9
enum
{
	HID_REQ_GET_REPORT   = 0x01,  /* Mandatory! */
	HID_REQ_GET_IDLE     = 0x02,
	HID_REQ_GET_PROTOCOL = 0x03,
	HID_REQ_SET_REPORT   = 0x09,
	HID_REQ_SET_IDLE     = 0x0A,
	HID_REQ_SET_PROTOCOL = 0x0B,
};

/** @brief Country code of localized hardware. */
typedef enum _hid_ctrycode_t
{
	HID_CTRYCODE_NOT_SUPPORTED       =  0,
	HID_CTRYCODE_ARABIC              =  1,
	HID_CTRYCODE_BELGIAN             =  2,
	HID_CTRYCODE_CANADIAN_BILINGUAL  =  3,
	HID_CTRYCODE_CANADIAN_FRENCH     =  4,
	HID_CTRYCODE_CZECH_REPUBLIC      =  5,
	HID_CTRYCODE_DANISH              =  6,
	HID_CTRYCODE_FINNISH             =  7,
	HID_CTRYCODE_FRENCH              =  8,
	HID_CTRYCODE_GERMAN              =  9,
	HID_CTRYCODE_GREEK               = 10,
	HID_CTRYCODE_HEBREW              = 11,
	HID_CTRYCODE_HUNGARY             = 12,
	HID_CTRYCODE_INTERNATIONAL_ISO   = 13,
	HID_CTRYCODE_ITALIAN             = 14,
	HID_CTRYCODE_JAPAN_KATAKANA      = 15,
	HID_CTRYCODE_KOREAN              = 16,
	HID_CTRYCODE_LATIN_AMERICAN      = 17,
	HID_CTRYCODE_NETHERLANDS_DUTCH   = 18,
	HID_CTRYCODE_NORWEGIAN           = 19,
	HID_CTRYCODE_PERSIAN_FARSI       = 20,
	HID_CTRYCODE_POLAND              = 21,
	HID_CTRYCODE_PORTUGUESE          = 22,
	HID_CTRYCODE_RUSSIA              = 23,
	HID_CTRYCODE_SLOVAKIA            = 24,
	HID_CTRYCODE_SPANISH             = 25,
	HID_CTRYCODE_SWEDISH             = 26,
	HID_CTRYCODE_SWISS_FRENCH        = 27,
	HID_CTRYCODE_SWISS_GERMAN        = 28,
	HID_CTRYCODE_SWITZERLAND         = 29,
	HID_CTRYCODE_TAIWAN              = 30,
	HID_CTRYCODE_TURKISH_Q           = 31,
	HID_CTRYCODE_UK                  = 32,
	HID_CTRYCODE_US                  = 33,
	HID_CTRYCODE_YUGOSLAVIA          = 34,
	HID_CTRYCODE_TURKISH_F           = 35
} hid_ctrycode_t;


typedef struct _hid_dev_t
{
	hid_state_t    state;      /**< Device's state.                           */
	uint32_t       status;     /**< Object's status, see constant definitions.*/
	usb_stack_t*   pstack;     /**< USB stack the device belongs to.          */
	uint16_t       id;         /**< Device's ID within the USB stack.         */
	hid_protocol_t protocol;   /**< Device's protocol.                        */
	hid_ctrycode_t ctry_code;  /**< Country code.                             */
	uint8_t        report[256];/**< Report's buffer, capped at 256 bytes.     */
	uint8_t        report_len; /**< Report's length, capped at 256 bytes.     */
} hid_dev_t;

typedef struct _hid_stack_t
{
	hid_dev_t devices[HID_MAX_DEVICES];
	uint8_t   n_devices;
} hid_stack_t;

/** @brief Whether object is free or currently in use. */
#define	HID_STATUS_FREE    (1 << 0)
/** @brief Whether device has already been initialized. */
#define	HID_STATUS_INIT    (1 << 1)
/** @brief Whether device has been opened by user code. */
#define	HID_STATUS_OPEN    (1 << 2)
/** @brief Whether device uses an extra interrupt OUT endpoint for control. */
#define	HID_STATUS_INTOUT  (1 << 3)
/**< Whether entry actions are to be exec'ed.  */
#define HID_STATUS_ENTRY   (1 << 4)


/**
 * @brief Driver registration probing function.
 */
int hid_probe( const uint8_t* buffer, uint8_t len );
/**
 * @brief Driver registration assignment function.
 */
int hid_assign(
		usb_stack_t*   pstack,
		uint16_t       id,
		const uint8_t* buffer,
		uint8_t        length
);
/**
 * @brief Driver registration removal function.
 */
int hid_remove( usb_stack_t* pstack, uint16_t id );


/******************************************************************************/

int hid_init( void );

int hid_dev_deinit( uint8_t index );

int hid_get_free_dev( void );

int hid_update( void );

int hid_update_device( uint8_t index );

int hid_open_dev( const char* str_num, int flags, hid_protocol_t protocol );


/* POSIX */
/**
 * @FIXME the following POSIX interface is beign  thrown  together  for  testing
 * purposes at the moment.
 */

int hid_open(const char *pathname, int flags);

int hid_close(int fd);

size_t hid_read(int fd, void *buf, size_t count);

int hid_write(int fd, const void *buf, size_t count);


/**  @} USB_HID */
#endif /* __USB_HID_H__ */
