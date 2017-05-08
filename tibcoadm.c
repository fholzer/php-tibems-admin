/* ***********************IMPORTANT ***************************************
 *  Copyright (C) 2007-2008 Lukas Prettenthaler <http://zyclonite.net>    *
 *  This program is free software; you can redistribute it and/or modify  *
 *  it under the terms of the GNU General Public License as published by  *
 *  the Free Software Foundation; either version 2 of the License.        *
 *                                                                        *
 *                      ********************                              *
 *                                                                        *
 *  This program is distributed in the hope that it will be useful,       *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *  GNU Library General Public License for more details.                  *
 *                                                                        *
 *                      ********************                              *
 *                                                                        *
 * You are highly encouraged to send your changes to <rdx@wsn.at>         *
 * for possible incorporation into the main distribution.                 *
 * By sending these changes to <rdx@wsn.at>, it is assumed                *
 * that you are offering <rdx@wsn.at> the unlimited,                      *
 * non-exclusive right to reuse, modify, and relicense the code.          *
 **************************************************************************/
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_tibcoadm.h"

ZEND_DECLARE_MODULE_GLOBALS(tibcoadm)

tibemsQueueConnectionFactory  factory;
tibemsQueueConnection         queueConnection;
tibemsQueueSession            queueSession;
tibemsQueueSender             queueSender;
tibemsQueueReceiver           queueReceiver;
tibemsQueue                   tmpQueue;
tibemsQueue                   queue;
char*                         queueName;


static const zend_function_entry tibcoadm_functions[] = {
    PHP_FE(tibcoadm_version, NULL)
    PHP_FE(tibcoadm_getstatus, NULL)
    PHP_FE(tibcoadm_getusers, NULL)
    PHP_FE(tibcoadm_createuser, NULL)
    PHP_FE(tibcoadm_removeuser, NULL)
    PHP_FE(tibcoadm_edituser, NULL)
    PHP_FE(tibcoadm_getpermissions, NULL)
    PHP_FE(tibcoadm_getqueues, NULL)
    PHP_FE(tibcoadm_createqueue, NULL)
    PHP_FE(tibcoadm_updatequeue, NULL)
    PHP_FE(tibcoadm_removequeue, NULL)
    PHP_FE(tibcoadm_purgequeue, NULL)
    PHP_FE(tibcoadm_gettopics, NULL)
    PHP_FE(tibcoadm_createtopic, NULL)
    PHP_FE(tibcoadm_updatetopic, NULL)
    PHP_FE(tibcoadm_removetopic, NULL)
    PHP_FE(tibcoadm_purgetopic, NULL)
    PHP_FE(tibcoadm_getdurables, NULL)
    PHP_FE(tibcoadm_createdurable, NULL)
    PHP_FE(tibcoadm_removedurable, NULL)
    PHP_FE(tibcoadm_purgedurable, NULL)
    PHP_FE(tibcoadm_getgroups, NULL)
    PHP_FE(tibcoadm_getgroup, NULL)
    PHP_FE(tibcoadm_creategroup, NULL)
    PHP_FE(tibcoadm_removegroup, NULL)
    PHP_FE(tibcoadm_addmember, NULL)
    PHP_FE(tibcoadm_removemember, NULL)
    PHP_FE(tibcoadm_getroutes, NULL)
    PHP_FE(tibcoadm_getacls, NULL)
    PHP_FE(tibcoadm_getconnections, NULL)
    PHP_FE(tibcoadm_removeconnection, NULL)
    PHP_FE(tibcoadm_getjndinames, NULL)
    PHP_FE(tibcoadm_getfactories, NULL)
    PHP_FE(tibcoadm_gettransactions, NULL)
    PHP_FE(tibcoadm_committransaction, NULL)
    PHP_FE(tibcoadm_rollbacktransaction, NULL)
    PHP_FE(tibcoadm_getbridges, NULL)
    PHP_FE(tibcoadm_getbridge, NULL)
    PHP_FE(tibcoadm_createbridge, NULL)
    PHP_FE(tibcoadm_removebridge, NULL)
    PHP_FE(tibcoadm_gettransports, NULL)
    PHP_FE(tibcoadm_getconsumers, NULL)
    PHP_FE(tibcoadm_getproducersstatistics, NULL)
    PHP_FE(tibcoadm_gettopicsstatistics, NULL)
    PHP_FE(tibcoadm_getqueuesstatistics, NULL)
    PHP_FE(tibcoadm_getroutestatistics, NULL)
    PHP_FE(tibcoadm_connect, NULL)
    PHP_FE(tibcoadm_disconnect, NULL)
    {NULL, NULL, NULL}
};

zend_module_entry tibcoadm_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_TIBCOADM_EXTNAME,
    tibcoadm_functions,
    PHP_MINIT(tibcoadm),
    PHP_MSHUTDOWN(tibcoadm),
    PHP_RINIT(tibcoadm),
    PHP_RSHUTDOWN(tibcoadm),
    PHP_MINFO(tibcoadm),
#if ZEND_MODULE_API_NO >= 20010901
    PHP_TIBCOADM_VERSION,
#endif
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_TIBCOADM
ZEND_GET_MODULE(tibcoadm)
#endif

static void php_tibcoadm_init_globals(zend_tibcoadm_globals *tibcoadm_globals)
{
}

long int currentMillis()
{
    struct timeb current;
    long int result;

    ftime(&current);
    result = current.time * 1000 + current.millitm;
    return result;
}

void closeTibco()
{
    tibemsConnection_Close(queueConnection);

    /* destroy factory */
    tibemsConnectionFactory_Destroy(factory);
}

void fail(tibems_status s)
{
    const char* msg = tibemsStatus_GetText(s);
    php_error(E_ERROR, "%s(): Status: %d %s", get_active_function_name(TSRMLS_C),s,msg?msg:"(Undefined Error)");
}

PHP_RINIT_FUNCTION(tibcoadm)
{
    factory = NULL;
    queueConnection = NULL;
    queueSession = NULL;
    queueSender = NULL;
    queueReceiver = NULL;
    tmpQueue = NULL;
    queue = NULL;
    queueName = "$sys.admin";
    TIBCOADM_G(arseq) = 0;

    return SUCCESS;
}

