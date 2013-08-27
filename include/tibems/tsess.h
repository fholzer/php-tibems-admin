/* 
 * Copyright 2001-2006 TIBCO Software Inc.
 * All rights reserved.
 * For more information, please contact:
 * TIBCO Software Inc., Palo Alto, California, USA
 * 
 * $Id: tsess.h 21731 2006-05-01 21:41:34Z $
 * 
 */

#ifndef _INCLUDED_tibemstsess_h
#define _INCLUDED_tibemstsess_h

#include "types.h"
#include "status.h"

#if defined(__cplusplus)
extern "C" {
#endif

extern tibems_status
tibemsTopicSession_CreateSubscriber(
    tibemsTopicSession          session,
    tibemsTopicSubscriber*      topicSubscriber,
    tibemsTopic                 topic,
    const char*                 optionalSelector,
    tibems_bool                 noLocal);

extern tibems_status
tibemsTopicSession_CreateDurableSubscriber(
    tibemsTopicSession          session,
    tibemsTopicSubscriber*      topicSubscriber,
    tibemsTopic                 topic,
    const char*                 subscriberName,
    const char*                 optionalSelector,
    tibems_bool                 noLocal);

extern tibems_status
tibemsTopicSession_CreatePublisher(
    tibemsTopicSession          session,
    tibemsTopicPublisher*       topicPublisher,
    tibemsTopic                 topic);

extern tibems_status
tibemsTopicSession_Unsubscribe(
    tibemsTopicSession          session,
    const char*                 subscriberName);

extern tibems_status
tibemsTopicSession_CreateTemporaryTopic(
    tibemsTopicSession          session,
    tibemsTemporaryTopic*       tmpTopic);

extern tibems_status
tibemsTopicSession_DeleteTemporaryTopic(
    tibemsTopicSession          session,
    tibemsTemporaryTopic        tmpTopic);

#ifdef  __cplusplus
}
#endif

#endif /* _INCLUDED_tibemstsess_h */
