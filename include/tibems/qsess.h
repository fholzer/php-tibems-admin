/* 
 * Copyright 2001-2006 TIBCO Software Inc.
 * All rights reserved.
 * For more information, please contact:
 * TIBCO Software Inc., Palo Alto, California, USA
 * 
 * $Id: qsess.h 21731 2006-05-01 21:41:34Z $
 * 
 */

#ifndef _INCLUDED_tibemsqsess_h
#define _INCLUDED_tibemsqsess_h

#include "types.h"
#include "status.h"

#if defined(__cplusplus)
extern "C" {
#endif

extern tibems_status
tibemsQueueSession_CreateBrowser(
    tibemsQueueSession          session,
    tibemsQueueBrowser*         browser,
    tibemsQueue                 queue,
    const char*                 optionalSelector);

extern tibems_status
tibemsQueueSession_CreateReceiver(
    tibemsQueueSession          session,
    tibemsQueueReceiver*        queueReceiver,
    tibemsQueue                 queue,
    const char*                 optionalSelector);

extern tibems_status
tibemsQueueSession_CreateSender(
    tibemsQueueSession          session,
    tibemsQueueSender*          queueSender,
    tibemsQueue                 queue);

extern tibems_status
tibemsQueueSession_CreateTemporaryQueue(
    tibemsQueueSession          session,
    tibemsTemporaryQueue*       tmpQueue);

extern tibems_status
tibemsQueueSession_DeleteTemporaryQueue(
    tibemsQueueSession          session,
    tibemsTemporaryQueue        tmpQueue);

#ifdef  __cplusplus
}
#endif

#endif /* _INCLUDED_tibemsqsess_h */