PHP_RSHUTDOWN_FUNCTION(tibcoadm)
{
    closeTibco();

    return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(tibcoadm)
{
    closeTibco();

    return SUCCESS;
}

PHP_MINIT_FUNCTION(tibcoadm)
{
    ZEND_INIT_MODULE_GLOBALS(tibcoadm, php_tibcoadm_init_globals, NULL);
}

PHP_MINFO_FUNCTION(tibcoadm)
{
    php_info_print_table_start();
    php_info_print_table_header(2, "TIBCO EMS Admin Support", "Enabled");
    php_info_print_table_row(2, "Version", PHP_TIBCOADM_VERSION);
    php_info_print_table_row(2, "Copyright", "Lukas Prettenthaler (zyclonite.net)");
    php_info_print_table_end();
}

PHP_FUNCTION(tibcoadm_version)
{
    RETURN_STRING(PHP_TIBCOADM_VERSION, 1);
}

PHP_FUNCTION(tibcoadm_disconnect)
{
    tibems_status status = TIBEMS_OK;

    /* destroy the queue */
    status = tibemsQueue_Destroy(queue);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    closeTibco();

    RETURN_TRUE;
}

void receiveReply(int j, tibemsMapMsg* msg)
{
    tibems_status status = TIBEMS_OK;
    int           rrseq = 0;
    long          l, l1, l2, l3;

    l = 5000L;
    /* read messages */
    do 
    {
        status = tibemsMsgConsumer_ReceiveTimeout(queueReceiver, msg, l);
        if (status == TIBEMS_TIMEOUT)
        {
            fail(status);
        }
        else if (status != TIBEMS_OK)
        {
            fail(status);
        }

        if(tibemsMsg_GetIntProperty(*msg,"arseq",&rrseq) != TIBEMS_OK)
            break;
        if(rrseq == TIBCOADM_G(arseq))
            break;
        l2 = currentMillis();
        l3 = l2 - l1;
        if(l3 > 200L)
            l -= l3;
    } while(l > 10L);
}

void sendRequest(int i, tibemsMapMsg* msg, tibems_bool flag)
{
    tibems_status status = TIBEMS_OK;
    int rstatus;

    status = tibemsMsg_SetIntProperty(*msg,"code",i);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    TIBCOADM_G(arseq)++;

    status = tibemsMsg_SetIntProperty(*msg,"arseq",TIBCOADM_G(arseq));
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMsg_SetBooleanProperty(*msg,"save",TIBEMS_TRUE);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMsg_SetReplyTo(*msg,tmpQueue);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsQueueSender_Send(queueSender,*msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

//    char* buffer[5000];
//    tibemsMsg_PrintToBuffer(*msg, &buffer, 5000);
//    php_printf("Message sent: %s<br><br>",buffer);

    status = tibemsMsg_Destroy(*msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    receiveReply(TIBCOADM_G(arseq), msg);

//    tibemsMsg_PrintToBuffer(*msg, &buffer, 5000);
//    php_printf("Message received: %s<br><br>",buffer);

    status = tibemsMsg_GetIntProperty(*msg,"status",&rstatus);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    if(rstatus != 0)
    {
        switch(rstatus)
        {
            case 30:
                php_error(E_ERROR, "%s(): Invalid Name on parsing the answer", get_active_function_name(TSRMLS_C));
                break;
            case 91:
                php_error(E_ERROR, "%s(): Name Exists on parsing the answer", get_active_function_name(TSRMLS_C));
                break;
            case 6:
            case 27:
                php_error(E_ERROR, "%s(): Security Exception on parsing the answer", get_active_function_name(TSRMLS_C));
                break;
        }
    }
}

int reverseInt (int i) {
    unsigned char c1, c2, c3, c4;

    if(is_bigendian()) {
        c1 = i & 255;
        c2 = (i >> 8) & 255;
        c3 = (i >> 16) & 255;
        c4 = (i >> 24) & 255;

        return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
    }else{
        return i;
    }
}

char *StrToHex(char *str, int len)
{
    char *newstr = malloc (sizeof(char)*len*2+1);
    char *cpold = str;
    char *cpnew = newstr;
    int  i;

    for(i=0; i < len; i++) {
        sprintf(cpnew, "%02X", (char)(*cpold++));
        cpnew+=2;
    }
    *(cpnew) = '\0';
    return(newstr);
}

void mapMsgToZendArray(tibemsMapMsg msg, zval* zarray)
{
    tibemsMsgEnum  enumeration;
    const char     *name;
    tibems_status  status = TIBEMS_OK;
    tibemsMsgField field;
    zval           *tarray;

    status = tibemsMapMsg_GetMapNames(msg,&enumeration);

    while((status = tibemsMsgEnum_GetNextName(enumeration,&name)) == TIBEMS_OK)
    {
        status = tibemsMapMsg_GetField(msg,name,&field);
        if (status == TIBEMS_OK)
        switch(field.type)
        {
            case TIBEMS_NULL:
                add_assoc_null(zarray, (char*)name);
                break;
            case TIBEMS_BOOL:
                add_assoc_bool(zarray, (char*)name, field.data.boolValue?1:0);
                break;
            case TIBEMS_BYTE:
                add_assoc_long(zarray, (char*)name, field.data.byteValue);
                break;
            case TIBEMS_SHORT:
                add_assoc_long(zarray, (char*)name, field.data.shortValue);
                break;
            case TIBEMS_INT:
                if(strcmp(name, "n")!=0)
                add_assoc_long(zarray, (char*)name, field.data.intValue);
                break;
            case TIBEMS_LONG:
                add_assoc_long(zarray, (char*)name, field.data.longValue);
                break;
            case TIBEMS_FLOAT:
                add_assoc_double(zarray, (char*)name, field.data.floatValue);
                break;
            case TIBEMS_DOUBLE:
                add_assoc_double(zarray, (char*)name, field.data.doubleValue);
                break;
            case TIBEMS_UTF8:
                add_assoc_string(zarray, (char*)name, field.data.utf8Value,1);
                break;
            case TIBEMS_BYTES:
                ALLOC_INIT_ZVAL(tarray);
                array_init(tarray);
                add_assoc_string(tarray, "bytes", to64frombits(field.data.bytesValue, field.size),1);
                add_assoc_zval(zarray, (char*)name, tarray);
                break;
            case TIBEMS_MAP_MSG:
                ALLOC_INIT_ZVAL(tarray);
                array_init(tarray);
                mapMsgToZendArray(field.data.msgValue, tarray);
                add_assoc_zval(zarray, (char*)name, tarray);
                break;
        }
    }
    tibemsMsgEnum_Destroy(enumeration);
}

void msgPropToZendArray(tibemsMapMsg msg, zval* zarray)
{
    tibemsMsgEnum  enumeration;
    const char     *name;
    tibems_status  status = TIBEMS_OK;
    tibemsMsgField field;
    zval           *tarray;

    status = tibemsMsg_GetPropertyNames(msg,&enumeration);

    while((status = tibemsMsgEnum_GetNextName(enumeration,&name)) == TIBEMS_OK)
    {
        status = tibemsMsg_GetProperty(msg,name,&field);
        if (status == TIBEMS_OK)
        switch(field.type)
        {
            case TIBEMS_NULL:
                add_assoc_null(zarray, (char*)name);
                break;
            case TIBEMS_BOOL:
                add_assoc_bool(zarray, (char*)name, field.data.boolValue?1:0);
                break;
            case TIBEMS_BYTE:
                add_assoc_long(zarray, (char*)name, field.data.byteValue);
                break;
            case TIBEMS_SHORT:
                add_assoc_long(zarray, (char*)name, field.data.shortValue);
                break;
            case TIBEMS_INT:
		if(strcmp(name, "n")!=0)
                add_assoc_long(zarray, (char*)name, field.data.intValue);
                break;
            case TIBEMS_LONG:
                add_assoc_long(zarray, (char*)name, field.data.longValue);
                break;
            case TIBEMS_FLOAT:
                add_assoc_double(zarray, (char*)name, field.data.floatValue);
                break;
            case TIBEMS_DOUBLE:
                add_assoc_double(zarray, (char*)name, field.data.doubleValue);
                break;
            case TIBEMS_UTF8:
                add_assoc_string(zarray, (char*)name, field.data.utf8Value,1);
                break;
            case TIBEMS_BYTES:
                ALLOC_INIT_ZVAL(tarray);
                array_init(tarray);
                if(strstr((char*)name, "xid") != 0) {
                    int g, b;
                    char tmp[100];
                    int  *j;
                    char* i = field.data.bytesValue;
                    j = field.data.bytesValue;
                    add_assoc_long(tarray, "formatId", reverseInt(*j));
                    j++;
                    add_assoc_long(tarray, "globalTxIdLength", reverseInt(*j));
                    g = reverseInt(*j);
                    j++;
                    add_assoc_long(tarray, "branchQualLength", reverseInt(*j));
                    b = reverseInt(*j);
                    j++;
                    i = (char*)j;
                    strncpy(tmp, (char*)i, g);
                    tmp[g]='\0';
                    add_assoc_string(tarray, "globalTxId", tmp,1);
                    i+=g;
                    strncpy(tmp, (char*)i, b);
                    tmp[b]='\0';
                    add_assoc_string(tarray, "branchQual", tmp,1);
                    i+=b;
                    j = (int*)i;
                    add_assoc_long(tarray, "state", reverseInt(*j));
                    add_assoc_string(tarray, "bytes", to64frombits(field.data.bytesValue, field.size),1);
                }else{
                    add_assoc_string(tarray, "bytes", to64frombits(field.data.bytesValue, field.size),1);
                }
                add_assoc_zval(zarray, (char*)name, tarray);
                break;
            case TIBEMS_MAP_MSG:
                ALLOC_INIT_ZVAL(tarray);
                array_init(tarray);
                mapMsgToZendArray(field.data.msgValue, tarray);
                add_assoc_zval(zarray, (char*)name, tarray);
                break;
        }
    }
    tibemsMsgEnum_Destroy(enumeration);
}

char *manglePassword(const char *s, bool flag, int *len)
{
	int i, j, k, l;
	char byte0, byte1, byte2;
	char *abyte0 = (char*)strdup(s);
	char *abyte1;

	j = strlen(s);
	if (j % 16) {
		i = (j / 16 + 1) * 16 + 4;
	} else {
		i = j + 4;
	}
	*len = i;
	abyte1 = malloc (sizeof(char)*i);
	srandom(time(NULL));
	strcpy((abyte1+4), abyte0);
	for ( k = j+4; k < i; ++k) {
		abyte1[k] = (char)random();
	}

	do {
		k = random();
	} while (k == 0 || k == -1);
	byte1 = (char)k;
	byte2 = (char)(k >> 8);
	abyte1[0] = byte1;
	abyte1[1] = byte2;
	abyte1[2] = (char)(j + 7777 ^ abyte1[1]);
	abyte1[3] = (char)(j + 7777 >> 8 ^ abyte1[0]);


	for(l = 4; l < i; l++ ){
		byte0 = ((l % 2) == 0) ? byte1 : byte2;
		abyte1[l] = (char)(abyte1[l] ^ byte0);
		j = byte0 & 1;
		byte0 >>= 1; /* byte0 = byte0 >> 1; */
		if(j != 0) {
			byte0 |= 0x80;
		} else {
			if(!flag) {
				byte0 &= 0x7f;
			}
		}
		if(l % 2 != 0) {
			byte2 = byte0;
		} else {
			byte1 = byte0;
		}
	}

	free (abyte0);
	return abyte1;
}

PHP_FUNCTION(tibcoadm_getroutestatistics)
{
    tibems_status status = TIBEMS_OK;
    tibemsMapMsg  msg    = NULL;
    char*         routeName;
    int           routeName_len = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &routeName, &routeName_len) == FAILURE) {
        RETURN_NULL();
    }

    /* create message */
    status = tibemsMapMsg_Create(&msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetString(msg,"name",routeName);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    sendRequest(163, &msg, TIBEMS_TRUE);

    array_init(return_value);

    mapMsgToZendArray(msg, return_value);

    /* destroy the message */
    status = tibemsMsg_Destroy(msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }
}

PHP_FUNCTION(tibcoadm_getqueuesstatistics)
{
    tibems_status status = TIBEMS_OK;
    tibemsMapMsg  msg    = NULL;
    char*         destName;
    int           destName_len = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &destName, &destName_len) == FAILURE) {
        RETURN_NULL();
    }

    /* create message */
    status = tibemsMapMsg_Create(&msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetString(msg,"pattern",destName);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetInt(msg,"dt",1);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetBoolean(msg,"ia",TIBEMS_TRUE);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    sendRequest(12, &msg, TIBEMS_TRUE);

    array_init(return_value);

    mapMsgToZendArray(msg, return_value);

    /* destroy the message */
    status = tibemsMsg_Destroy(msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }
}

PHP_FUNCTION(tibcoadm_gettopicsstatistics)
{
    tibems_status status = TIBEMS_OK;
    tibemsMapMsg  msg    = NULL;
    char*         destName;
    int           destName_len = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &destName, &destName_len) == FAILURE) {
        RETURN_NULL();
    }

    /* create message */
    status = tibemsMapMsg_Create(&msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetString(msg,"pattern",destName);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetInt(msg,"dt",2);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetBoolean(msg,"ia",TIBEMS_TRUE);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    sendRequest(12, &msg, TIBEMS_TRUE);

    array_init(return_value);

    mapMsgToZendArray(msg, return_value);

    /* destroy the message */
    status = tibemsMsg_Destroy(msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }
}

