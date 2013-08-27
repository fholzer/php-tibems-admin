/* 
 * Copyright 2001-2006 TIBCO Software Inc.
 * All rights reserved.
 * For more information, please contact:
 * TIBCO Software Inc., Palo Alto, California, USA
 * 
 * $Id: sub.h 21731 2006-05-01 21:41:34Z $
 * 
 */

#ifndef _INCLUDED_tibemstsub_h
#define _INCLUDED_tibemstsub_h

#include "types.h"
#include "status.h"

#if defined(__cplusplus)
extern "C" {
#endif

extern tibems_status
tibemsTopicSubscriber_GetTopic(
    tibemsTopicSubscriber       topicSubscriber,
    tibemsTopic*                topic);

extern tibems_status
tibemsTopicSubscriber_GetNoLocal(
    tibemsTopicSubscriber       topicSubscriber,
    tibems_bool*                isNoLocal);

#ifdef  __cplusplus
}
#endif

#endif /* _INCLUDED_tibemstsub_h */
