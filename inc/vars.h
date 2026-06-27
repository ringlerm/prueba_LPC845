
#ifndef UTILS_H_
#define UTILS_H_

#define __I    				volatile const  //!< Defines 'read only' permission
#define __O    				volatile        //!< Defines 'write only' permission
#define __IO   				volatile        //!< Defines 'read / write' permission

typedef	unsigned char 		uint8_t;
typedef	signed char			int8_t;
typedef	short unsigned int 	uint16_t;
typedef	short int 			int16_t;
typedef	unsigned long int	uint32_t;
typedef	long int			int32_t;

#ifndef INT32_MAX
#define	INT32_MAX			(2147483647) 	//!< Maximum value of the INT32 variable type.
#endif
#ifndef INT32_MIN
#define	INT32_MIN			(-2147483648) 	//!< Minimum value of the INT32 variable type.
#endif
#ifndef UINT32_MAX
#define	UINT32_MAX			(4294967295) 	//!< Maximum value of the UINT32 variable type.
#endif

#ifndef INT16_MAX
#define	INT16_MAX			(32767) 		//!< Maximum value of the INT16 variable type.
#endif
#ifndef INT16_MIN
#define	INT16_MIN			(-32768) 		//!< Minimum value of the INT16 variable type.
#endif
#ifndef UINT16_MAX
#define	UINT16_MAX			(65535) 		//!< Maximum value of the UINT16 variable type.
#endif

#ifndef INT8_MAX
#define	INT8_MAX			(127)			//!< Maximum value of the INT8 variable type.
#endif
#ifndef INT8_MIN
#define	INT8_MIN			(-128)			//!< Minimum value of the INT8 variable type.
#endif
#ifndef UINT8_MAX
#define	UINT8_MAX			(255)			//!< Maximum value of the UINT8 variable type.
#endif

#define BYTE_SIZE			8
#define REG_BYTES_SIZE		32 // BYTE_SIZE * 4

#endif /* UTILS_H_ */