PHP_FUNCTION(tibcoadm_getproducersstatistics)
{
    tibems_status status = TIBEMS_OK;
    tibemsMapMsg  msg    = NULL;
    char*         userName;
    int           userName_len = 0;
    long          connId = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|ls", &connId, &userName, &userName_len) == FAILURE) {
        RETURN_NULL();
    }

    /* create message */
    status = tibemsMapMsg_Create(&msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    if(userName_len > 0) {
        status = tibemsMapMsg_SetString(msg,"user",userName);
        if (status != TIBEMS_OK)
        {
            fail(status);
        }
    }

    if(connId > 0) {
        status = tibemsMapMsg_SetLong(msg,"connid",connId);
        if (status != TIBEMS_OK)
        {
            fail(status);
        }
    }

    sendRequest(160, &msg, TIBEMS_TRUE);

    array_init(return_value);

    mapMsgToZendArray(msg, return_value);

    /* destroy the message */
    status = tibemsMsg_Destroy(msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }
}

PHP_FUNCTION(tibcoadm_getdurables)
{
    tibems_status status = TIBEMS_OK;
    tibemsMapMsg  msg    = NULL;

    /* create message */
    status = tibemsMapMsg_Create(&msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetString(msg,"tn","");
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    sendRequest(30, &msg, TIBEMS_TRUE);

    array_init(return_value);

    mapMsgToZendArray(msg, return_value);

    /* destroy the message */
    status = tibemsMsg_Destroy(msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }
}

PHP_FUNCTION(tibcoadm_removedurable)
{
    tibems_status status = TIBEMS_OK;
    tibemsMapMsg  msg    = NULL;
    char*         durableName;
    int           durableName_len = 0;
    char*         clientId;
    int           clientId_len = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|s", &durableName, &durableName_len, &clientId, &clientId_len) == FAILURE) {
        RETURN_NULL();
    }

    /* create message */
    status = tibemsMapMsg_Create(&msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetString(msg,"name",durableName);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    if(clientId_len > 0) {
        status = tibemsMapMsg_SetString(msg,"clientID",clientId);
        if (status != TIBEMS_OK)
        {
            fail(status);
        }
    }

    sendRequest(33, &msg, TIBEMS_TRUE);

    /* destroy the message */
    status = tibemsMsg_Destroy(msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }
    RETURN_TRUE;
}

PHP_FUNCTION(tibcoadm_purgedurable)
{
    tibems_status status = TIBEMS_OK;
    tibemsMapMsg  msg    = NULL;
    char*         durableName;
    int           durableName_len = 0;
    char*         clientId;
    int           clientId_len = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|s", &durableName, &durableName_len, &clientId, &clientId_len) == FAILURE) {
        RETURN_NULL();
    }

    /* create message */
    status = tibemsMapMsg_Create(&msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetString(msg,"name",durableName);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    if(clientId_len > 0) {
        status = tibemsMapMsg_SetString(msg,"clientID",clientId);
        if (status != TIBEMS_OK)
        {
            fail(status);
        }
    }

    sendRequest(32, &msg, TIBEMS_TRUE);

    /* destroy the message */
    status = tibemsMsg_Destroy(msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }
    RETURN_TRUE;
}

PHP_FUNCTION(tibcoadm_createdurable)
{
    tibems_status status = TIBEMS_OK;
    tibemsMapMsg  msg    = NULL;
    char*         durableName;
    int           durableName_len = 0;
    char*         topicName;
    int           topicName_len = 0;
    char*         clientId;
    int           clientId_len = 0;
    char*         selector;
    int           selector_len = 0;
    tibems_bool   nolocal = TIBEMS_FALSE;
    tibems_bool   route = TIBEMS_FALSE;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss|ssbb", &topicName, &topicName_len, &durableName, &durableName_len, &clientId, &clientId_len, &selector, &selector_len, &nolocal, &route) == FAILURE) {
        RETURN_NULL();
    }

    /* create message */
    status = tibemsMapMsg_Create(&msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetString(msg,"topic",topicName);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetString(msg,"name",durableName);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    if(clientId_len > 0) {
        status = tibemsMapMsg_SetString(msg,"clientID",clientId);
        if (status != TIBEMS_OK)
        {
            fail(status);
        }
    }

    if(selector_len > 0) {
        status = tibemsMapMsg_SetString(msg,"selector",selector);
        if (status != TIBEMS_OK)
        {
            fail(status);
        }
    }

    if(nolocal == TIBEMS_TRUE) {
        status = tibemsMapMsg_SetBoolean(msg,"nolocal",nolocal);
        if (status != TIBEMS_OK)
        {
             fail(status);
        }
    }

    if(route == TIBEMS_TRUE) {
        status = tibemsMapMsg_SetBoolean(msg,"route",route);
        if (status != TIBEMS_OK)
        {
            fail(status);
        }
    }

    sendRequest(211, &msg, TIBEMS_TRUE);

    /* destroy the message */
    status = tibemsMsg_Destroy(msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }
    RETURN_TRUE;
}

PHP_FUNCTION(tibcoadm_getgroups)
{
    tibems_status status = TIBEMS_OK;
    tibemsMapMsg  msg    = NULL;

    /* create message */
    status = tibemsMapMsg_Create(&msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    sendRequest(50, &msg, TIBEMS_TRUE);

    array_init(return_value);

    mapMsgToZendArray(msg, return_value);

    /* destroy the message */
    status = tibemsMsg_Destroy(msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }
}

PHP_FUNCTION(tibcoadm_getgroup)
{
    tibems_status status = TIBEMS_OK;
    tibemsMapMsg  msg    = NULL;
    char*         groupName;
    int           groupName_len = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &groupName, &groupName_len) == FAILURE) {
        RETURN_NULL();
    }

    /* create message */
    status = tibemsMapMsg_Create(&msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetString(msg,"name",groupName);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    sendRequest(48, &msg, TIBEMS_TRUE);

    array_init(return_value);

    mapMsgToZendArray(msg, return_value);

    /* destroy the message */
    status = tibemsMsg_Destroy(msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }
}

PHP_FUNCTION(tibcoadm_creategroup)
{
    tibems_status status = TIBEMS_OK;
    tibemsMapMsg  msg    = NULL;
    char*         groupName;
    int           groupName_len = 0;
    char*         groupDesc;
    int           groupDesc_len = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|s", &groupName, &groupName_len, &groupDesc, &groupDesc_len) == FAILURE) {
        RETURN_NULL();
    }

    /* create message */
    status = tibemsMapMsg_Create(&msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetString(msg,"name",groupName);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    if(groupDesc_len > 0) {
        status = tibemsMapMsg_SetString(msg,"desc",groupDesc);
        if (status != TIBEMS_OK)
        {
            fail(status);
        }
    }

    sendRequest(47, &msg, TIBEMS_TRUE);

    /* destroy the message */
    status = tibemsMsg_Destroy(msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }
    RETURN_TRUE;
}

PHP_FUNCTION(tibcoadm_removegroup)
{
    tibems_status status = TIBEMS_OK;
    tibemsMapMsg  msg    = NULL;
    char*         groupName;
    int           groupName_len = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &groupName, &groupName_len) == FAILURE) {
        RETURN_NULL();
    }

    /* create message */
    status = tibemsMapMsg_Create(&msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetString(msg,"name",groupName);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    sendRequest(52, &msg, TIBEMS_TRUE);

    /* destroy the message */
    status = tibemsMsg_Destroy(msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }
    RETURN_TRUE;
}

