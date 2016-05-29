/*
   +----------------------------------------------------------------------+
   | PHP Version 5                                                        |
   +----------------------------------------------------------------------+
   | Copyright (c) 1997-2004 The PHP Group                                |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.0 of the PHP license,       |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_0.txt.                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Authors: Wez Furlong <wez@thebrainroom.com>                          |
   +----------------------------------------------------------------------+
 */
/* $Id$ */

#include "php.h"
#include "php_main.h"
#include "SAPI.h"
#include "php_globals.h"
#include "ext/standard/info.h"
#include "php_variables.h"
#include "php_ini.h"
#include "php5activescript.h"

/* SAPI definitions and DllMain */

static int php_activescript_startup(sapi_module_struct *sapi_module)
{
	if (php_module_startup(sapi_module, &php_activescript_module, 1) == FAILURE) {
		return FAILURE;
	} else {
		return SUCCESS;
	}
}

static int sapi_activescript_ub_write(const char *str, uint str_length TSRMLS_DC)
{
	/* In theory, this is a blackhole.  In practice, I want to see the output
	 * in the debugger! */
#if ZEND_DEBUG
	char buf[1024];
	uint l, a = str_length;

	while(a) {
		l = a;
		if (l > sizeof(buf) - 1)
			l = sizeof(buf) - 1;
		memcpy(buf, str, l);
		buf[l] = 0;
		OutputDebugString(buf);
		a -= l;
	}
#endif
	return str_length;
}

static void init_request_info( TSRMLS_D)
{
   /*
    sapi_cgibin_putenv("PATH_INFO", "d:\\noname2.php" TSRMLS_CC);
  
  	// Build the special-case PHP_SELF variable for the CLI version //
 	sapi_cgibin_putenv("PHP_SELF", "d:\\noname2.php"   TSRMLS_CC);
    sapi_cgibin_putenv("SCRIPT_NAME", "d:\\noname2.php"   TSRMLS_CC);
	// filenames are empty for stdin //
  	sapi_cgibin_putenv("SCRIPT_FILENAME", "d:\\noname2.php"   TSRMLS_CC);
 	sapi_cgibin_putenv("PATH_TRANSLATED", "d:\\noname2.php"  TSRMLS_CC);
	// just make it available //
    //sapi_cgibin_putenv("DOCUMENT_ROOT", "",   TSRMLS_CC);
    sapi_cgibin_putenv("LOCAL_ADDR", "127.0.0.1"  TSRMLS_CC);
    sapi_cgibin_putenv("REMOTE_ADDR", "127.0.0.1"  TSRMLS_CC);
     sapi_cgibin_putenv("REMOTE_HOST", "127.0.0.1"  TSRMLS_CC);  
	 sapi_cgibin_putenv("HTTP_X_REWRITE_URL", "d:\\noname2.php?DBGSESSID=1@clienthost%3A7869%3Bd%3D1%2Cp%3D1&"  TSRMLS_CC); 
	 sapi_cgibin_putenv("QUERY_STRING","DBGSESSID=1@clienthost%3A7869%3Bd%3D1%2Cp%3D1&"  TSRMLS_CC);
     sapi_cgibin_putenv("HTTP_COOKIE", "DBGSESSID=1@clienthost:7869"  TSRMLS_CC);
*/
 
}
static void sapi_activescript_register_server_variables(zval *track_vars_array TSRMLS_DC)
{
     /*
    // char *env_path_info = "d:\\noname203.php";
    // env_path_info = sapi_cgibin_putenv("PATH_INFO", env_path_info TSRMLS_CC);

    init_request_info( TSRMLS_C); 
 	php_import_environment_variables(track_vars_array TSRMLS_CC);


   //	init_request_info(TSRMLS_C);

	// Build the special-case PHP_SELF variable for the CLI version  //
 	php_register_variable("PHP_SELF", "d:\\noname1.php", track_vars_array TSRMLS_CC);
    php_register_variable("SCRIPT_NAME", "d:\\noname1.php", track_vars_array TSRMLS_CC);
	// filenames are empty for stdin //
  	php_register_variable("SCRIPT_FILENAME", "d:\\noname1.php", track_vars_array TSRMLS_CC);
 	php_register_variable("PATH_TRANSLATED", "d:\\noname1.php", track_vars_array TSRMLS_CC);
	// just make it available //
    php_register_variable("DOCUMENT_ROOT", "", track_vars_array TSRMLS_CC);
     php_register_variable("QUERY_STRING","DBGSESSID=1@clienthost%3A7869%3Bd%3D1%2Cp%3D1&",  track_vars_array TSRMLS_CC);
 
   // php_register_variable_safe("PHP_SELF", "2222", 5, track_vars_array TSRMLS_CC);
      
   
   */
  return ;
}

