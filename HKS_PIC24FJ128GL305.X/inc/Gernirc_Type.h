#ifndef GERNIC_TYPE_H
#define	GERNIC_TYPE_H

#include <xc.h>
/*-----------------------------------------------
   Gerernic type
-----------------------------------------------*/
typedef unsigned char		uint8_t ;
typedef unsigned int		   uint16_t ;
typedef unsigned long		uint32_t ;
typedef unsigned long long	uint64_t ;
typedef char				   int8 ;
typedef int				      int16 ;
typedef long				   int32 ;
typedef long long          int64;
/*-----------------------------------------------
   boolean type
-----------------------------------------------*/
#define True    1
#define False   0

#define High    1 
#define Low     0

#define Enable  1
#define Disable 0

/*-----------------------------------------------
   ptr function
-----------------------------------------------*/
typedef void (*Callback)(void);


#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* TEMPLATE_H */