PHP_FUNCTION(tibcoadm_addmember)
{
    tibems_status status = TIBEMS_OK;
    tibemsMapMsg  msg    = NULL;
    char*         groupName;
    int           groupName_len = 0;
    char*         memberName;
    int           memberName_len = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &groupName, &groupName_len, &memberName, &memberName_len) == FAILURE) {
        RETURN_NULL();
    }

    /* create message */
    status = tibemsMapMsg_Create(&msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetString(msg,"name",groupName);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetString(msg,"u0",memberName);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetInt(msg,"n",1);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    sendRequest(54, &msg, TIBEMS_TRUE);

    /* destroy the message */
    status = tibemsMsg_Destroy(msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }
    RETURN_TRUE;
}

PHP_FUNCTION(tibcoadm_removemember)
{
    tibems_status status = TIBEMS_OK;
    tibemsMapMsg  msg    = NULL;
    char*         groupName;
    int           groupName_len = 0;
    char*         memberName;
    int           memberName_len = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &groupName, &groupName_len, &memberName, &memberName_len) == FAILURE) {
        RETURN_NULL();
    }

    /* create message */
    status = tibemsMapMsg_Create(&msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetString(msg,"name",groupName);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetString(msg,"u0",memberName);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetInt(msg,"n",1);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    sendRequest(55, &msg, TIBEMS_TRUE);

    /* destroy the message */
    status = tibemsMsg_Destroy(msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }
    RETURN_TRUE;
}

