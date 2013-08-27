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
#ifndef PHP_TIBCOADM_H
#define PHP_TIBCOADM_H 1

#ifdef ZTS
#include "TSRM.h"
#endif

ZEND_BEGIN_MODULE_GLOBALS(tibcoadm)
    int arseq;
ZEND_END_MODULE_GLOBALS(tibcoadm)

#ifdef ZTS
#define TIBCOADM_G(v) TSRMG(tibcoadm_globals_id, zend_tibcoadm_globals *, v)
#else
#define TIBCOADM_G(v) (tibcoadm_globals.v)
#endif

#ifdef __MVS__  /* TIBEMSOS_ZOS  */
#include <tibems.h>
#else
#include <tibems/tibems.h>
#endif

#include <sys/timeb.h>
#include <stdbool.h>
#include "base64.h"

#define PHP_TIBCOADM_VERSION "0.9.7beta"
#define PHP_TIBCOADM_EXTNAME "tibcoadm"

#define THREAD_RETVAL         void*
#define THREAD_OBJ            pthread_t
#define THREAD_CREATE(t,f,a)  pthread_create(&(t),NULL,(f),(a))

#define is_bigendian() ( (*(char*)&i) == 0 )

PHP_MINIT_FUNCTION(tibcoadm);
PHP_MSHUTDOWN_FUNCTION(tibcoadm);
PHP_RINIT_FUNCTION(tibcoadm);
PHP_RSHUTDOWN_FUNCTION(tibcoadm);
PHP_MINFO_FUNCTION(tibcoadm);

PHP_FUNCTION(tibcoadm_version);
PHP_FUNCTION(tibcoadm_getstatus);
PHP_FUNCTION(tibcoadm_getusers);
PHP_FUNCTION(tibcoadm_createuser);
PHP_FUNCTION(tibcoadm_removeuser);
PHP_FUNCTION(tibcoadm_edituser);
PHP_FUNCTION(tibcoadm_getpermissions);
PHP_FUNCTION(tibcoadm_getqueues);
PHP_FUNCTION(tibcoadm_createqueue);
PHP_FUNCTION(tibcoadm_updatequeue);
PHP_FUNCTION(tibcoadm_removequeue);
PHP_FUNCTION(tibcoadm_purgequeue);
PHP_FUNCTION(tibcoadm_gettopics);
PHP_FUNCTION(tibcoadm_createtopic);
PHP_FUNCTION(tibcoadm_updatetopic);
PHP_FUNCTION(tibcoadm_removetopic);
PHP_FUNCTION(tibcoadm_purgetopic);
PHP_FUNCTION(tibcoadm_getdurables);
PHP_FUNCTION(tibcoadm_createdurable);
PHP_FUNCTION(tibcoadm_removedurable);
PHP_FUNCTION(tibcoadm_purgedurable);
PHP_FUNCTION(tibcoadm_getgroups);
PHP_FUNCTION(tibcoadm_getgroup);
PHP_FUNCTION(tibcoadm_creategroup);
PHP_FUNCTION(tibcoadm_removegroup);
PHP_FUNCTION(tibcoadm_addmember);
PHP_FUNCTION(tibcoadm_removemember);
PHP_FUNCTION(tibcoadm_getroutes);
PHP_FUNCTION(tibcoadm_getacls);
PHP_FUNCTION(tibcoadm_getconnections);
PHP_FUNCTION(tibcoadm_removeconnection);
PHP_FUNCTION(tibcoadm_getjndinames);
PHP_FUNCTION(tibcoadm_getfactories);
PHP_FUNCTION(tibcoadm_gettransactions);
PHP_FUNCTION(tibcoadm_committransaction);
PHP_FUNCTION(tibcoadm_rollbacktransaction);
PHP_FUNCTION(tibcoadm_getbridges);
PHP_FUNCTION(tibcoadm_getbridge);
PHP_FUNCTION(tibcoadm_createbridge);
PHP_FUNCTION(tibcoadm_removebridge);
PHP_FUNCTION(tibcoadm_gettransports);
PHP_FUNCTION(tibcoadm_getconsumers);
PHP_FUNCTION(tibcoadm_getproducersstatistics);
PHP_FUNCTION(tibcoadm_gettopicsstatistics);
PHP_FUNCTION(tibcoadm_getqueuesstatistics);
PHP_FUNCTION(tibcoadm_getroutestatistics);

PHP_FUNCTION(tibcoadm_connect);
PHP_FUNCTION(tibcoadm_disconnect);

extern tibems_status
setLookupParams(
    tibemsLookupParams lookup_params,
    int argc, 
    char* argv[]);

extern zend_module_entry tibcoadm_module_entry;
#define phpext_tibcoadm_ptr &tibcoadm_module_entry

#endif
