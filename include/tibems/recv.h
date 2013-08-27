/* 
 * Copyright 2001-2006 TIBCO Software Inc.
 * All rights reserved.
 * For more information, please contact:
 * TIBCO Software Inc., Palo Alto, California, USA
 * 
 * $Id: recv.h 21731 2006-05-01 21:41:34Z $
 * 
 */

#ifndef _INCLUDED_tibemsqrecv_h
#define _INCLUDED_tibemsqrecv_h

#include "types.h"
#include "status.h"

#if defined(__cplusplus)
extern "C" {
#endif

extern tibems_status
tibemsQueueReceiver_GetQueue(
    tibemsQueueReceiver         queueReceiver,
    tibemsQueue*                queue);

#ifdef  __cplusplus
}
#endif

#endif /* _INCLUDED_tibemsqrecv_h */