PHP_FUNCTION(tibcoadm_getroutes)
{
    tibems_status status = TIBEMS_OK;
    tibemsMapMsg  msg    = NULL;

    /* create message */
    status = tibemsMapMsg_Create(&msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetBoolean(msg,"details",TIBEMS_TRUE);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    sendRequest(91, &msg, TIBEMS_TRUE);

    array_init(return_value);

    mapMsgToZendArray(msg, return_value);

    /* destroy the message */
    status = tibemsMsg_Destroy(msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }
}

PHP_FUNCTION(tibcoadm_getacls)
{
    tibems_status status = TIBEMS_OK;
    tibemsMapMsg  msg    = NULL;

    /* create message */
    status = tibemsMapMsg_Create(&msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetInt(msg,"aclsrc",0);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    sendRequest(74, &msg, TIBEMS_TRUE);

    array_init(return_value);

    mapMsgToZendArray(msg, return_value);

    /* destroy the message */
    status = tibemsMsg_Destroy(msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }
}

PHP_FUNCTION(tibcoadm_getpermissions)
{
    tibems_status status = TIBEMS_OK;
    tibemsMapMsg  msg    = NULL;
    char*         userName;
    int           userName_len = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &userName, &userName_len) == FAILURE) {
        RETURN_NULL();
    }
    /* create message */
    status = tibemsMapMsg_Create(&msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetInt(msg,"aclsrc",1);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetString(msg,"name",userName);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetInt(msg,"queryflags",15);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    sendRequest(74, &msg, TIBEMS_TRUE);

    array_init(return_value);

    mapMsgToZendArray(msg, return_value);

    /* destroy the message */
    status = tibemsMsg_Destroy(msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }
}

PHP_FUNCTION(tibcoadm_getconnections)
{
    tibems_status status = TIBEMS_OK;
    tibemsMapMsg  msg    = NULL;

    /* create message */
    status = tibemsMapMsg_Create(&msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetString(msg,"host","");
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetString(msg,"username","");
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetInt(msg,"dt",0);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    sendRequest(100, &msg, TIBEMS_TRUE);

    array_init(return_value);

    mapMsgToZendArray(msg, return_value);

    /* destroy the message */
    status = tibemsMsg_Destroy(msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }
}

PHP_FUNCTION(tibcoadm_removeconnection)
{
    tibems_status status = TIBEMS_OK;
    tibemsMapMsg  msg    = NULL;
    long          connectionId;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &connectionId) == FAILURE) {
        RETURN_NULL();
    }

    /* create message */
    status = tibemsMapMsg_Create(&msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetLong(msg,"connID",connectionId);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    sendRequest(101, &msg, TIBEMS_TRUE);

    /* destroy the message */
    status = tibemsMsg_Destroy(msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }
    RETURN_TRUE;
}

PHP_FUNCTION(tibcoadm_getjndinames)
{
    tibems_status status = TIBEMS_OK;
    tibemsMapMsg  msg    = NULL;

    /* create message */
    status = tibemsMapMsg_Create(&msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetString(msg,"pattern","");
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    sendRequest(143, &msg, TIBEMS_TRUE);

    array_init(return_value);

    mapMsgToZendArray(msg, return_value);

    /* destroy the message */
    status = tibemsMsg_Destroy(msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }
}

PHP_FUNCTION(tibcoadm_getfactories)
{
    tibems_status status = TIBEMS_OK;
    tibemsMapMsg  msg    = NULL;

    /* create message */
    status = tibemsMapMsg_Create(&msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    sendRequest(153, &msg, TIBEMS_TRUE);

    array_init(return_value);

    mapMsgToZendArray(msg, return_value);

    /* destroy the message */
    status = tibemsMsg_Destroy(msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }
}

PHP_FUNCTION(tibcoadm_gettransactions)
{
    tibems_status status = TIBEMS_OK;
    tibemsMapMsg  msg    = NULL;

    /* create message */
    status = tibemsMapMsg_Create(&msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    sendRequest(200, &msg, TIBEMS_TRUE);

    array_init(return_value);

    msgPropToZendArray(msg, return_value);

    /* destroy the message */
    status = tibemsMsg_Destroy(msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }
}

PHP_FUNCTION(tibcoadm_committransaction)
{
    tibems_status status = TIBEMS_OK;
    tibemsMapMsg  msg    = NULL;
    char*         transId;
    int           transId_len = 0;
    char          transIdEnc[256];
    int           transIdEnc_len = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &transId, &transId_len) == FAILURE) {
        RETURN_NULL();
    }

    /* create message */
    status = tibemsMapMsg_Create(&msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    transIdEnc_len=from64tobits(transIdEnc, transId);

    status = _tibemsMsg_setBytesProperty(msg,"xid0",transIdEnc,transIdEnc_len);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    sendRequest(201, &msg, TIBEMS_TRUE);

    /* destroy the message */
    status = tibemsMsg_Destroy(msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }
    RETURN_TRUE;
}

PHP_FUNCTION(tibcoadm_rollbacktransaction)
{
    tibems_status status = TIBEMS_OK;
    tibemsMapMsg  msg    = NULL;
    char*         transId;
    int           transId_len = 0;
    char          transIdEnc[256];
    int           transIdEnc_len = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &transId, &transId_len) == FAILURE) {
        RETURN_NULL();
    }

    /* create message */
    status = tibemsMapMsg_Create(&msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    transIdEnc_len=from64tobits(transIdEnc, transId);

    status = _tibemsMsg_setBytesProperty(msg,"xid0",transIdEnc,transIdEnc_len);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    sendRequest(202, &msg, TIBEMS_TRUE);

    /* destroy the message */
    status = tibemsMsg_Destroy(msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }
    RETURN_TRUE;
}

PHP_FUNCTION(tibcoadm_getbridges)
{
    tibems_status status = TIBEMS_OK;
    tibemsMapMsg  msg    = NULL;

    /* create message */
    status = tibemsMapMsg_Create(&msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetString(msg,"pattern","");
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetInt(msg,"type",0);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetBoolean(msg,"details",TIBEMS_TRUE);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    sendRequest(209, &msg, TIBEMS_TRUE);

    array_init(return_value);

    mapMsgToZendArray(msg, return_value);

    /* destroy the message */
    status = tibemsMsg_Destroy(msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }
}

PHP_FUNCTION(tibcoadm_getbridge)
{
    tibems_status status = TIBEMS_OK;
    tibemsMapMsg  msg    = NULL;
    char*         bridgeSrc;
    int           bridgeSrc_len = 0;
    long          bridgeSrcType;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sl", &bridgeSrc, &bridgeSrc_len, &bridgeSrcType) == FAILURE) {
        RETURN_NULL();
    }

    /* create message */
    status = tibemsMapMsg_Create(&msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMsg_SetStringProperty(msg,"pattern",bridgeSrc);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    switch(bridgeSrcType)
    {
        case 2:
            status = tibemsMsg_SetIntProperty(msg,"type",2);
            break;
        case 1:
            status = tibemsMsg_SetIntProperty(msg,"type",1);
            break;
        default:
            status = tibemsMsg_SetIntProperty(msg,"type",0);
            break;
    }
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    sendRequest(210, &msg, TIBEMS_TRUE);

    array_init(return_value);

    mapMsgToZendArray(msg, return_value);

    /* destroy the message */
    status = tibemsMsg_Destroy(msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }
}

PHP_FUNCTION(tibcoadm_createbridge)
{
    tibems_status status = TIBEMS_OK;
    tibemsMapMsg  msg    = NULL;
    char*         bridgeDst;
    int           bridgeDst_len = 0;
    long          bridgeDstType;
    char*         bridgeSrc;
    int           bridgeSrc_len = 0;
    long          bridgeSrcType;
    char*         selector;
    int           selector_len = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "slsl|s", &bridgeSrc, &bridgeSrc_len, &bridgeSrcType, &bridgeDst, &bridgeDst_len, &bridgeDstType, &selector, &selector_len) == FAILURE) {
        RETURN_NULL();
    }

    /* create message */
    status = tibemsMapMsg_Create(&msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetString(msg,"sn",bridgeSrc);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    switch(bridgeSrcType)
    {
        case 2:
            status = tibemsMapMsg_SetInt(msg,"st",2);
            break;
        default:
            status = tibemsMapMsg_SetInt(msg,"st",1);
            break;
    }
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetString(msg,"tn",bridgeDst);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    switch(bridgeDstType)
    {
        case 2:
            status = tibemsMapMsg_SetInt(msg,"tt",2);
            break;
        default:
            status = tibemsMapMsg_SetInt(msg,"tt",1);
            break;
    }
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    if(selector_len > 0) {
        status = tibemsMapMsg_SetString(msg,"sel",selector);
        if (status != TIBEMS_OK)
        {
            fail(status);
        }
    }

    sendRequest(220, &msg, TIBEMS_TRUE);

    /* destroy the message */
    status = tibemsMsg_Destroy(msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }
    RETURN_TRUE;
}

PHP_FUNCTION(tibcoadm_removebridge)
{
    tibems_status status = TIBEMS_OK;
    tibemsMapMsg  msg    = NULL;
    char*         bridgeDst;
    int           bridgeDst_len = 0;
    long          bridgeDstType;
    char*         bridgeSrc;
    int           bridgeSrc_len = 0;
    long          bridgeSrcType;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "slsl", &bridgeSrc, &bridgeSrc_len, &bridgeSrcType, &bridgeDst, &bridgeDst_len, &bridgeDstType) == FAILURE) {
        RETURN_NULL();
    }

    /* create message */
    status = tibemsMapMsg_Create(&msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetString(msg,"sn",bridgeSrc);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    switch(bridgeSrcType)
    {
        case 2:
            status = tibemsMapMsg_SetInt(msg,"st",2);
            break;
        default:
            status = tibemsMapMsg_SetInt(msg,"st",1);
            break;
    }
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetString(msg,"tn",bridgeDst);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    switch(bridgeDstType)
    {
        case 2:
            status = tibemsMapMsg_SetInt(msg,"tt",2);
            break;
        default:
            status = tibemsMapMsg_SetInt(msg,"tt",1);
            break;
    }
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    sendRequest(221, &msg, TIBEMS_TRUE);

    /* destroy the message */
    status = tibemsMsg_Destroy(msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }
    RETURN_TRUE;
}

PHP_FUNCTION(tibcoadm_gettransports)
{
    tibems_status status = TIBEMS_OK;
    tibemsMapMsg  msg    = NULL;

    /* create message */
    status = tibemsMapMsg_Create(&msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetString(msg,"pattern","");
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetInt(msg,"type",0);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetBoolean(msg,"details",TIBEMS_TRUE);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    sendRequest(207, &msg, TIBEMS_TRUE);

    array_init(return_value);

    mapMsgToZendArray(msg, return_value);

    /* destroy the message */
    status = tibemsMsg_Destroy(msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }
}

PHP_FUNCTION(tibcoadm_getconsumers)
{
    tibems_status status = TIBEMS_OK;
    tibemsMapMsg  msg    = NULL;

    /* create message */
    status = tibemsMapMsg_Create(&msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetString(msg,"pattern","");
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    sendRequest(226, &msg, TIBEMS_TRUE);

    array_init(return_value);

    mapMsgToZendArray(msg, return_value);

    /* destroy the message */
    status = tibemsMsg_Destroy(msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }
}

PHP_FUNCTION(tibcoadm_gettopics)
{
    tibems_status status = TIBEMS_OK;
    tibemsMapMsg  msg    = NULL;
    char*         destName;
    int           destName_len = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|s", &destName, &destName_len) == FAILURE) {
        RETURN_NULL();
    }

    /* create message */
    status = tibemsMapMsg_Create(&msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    if (destName_len > 0)
    {
        status = tibemsMapMsg_SetString(msg,"pattern",destName);
        if (status != TIBEMS_OK)
        {
            fail(status);
        }
    }
    
    status = tibemsMapMsg_SetInt(msg,"dt",2);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetBoolean(msg,"ia",TIBEMS_TRUE);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    sendRequest(12, &msg, TIBEMS_TRUE);

    array_init(return_value);

    mapMsgToZendArray(msg, return_value);

    /* destroy the message */
    status = tibemsMsg_Destroy(msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }
}

PHP_FUNCTION(tibcoadm_removetopic)
{
    tibems_status status = TIBEMS_OK;
    tibemsMapMsg  msg    = NULL;
    char*         destName;
    int           destName_len = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &destName, &destName_len) == FAILURE) {
        RETURN_NULL();
    }

    /* create message */
    status = tibemsMapMsg_Create(&msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetString(msg,"dn",destName);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetInt(msg,"dt",2);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    sendRequest(16, &msg, TIBEMS_TRUE);

    /* destroy the message */
    status = tibemsMsg_Destroy(msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }
    RETURN_TRUE;
}

PHP_FUNCTION(tibcoadm_purgetopic)
{
    tibems_status status = TIBEMS_OK;
    tibemsMapMsg  msg    = NULL;
    char*         destName;
    int           destName_len = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &destName, &destName_len) == FAILURE) {
        RETURN_NULL();
    }

    /* create message */
    status = tibemsMapMsg_Create(&msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetString(msg,"pattern",destName);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetInt(msg,"dt",2);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    sendRequest(15, &msg, TIBEMS_TRUE);

    /* destroy the message */
    status = tibemsMsg_Destroy(msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }
    RETURN_TRUE;
}

PHP_FUNCTION(tibcoadm_createtopic)
{
    tibems_status status = TIBEMS_OK;
    tibemsMapMsg  msg    = NULL;
    char*         destName;
    int           destName_len = 0;
    int           prefetch = 64;
    int           overview = 0;
    long          maxbytes = 0;
    long          maxmsgs = 0;
    long          expiration = 0;
    long          flowcontrol = 0;
    tibems_bool   failsafe = TIBEMS_FALSE;
    tibems_bool   secure = TIBEMS_FALSE;
    tibems_bool   global = TIBEMS_FALSE;
    tibems_bool   sname = TIBEMS_FALSE;
    tibems_bool   snameenf = TIBEMS_FALSE;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|llllllbbbbb", &destName, &destName_len, &prefetch, &overview, &maxbytes, &maxmsgs, &expiration, &flowcontrol, &failsafe, &secure, &global, &sname, &snameenf) == FAILURE) {
        RETURN_NULL();
    }

    /* create message */
    status = tibemsMapMsg_Create(&msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetString(msg,"dn",destName);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetInt(msg,"dt",2);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetInt(msg,"pf",prefetch); //prefetch
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetInt(msg,"op",overview); //overview policy
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetLong(msg,"mb",maxbytes); //maxbytes
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetLong(msg,"mm",maxmsgs); //maxmsgs
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetLong(msg,"fcs",flowcontrol); //flowControl
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetLong(msg,"expy",expiration); //expiration
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetBoolean(msg,"failsafe",failsafe); //failsafe
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetBoolean(msg,"secure",secure); //secure
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetBoolean(msg,"global",global); //global
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetBoolean(msg,"sname",sname); //sender_name
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetBoolean(msg,"snameenf",snameenf); //sender_name enforced
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

//    status = tibemsMapMsg_SetByte(msg,"mtr",NULL);
//    if (status != TIBEMS_OK)
//    {
//        fail(status);
//    }

    status = tibemsMsg_SetBooleanProperty(msg,"JMS_TIBCO_MSG_EXT",TIBEMS_TRUE);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    sendRequest(18, &msg, TIBEMS_TRUE);

    /* destroy the message */
    status = tibemsMsg_Destroy(msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }
    RETURN_TRUE;
}

PHP_FUNCTION(tibcoadm_updatetopic)
{
    tibems_status status = TIBEMS_OK;
    tibemsMapMsg  msg    = NULL;
    char*         destName;
    int           destName_len = 0;
    int           prefetch = 64;
    int           overview = 0;
    long          maxbytes = 0;
    long          maxmsgs = 0;
    long          expiration = 0;
    long          flowcontrol = 0;
    tibems_bool   failsafe = TIBEMS_FALSE;
    tibems_bool   secure = TIBEMS_FALSE;
    tibems_bool   global = TIBEMS_FALSE;
    tibems_bool   sname = TIBEMS_FALSE;
    tibems_bool   snameenf = TIBEMS_FALSE;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|llllllbbbbb", &destName, &destName_len, &prefetch, &overview, &maxbytes, &maxmsgs, &expiration, &flowcontrol, &failsafe, &secure, &global, &sname, &snameenf) == FAILURE) {
        RETURN_NULL();
    }

    /* create message */
    status = tibemsMapMsg_Create(&msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetString(msg,"dn",destName);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetInt(msg,"dt",2);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetInt(msg,"pf",prefetch); //prefetch
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetInt(msg,"op",overview); //overview policy
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetLong(msg,"mb",maxbytes); //maxbytes
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetLong(msg,"mm",maxmsgs); //maxmsgs
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetLong(msg,"fcs",flowcontrol); //flowControl
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetLong(msg,"expy",expiration); //expiration
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetBoolean(msg,"failsafe",failsafe); //failsafe
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetBoolean(msg,"secure",secure); //secure
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetBoolean(msg,"global",global); //global
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetBoolean(msg,"sname",sname); //sender_name
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetBoolean(msg,"snameenf",snameenf); //sender_name enforced
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

//    status = tibemsMapMsg_SetByte(msg,"mtr",NULL);
//    if (status != TIBEMS_OK)
//    {
//        fail(status);
//    }

    status = tibemsMsg_SetBooleanProperty(msg,"JMS_TIBCO_MSG_EXT",TIBEMS_TRUE);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    sendRequest(13, &msg, TIBEMS_TRUE);

    /* destroy the message */
    status = tibemsMsg_Destroy(msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }
    RETURN_TRUE;
}

PHP_FUNCTION(tibcoadm_getqueues)
{
    tibems_status status = TIBEMS_OK;
    tibemsMapMsg  msg    = NULL;
    char*         destName;
    int           destName_len = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|s", &destName, &destName_len) == FAILURE) {
        RETURN_NULL();
    }

    /* create message */
    status = tibemsMapMsg_Create(&msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    if (destName_len > 0)
    {
	status = tibemsMapMsg_SetString(msg,"pattern",destName);
	if (status != TIBEMS_OK)
        {
            fail(status);
        }
    }

    status = tibemsMapMsg_SetInt(msg,"dt",1);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetBoolean(msg,"ia",TIBEMS_TRUE);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    sendRequest(12, &msg, TIBEMS_TRUE);

    array_init(return_value);

    mapMsgToZendArray(msg, return_value);

    /* destroy the message */
    status = tibemsMsg_Destroy(msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }
}

PHP_FUNCTION(tibcoadm_removequeue)
{
    tibems_status status = TIBEMS_OK;
    tibemsMapMsg  msg    = NULL;
    char*         destName;
    int           destName_len = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &destName, &destName_len) == FAILURE) {
        RETURN_NULL();
    }

    /* create message */
    status = tibemsMapMsg_Create(&msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetString(msg,"dn",destName);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetInt(msg,"dt",1);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    sendRequest(16, &msg, TIBEMS_TRUE);

    /* destroy the message */
    status = tibemsMsg_Destroy(msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }
    RETURN_TRUE;
}

