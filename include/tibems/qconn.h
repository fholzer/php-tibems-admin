/* 
 * Copyright 2001-2006 TIBCO Software Inc.
 * All rights reserved.
 * For more information, please contact:
 * TIBCO Software Inc., Palo Alto, California, USA
 * 
 * $Id: qconn.h 21731 2006-05-01 21:41:34Z $
 * 
 */

#ifndef _INCLUDED_tibemsqconn_h
#define _INCLUDED_tibemsqconn_h

#include "types.h"
#include "status.h"

#if defined(__cplusplus)
extern "C" {
#endif

extern tibems_status
tibemsQueueConnection_Create(
    tibemsQueueConnection*              queueConnection,
    const char*                         brokerURL,
    const char*                         clientId,
    const char*                         username,
    const char*                         password);

extern tibems_status
tibemsQueueConnection_CreateQueueSession(
    tibemsQueueConnection               queueConnection,
    tibemsQueueSession*                 queueSession,
    tibems_bool                         transacted,
    tibemsAcknowledgeMode               acknowledgeMode);

#ifdef  __cplusplus
}
#endif

#endif /* _INCLUDED_tibemsqconn_h */
