/* 
 * Copyright 2001-2006 TIBCO Software Inc.
 * All rights reserved.
 * For more information, please contact:
 * TIBCO Software Inc., Palo Alto, California, USA
 * 
 * $Id: pub.h 21731 2006-05-01 21:41:34Z $
 * 
 */

#ifndef _INCLUDED_tibemstpub_h
#define _INCLUDED_tibemstpub_h

#include "types.h"
#include "status.h"

#if defined(__cplusplus)
extern "C" {
#endif

extern tibems_status
tibemsTopicPublisher_GetTopic(
    tibemsTopicPublisher        topicPublisher,
    tibemsTopic*                topic);

extern tibems_status
tibemsTopicPublisher_Publish(
    tibemsTopicPublisher        topicPublisher,
    tibemsMsg                   msg);

extern tibems_status
tibemsTopicPublisher_PublishEx(
    tibemsTopicPublisher        topicPublisher,
    tibemsMsg                   msg,
    tibems_int                  deliveryMode,
    tibems_int                  priority,
    tibems_long                 timeToLive);

extern tibems_status
tibemsTopicPublisher_PublishToTopic(
    tibemsTopicPublisher        topicPublisher,
    tibemsTopic                 topic,
    tibemsMsg                   msg);

extern tibems_status
tibemsTopicPublisher_PublishToTopicEx(
    tibemsTopicPublisher        topicPublisher,
    tibemsTopic                 topic,
    tibemsMsg                   msg,
    tibemsDeliveryMode          deliveryMode,
    tibems_int                  priority,
    tibems_long                 timeToLive);

#ifdef  __cplusplus
}
#endif

#endif /* _INCLUDED_tibemstpub_h */