PHP_FUNCTION(tibcoadm_purgequeue)
{
    tibems_status status = TIBEMS_OK;
    tibemsMapMsg  msg    = NULL;
    char*         destName;
    int           destName_len = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &destName, &destName_len) == FAILURE) {
        RETURN_NULL();
    }

    /* create message */
    status = tibemsMapMsg_Create(&msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetString(msg,"pattern",destName);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetInt(msg,"dt",1);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    sendRequest(15, &msg, TIBEMS_TRUE);

    /* destroy the message */
    status = tibemsMsg_Destroy(msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }
    RETURN_TRUE;
}

PHP_FUNCTION(tibcoadm_createqueue)
{
    tibems_status status = TIBEMS_OK;
    tibemsMapMsg  msg    = NULL;
    char*         destName;
    int           destName_len = 0;
    int           prefetch = 5;
    int           overview = 0;
    int           redelivery = 0;
    long          maxbytes = 0;
    long          maxmsgs = 0;
    long          expiration = 0;
    long          flowcontrol = 0;
    tibems_bool   failsafe = TIBEMS_FALSE;
    tibems_bool   secure = TIBEMS_FALSE;
    tibems_bool   global = TIBEMS_FALSE;
    tibems_bool   sname = TIBEMS_FALSE;
    tibems_bool   snameenf = TIBEMS_FALSE;
    tibems_bool   exclusive = TIBEMS_FALSE;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|lllllllbbbbbb", &destName, &destName_len, &prefetch, &overview, &redelivery, &maxbytes, &maxmsgs, &expiration, &flowcontrol, &failsafe, &secure, &global, &sname, &snameenf, &exclusive) == FAILURE) {
        RETURN_NULL();
    }

    /* create message */
    status = tibemsMapMsg_Create(&msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetString(msg,"dn",destName);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetInt(msg,"dt",1);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetInt(msg,"pf",prefetch); //prefetch
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetInt(msg,"op",overview); //overview policy
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetInt(msg,"mrd",redelivery); //max redelivery
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetLong(msg,"mb",maxbytes); //maxbytes
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetLong(msg,"mm",maxmsgs); //maxmsgs
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetLong(msg,"fcs",flowcontrol); //flowControl
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetLong(msg,"expy",expiration); //expiration
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetBoolean(msg,"failsafe",failsafe); //failsafe
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetBoolean(msg,"secure",secure); //secure
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetBoolean(msg,"global",global); //global
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetBoolean(msg,"sname",sname); //sender_name
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetBoolean(msg,"snameenf",snameenf); //sender_name enforced
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetBoolean(msg,"exclusive",exclusive); //exclusive
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

//    status = tibemsMapMsg_SetByte(msg,"mtr",NULL);
//    if (status != TIBEMS_OK)
//    {
//        fail(status);
//    }

    status = tibemsMsg_SetBooleanProperty(msg,"JMS_TIBCO_MSG_EXT",TIBEMS_TRUE);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    sendRequest(18, &msg, TIBEMS_TRUE);

    /* destroy the message */
    status = tibemsMsg_Destroy(msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }
    RETURN_TRUE;
}