static char *sapi_activescript_read_cookies(TSRMLS_D)
{
  //return "DBGSESSID=1@clienthost:7869";
	return NULL;
}

static int sapi_activescript_header_handler(sapi_header_struct *sapi_header, sapi_headers_struct *sapi_headers TSRMLS_DC)
{
	return SAPI_HEADER_ADD;
}

static int sapi_activescript_send_headers(sapi_headers_struct *sapi_headers TSRMLS_DC)
{
	return SAPI_HEADER_SENT_SUCCESSFULLY;
}

static char *sapi_cgibin_getenv(char *name, size_t name_len TSRMLS_DC)
{	/*  if cgi, or fastcgi and not found in fcgi env
		check the regular environment */
	return getenv(name);
}
static char *sapi_cgibin_putenv(char *name, char *value TSRMLS_DC)
{
	int name_len;
#if !HAVE_SETENV || !HAVE_UNSETENV
	int len;
	char *buf;
#endif

	if (!name) {
		return NULL;
	}
	name_len = strlen(name);

 
#if HAVE_SETENV 
	if (value) {
		setenv(name, value, 1);
	}
#endif
#if HAVE_UNSETENV
	if (!value) {
		unsetenv(name);
	}
#endif

#if !HAVE_SETENV || !HAVE_UNSETENV
	/*  if cgi, or fastcgi and not found in fcgi env
		check the regular environment 
		this leaks, but it's only cgi anyway, we'll fix
		it for 5.0
	*/
	len = name_len + (value ? strlen(value) : 0) + sizeof("=") + 2;
	buf = (char *) malloc(len);
	if (buf == NULL) {
		return getenv(name);
	}
#endif
#if !HAVE_SETENV
	if (value) {
		len = slprintf(buf, len - 1, "%s=%s", name, value);
		putenv(buf); 
	}
#endif
#if !HAVE_UNSETENV
	if (!value) {
		len = slprintf(buf, len - 1, "%s=", name);
		putenv(buf);
	}
#endif
	return getenv(name);
}

zend_module_entry php_activescript_module = {
    STANDARD_MODULE_HEADER,
	"PDAinterface",
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
    NULL,
	STANDARD_MODULE_PROPERTIES
};


sapi_module_struct activescript_sapi_module = {
	"pdascript",						/* name */
	"PDAScript",					/* pretty name */
									
	php_activescript_startup,				/* startup */
	php_module_shutdown_wrapper,	/* shutdown */

	NULL,							/* activate */
	NULL,							/* deactivate */

	sapi_activescript_ub_write,			/* unbuffered write */
	NULL,							/* flush */
	NULL,							/* get uid */
	sapi_cgibin_getenv,							/* getenv */

	zend_error,						/* error handler */

	sapi_activescript_header_handler,		/* header handler */
	sapi_activescript_send_headers,		/* send headers handler */
	NULL,							/* send header handler */

	NULL,			/* read POST data */
	sapi_activescript_read_cookies,		/* read Cookies */

	sapi_activescript_register_server_variables,	/* register server variables */
	NULL,									/* Log message */

	STANDARD_SAPI_MODULE_PROPERTIES
};

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	switch (fdwReason) {
		case DLL_PROCESS_ATTACH:
			module_handle = hinstDLL;

			tsrm_startup(128, 32, TSRM_ERROR_LEVEL_CORE, "C:\\TSRM.log");

			/* useful behaviour for the host: we take the application path
			 * and use that dir as the override for the php.ini, so that
			 * we don't pick up a global .ini file */
			{
				char module_dir[MAXPATHLEN];
				char *slash;

				GetModuleFileName(0, module_dir, sizeof(module_dir));
				slash = strrchr(module_dir, '\\');
				if (slash) {
					slash[1] = '\0';
				}

				activescript_sapi_module.php_ini_path_override = strdup(module_dir);
			}
			
			sapi_startup(&activescript_sapi_module);
			if (activescript_sapi_module.startup) {
				activescript_sapi_module.startup(&sapi_module);
			}
			break;
		case DLL_THREAD_ATTACH:
			break;
		case DLL_THREAD_DETACH:
			//OutputDebugString("THREAD_DETACH\n");
			ts_free_thread();
			break;
		case DLL_PROCESS_DETACH:
			if (activescript_sapi_module.shutdown) {
				activescript_sapi_module.shutdown(&sapi_module);
			}
			//OutputDebugString("PROCESS_DETACH\n");
			sapi_shutdown();
			tsrm_shutdown();
			break;
	}
	return TRUE;
}


