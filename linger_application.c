/*
  +----------------------------------------------------------------------+
  | linger_framework                                                     |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2016 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: liubang <it.liubang@gmail.com>                               |
  +----------------------------------------------------------------------+
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_linger_framework.h"
#include "linger_application.h"

/* class entry */
zend_class_entry *application_ce;


PHP_METHOD(linger_framework_application, __construct)
{
    zval *app,
         *aconfig = NULL,
    zconfig = {{0}},
    zrouter = {{0}},
    zrequest = {{0}},
    zresponse = {{0}},
    zdispatcher = {{0}};

    app = zend_read_static_property(application_ce, ZEND_STRL(APPLICATION_PROPERTIES_APP), 1);

    if (!ZVAL_IS_NULL(app)) {
        linger_throw_exception(NULL, 0, "can not reinstance application.");
        RETURN_FALSE;
    }

    if (zend_parse_parameters_throw(ZEND_NUM_ARGS(), "z", &aconfig) != SUCCESS) {
        return;
    }

    if (!aconfig || Z_TYPE_P(aconfig) != IS_ARRAY) {
        linger_throw_exception(NULL, 0, "config must be an array.");
        RETURN_FALSE;
    }

    zval *self = getThis();
    zend_update_static_property(application_ce, ZEND_STRL(APPLICATION_PROPERTIES_APP), self);

    // init config
    (void)linger_config_instance(&zconfig, aconfig);
    zend_update_property(application_ce, self, ZEND_STRL(APPLICATION_PROPERTIES_CONFIG), &zconfig);
    zval_ptr_dtor(&zconfig);

    // TODO instance request, router, dispatcher
}

PHP_METHOD(linger_framework_application, init)
{

}

PHP_METHOD(linger_framework_application, run)
{

}

PHP_METHOD(linger_framework_application, app)
{
    zval *app = zend_read_static_property(application_ce, ZEND_STRL(APPLICATION_PROPERTIES_APP), 1);
    RETURN_ZVAL(app, 1, 0);
}

PHP_METHOD(linger_framework_application, getConfig)
{
    zval *config = zend_read_property(application_ce, getThis(), ZEND_STRL(APPLICATION_PROPERTIES_CONFIG), 1, NULL);
    RETURN_ZVAL(config, 1, 0);
}

PHP_METHOD(linger_framework_application, getRouter)
{
    zval *router = zend_read_property(application_ce, getThis(), ZEND_STRL(APPLICATION_PROPERTIES_ROUTER), 1, NULL);
    RETURN_ZVAL(router, 1, 0);
}

PHP_METHOD(linger_framework_application, getDispatcher)
{
    zval *dispatcher = zend_read_property(application_ce, getThis(), ZEND_STRL(APPLICATION_PROPERTIES_DISPATCHER), 1, NULL);
    RETURN_ZVAL(dispatcher, 1, 0);
}

PHP_METHOD(linger_framework_application, getRequest)
{
    zval *request = zend_read_property(application_ce, getThis(), ZEND_STRL(APPLICATION_PROPERTIES_REQUEST), 1, NULL);
    RETURN_ZVAL(request, 1, 0);
}

PHP_METHOD(linger_framework_application, __destruct)
{
    zend_update_static_property_null(application_ce, ZEND_STRL(APPLICATION_PROPERTIES_APP));
}

zend_function_entry application_methods[] = {
    PHP_ME(linger_framework_application, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(linger_framework_application, app, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
    PHP_ME(linger_framework_application, init, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(linger_framework_application, run, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(linger_framework_application, getConfig, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(linger_framework_application, getRouter, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(linger_framework_application, getDispatcher, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(linger_framework_application, getRequest, NULL, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

LINGER_MINIT_FUNCTION(application)
{
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "Linger\\Framework\\Application", application_methods);
    application_ce = zend_register_internal_class_ex(&ce, NULL);
    application_ce->ce_flags |= ZEND_ACC_FINAL;

    zend_declare_property_null(application_ce, ZEND_STRL(APPLICATION_PROPERTIES_APP), ZEND_ACC_PROTECTED | ZEND_ACC_STATIC);
    zend_declare_property_null(application_ce, ZEND_STRL(APPLICATION_PROPERTIES_CONFIG), ZEND_ACC_PROTECTED);
    zend_declare_property_null(application_ce, ZEND_STRL(APPLICATION_PROPERTIES_ROUTER), ZEND_ACC_PROTECTED);
    zend_declare_property_null(application_ce, ZEND_STRL(APPLICATION_PROPERTIES_REQUEST), ZEND_ACC_PROTECTED);
    zend_declare_property_null(application_ce, ZEND_STRL(APPLICATION_PROPERTIES_DISPATCHER), ZEND_ACC_PROTECTED);

    return SUCCESS;
}