PHP_FUNCTION(tibcoadm_updatequeue)
{
    tibems_status status = TIBEMS_OK;
    tibemsMapMsg  msg    = NULL;
    char*         destName;
    int           destName_len = 0;
    int           prefetch = 5;
    int           overview = 0;
    int           redelivery = 0;
    long          maxbytes = 0;
    long          maxmsgs = 0;
    long          expiration = 0;
    long          flowcontrol = 0;
    tibems_bool   failsafe = TIBEMS_FALSE;
    tibems_bool   secure = TIBEMS_FALSE;
    tibems_bool   global = TIBEMS_FALSE;
    tibems_bool   sname = TIBEMS_FALSE;
    tibems_bool   snameenf = TIBEMS_FALSE;
    tibems_bool   exclusive = TIBEMS_FALSE;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|lllllllbbbbbb", &destName, &destName_len, &prefetch, &overview, &redelivery, &maxbytes, &maxmsgs, &expiration, &flowcontrol, &failsafe, &secure, &global, &sname, &snameenf, &exclusive) == FAILURE) {
        RETURN_NULL();
    }

    /* create message */
    status = tibemsMapMsg_Create(&msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetString(msg,"dn",destName);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetInt(msg,"dt",1);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetInt(msg,"pf",prefetch); //prefetch
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetInt(msg,"op",overview); //overview policy
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetInt(msg,"mrd",redelivery); //max redelivery
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetLong(msg,"mb",maxbytes); //maxbytes
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetLong(msg,"mm",maxmsgs); //maxmsgs
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetLong(msg,"fcs",flowcontrol); //flowControl
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetLong(msg,"expy",expiration); //expiration
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetBoolean(msg,"failsafe",failsafe); //failsafe
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetBoolean(msg,"secure",secure); //secure
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetBoolean(msg,"global",global); //global
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetBoolean(msg,"sname",sname); //sender_name
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetBoolean(msg,"snameenf",snameenf); //sender_name enforced
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetBoolean(msg,"exclusive",exclusive); //exclusive
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

//    status = tibemsMapMsg_SetByte(msg,"mtr",NULL);
//    if (status != TIBEMS_OK)
//    {
//        fail(status);
//    }

    status = tibemsMsg_SetBooleanProperty(msg,"JMS_TIBCO_MSG_EXT",TIBEMS_TRUE);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    sendRequest(13, &msg, TIBEMS_TRUE);

    /* destroy the message */
    status = tibemsMsg_Destroy(msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }
    RETURN_TRUE;
}

