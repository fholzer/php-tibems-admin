/* 
 * Copyright 2001-2006 TIBCO Software Inc.
 * All rights reserved.
 * For more information, please contact:
 * TIBCO Software Inc., Palo Alto, California, USA
 * 
 * $Id: msgreq.h 23259 2006-10-05 20:25:47Z $
 * 
 */

#ifndef _INCLUDED_tibemsmsgreq_h
#define _INCLUDED_tibemsmsgreq_h

#include "types.h"
#include "status.h"

#if defined(__cplusplus)
extern "C" {
#endif

extern tibems_status
tibemsQueueRequestor_Create(
    tibemsQueueSession          session,
    tibemsMsgRequestor*         msgRequestor,
    tibemsQueue                 queue);

extern tibems_status
tibemsTopicRequestor_Create(
    tibemsTopicSession          session,
    tibemsMsgRequestor*         msgRequestor,
    tibemsTopic                 topic);

extern tibems_status
tibemsMsgRequestor_Request(
    tibemsMsgRequestor          msgRequestor,
    tibemsMsg                   msgSent,
    tibemsMsg*                  msgReply);

extern tibems_status
tibemsMsgRequestor_Close(
    tibemsMsgRequestor          msgRequestor);

#ifdef  __cplusplus
}
#endif

#endif /* _INCLUDED_tibemsmsgreq_h */