PHP_FUNCTION(tibcoadm_removeuser)
{
    tibems_status status = TIBEMS_OK;
    tibemsMapMsg  msg    = NULL;
    char*         userName;
    int           userName_len = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &userName, &userName_len) == FAILURE) {
        RETURN_NULL();
    }

    /* create message */
    status = tibemsMapMsg_Create(&msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetString(msg,"name",userName);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    sendRequest(45, &msg, TIBEMS_TRUE);

    /* destroy the message */
    status = tibemsMsg_Destroy(msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }
    RETURN_TRUE;
}

PHP_FUNCTION(tibcoadm_createuser)
{
    tibems_status status = TIBEMS_OK;
    tibemsMapMsg  msg    = NULL;
    char*         userName;
    int           userName_len = 0;
    char*         userPassword;
    int           userPassword_len = 0;
    char*         userDesc;
    int           userDesc_len = 0;
    char*         mangPassword;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss|s", &userName, &userName_len, &userPassword, &userPassword_len, &userDesc, &userDesc_len) == FAILURE) {
        RETURN_NULL();
    }

    /* create message */
    status = tibemsMapMsg_Create(&msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetString(msg,"name",userName);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    mangPassword = manglePassword(userPassword, false, &userPassword_len);
    status = tibemsMapMsg_SetBytes(msg,"password",mangPassword,userPassword_len);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    if(userDesc_len > 0) {
        status = tibemsMapMsg_SetString(msg,"desc",userDesc);
        if (status != TIBEMS_OK)
        {
            fail(status);
        }
    }

    sendRequest(40, &msg, TIBEMS_TRUE);

    /* destroy the message */
    status = tibemsMsg_Destroy(msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }
    RETURN_TRUE;
}

PHP_FUNCTION(tibcoadm_edituser)
{
    tibems_status status = TIBEMS_OK;
    tibemsMapMsg  msg    = NULL;
    char*         userName;
    int           userName_len = 0;
    char*         userPassword;
    int           userPassword_len = 0;
    char*         userDesc;
    int           userDesc_len = 0;
    char*         mangPassword;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss|s", &userName, &userName_len, &userPassword, &userPassword_len, &userDesc, &userDesc_len) == FAILURE) {
        RETURN_NULL();
    }

    /* create message */
    status = tibemsMapMsg_Create(&msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    status = tibemsMapMsg_SetString(msg,"name",userName);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    mangPassword = manglePassword(userPassword, false, &userPassword_len);
    status = tibemsMapMsg_SetBytes(msg,"password",mangPassword,userPassword_len);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    if(userDesc_len > 0) {
        status = tibemsMapMsg_SetString(msg,"desc",userDesc);
        if (status != TIBEMS_OK)
        {
            fail(status);
        }
    }

    sendRequest(42, &msg, TIBEMS_TRUE);

    /* destroy the message */
    status = tibemsMsg_Destroy(msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }
    RETURN_TRUE;
}

PHP_FUNCTION(tibcoadm_getusers)
{
    tibems_status status = TIBEMS_OK;
    tibemsMapMsg  msg    = NULL;

    /* create message */
    status = tibemsMapMsg_Create(&msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    sendRequest(43, &msg, TIBEMS_TRUE);

    array_init(return_value);

    mapMsgToZendArray(msg, return_value);

    /* destroy the message */
    status = tibemsMsg_Destroy(msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }
}

PHP_FUNCTION(tibcoadm_getstatus)
{
    tibems_status status = TIBEMS_OK;
    tibemsMapMsg  msg     = NULL;
    char         *sstate;
    const char   *server;
    int           pid, state, queuenum, topicnum, connnum, sessnum, prodnum, consnum, durablenum;
    tibems_long   pendcount, pendsize, inrm, outrm;

    /* create message */
    status = tibemsMapMsg_Create(&msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    sendRequest(120, &msg, TIBEMS_TRUE);

    array_init(return_value);

    mapMsgToZendArray(msg, return_value);

    /* destroy the message */
    status = tibemsMsg_Destroy(msg);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }
}

PHP_FUNCTION(tibcoadm_connect)
{

    tibems_status status = TIBEMS_OK;
    char *tmpvalue, *serverValue;

    char*           serverUrl     = "<$admin>:";
    int             serverUrl_len = 0;
    char*           userName      = "admin";
    int             userName_len  = 0;
    char*           password      = NULL;
    int             password_len  = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sss", &serverValue, &serverUrl_len, &userName, &userName_len, &password, &password_len) == FAILURE) {
        RETURN_NULL();
    }

    tmpvalue = (char *)ecalloc(strlen(serverUrl) + strlen(serverValue) + 1, sizeof(char));
    strcat(tmpvalue, serverUrl);
    strcat(tmpvalue, serverValue);
    serverUrl = (char *)ecalloc(strlen(tmpvalue) + 1, sizeof(char));
    strcpy(serverUrl, tmpvalue);
    serverUrl_len = strlen(serverUrl);

    factory = tibemsConnectionFactory_Create();
    if (!factory)
    {
        printf("Error creating tibemsConnectionFactory");
        exit(1);
    }

    status = tibemsConnectionFactory_SetType(factory, TIBEMS_QUEUE_CONNECTION_FACTORY);
    if (status != TIBEMS_OK) 
    {
        fail(status);
    }

    status = tibemsConnectionFactory_SetServerURL(factory,serverUrl);
    if (status != TIBEMS_OK) 
    {
        fail(status);
    }

    status = tibemsQueueConnectionFactory_CreateConnection(factory,&queueConnection,
                                                           userName,password);
    if (status != TIBEMS_OK)
    {
        if(status == TIBEMS_SECURITY_EXCEPTION || status == TIBEMS_SERVER_NOT_CONNECTED || status == TIBEMS_INVALID_HOSTNAME)
        {
            RETURN_FALSE;
        }
        fail(status);
    }

    /* create the queue session */
    status = tibemsQueue_Create(&queue,queueName);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    /* create the queue session */
    status = tibemsQueueConnection_CreateQueueSession(queueConnection,
            &queueSession,TIBEMS_FALSE,TIBEMS_NO_ACKNOWLEDGE);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    /* create the queue sender */
    status = tibemsQueueSession_CreateSender(queueSession,
            &queueSender,queue);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    /* create the temp queue */
    status = tibemsSession_CreateTemporaryQueue(queueSession,
                &tmpQueue);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    /* create the queue receiver */
    status = tibemsQueueSession_CreateReceiver(queueSession,
            &queueReceiver,tmpQueue,NULL);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    /* start the connection */
    status = tibemsConnection_Start(queueConnection);
    if (status != TIBEMS_OK)
    {
        fail(status);
    }

    efree(serverUrl);
    efree(tmpvalue);

    RETURN_TRUE;
}
