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
#include "php_ini.h"
#include "php_linger_framework.h"
#include "ext/standard/php_string.h"

zend_class_entry *router_rule_ce;

#define ROUTER_RULE_PROPERTIES_REQUEST_METHOD "_request_method"
#define ROUTER_RULE_PROPERTIES_URI            "_uri"
#define ROUTER_RULE_PROPERTIES_CLASS          "_class"
#define ROUTER_RULE_PROPERTIES_CLASS_METHOD   "_class_method"

zval *linger_router_rule_instance(zval *this, zval *request_method, zval *uri, zval *class, zval *class_method TSRMLS_DC)
{
    if (IS_STRING != Z_TYPE_P(request_method)) {
        linger_throw_exception(NULL, 0, "the parameter request_method must be string.");
        return NULL;
    }
    if (IS_STRING != Z_TYPE_P(uri)) {
        linger_throw_exception(NULL, 0, "the parameter uri must be string.");
        return NULL;
    }
    if (IS_STRING != Z_TYPE_P(class)) {
        linger_throw_exception(NULL, 0, "the parameter class must be string.");
        return NULL;
    }
    if (IS_STRING != Z_TYPE_P(class_method)) {
        linger_throw_exception(NULL, 0, "the parameter class_method must be string.");
        return NULL;
    }

    char *lower_method = zend_str_tolower_dup(Z_STRVAL_P(request_method), Z_STRLEN_P(request_method));
    if (!strncmp(lower_method, "get", 3) ||
            !strncmp(lower_method, "post", 4) ||
            !strncmp(lower_method, "put", 3) ||
            !strncmp(lower_method, "delete", 6)) {
        ZVAL_STRING(request_method, lower_method, 1);
        linger_efree(lower_method);
        zval *instance = NULL;
        if (this) {
            instance = this;
        } else {
            MAKE_STD_ZVAL(instance);
            object_init_ex(instance, router_rule_ce);
        }
        char *trimed_uri = php_trim(Z_STRVAL_P(uri), Z_STRLEN_P(uri), "/", 1, NULL, 3 TSRMLS_CC);
        char *format_uri = NULL;
        int format_uri_len = spprintf(&format_uri, 0, "/%s/", trimed_uri);
        linger_efree(trimed_uri);
        zend_update_property(router_rule_ce, instance, ZEND_STRL(ROUTER_RULE_PROPERTIES_REQUEST_METHOD), request_method TSRMLS_CC);
        zend_update_property_string(router_rule_ce, instance, ZEND_STRL(ROUTER_RULE_PROPERTIES_URI), format_uri TSRMLS_CC);
        zend_update_property(router_rule_ce, instance, ZEND_STRL(ROUTER_RULE_PROPERTIES_CLASS), class TSRMLS_CC);
        zend_update_property(router_rule_ce, instance, ZEND_STRL(ROUTER_RULE_PROPERTIES_CLASS_METHOD), class_method TSRMLS_CC);
        linger_efree(format_uri);
        return instance;
    } else {
        linger_throw_exception(NULL, 0, "invalid http request method:%s.", Z_STRVAL_P(request_method));
        linger_efree(lower_method);
        return NULL;
    }
}

zval *linger_router_rule_get_request_method(zval *this TSRMLS_DC)
{
    if (!this)
        return NULL;
    zval *request_method;
    request_method = zend_read_property(router_rule_ce, this, ZEND_STRL(ROUTER_RULE_PROPERTIES_REQUEST_METHOD), 1 TSRMLS_CC);

    return request_method;
}

zval *linger_router_rule_get_uri(zval *this TSRMLS_DC)
{
    if (!this)
        return NULL;
    zval *uri = NULL;
    uri = zend_read_property(router_rule_ce, this, ZEND_STRL(ROUTER_RULE_PROPERTIES_URI), 1 TSRMLS_CC);

    return uri;
}

zval *linger_router_rule_get_class(zval *this TSRMLS_DC)
{
    if (!this)
        return NULL;
    zval *class = NULL;
    class = zend_read_property(router_rule_ce, this, ZEND_STRL(ROUTER_RULE_PROPERTIES_CLASS), 1 TSRMLS_CC);

    return class;
}

zval *linger_router_rule_get_class_method(zval *this TSRMLS_DC)
{
    if (!this)
        return NULL;
    zval *class_method = NULL;
    class_method = zend_read_property(router_rule_ce, this, ZEND_STRL(ROUTER_RULE_PROPERTIES_CLASS_METHOD), 1 TSRMLS_CC);

    return class_method;
}

PHP_METHOD(linger_framework_router_rule, __construct)
{
    zval *request_method, *uri, *class, *class_method;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zzzz",
                              &request_method, &uri, &class, &class_method) == FAILURE) {
        return;
    }
    linger_router_rule_instance(getThis(), request_method, uri, class, class_method TSRMLS_CC);
}

PHP_METHOD(linger_framework_router_rule, getRequestMethod)
{
    zval *request_method;
    request_method = zend_read_property(router_rule_ce, getThis(), ZEND_STRL(ROUTER_RULE_PROPERTIES_REQUEST_METHOD), 1 TSRMLS_CC);

    RETURN_ZVAL(request_method, 1, 0);
}

PHP_METHOD(linger_framework_router_rule, getUri)
{
    zval *uri;
    uri = zend_read_property(router_rule_ce, getThis(), ZEND_STRL(ROUTER_RULE_PROPERTIES_URI), 1 TSRMLS_CC);

    RETURN_ZVAL(uri, 1, 0);
}

PHP_METHOD(linger_framework_router_rule, getClass)
{
    zval *class;
    class = zend_read_property(router_rule_ce, getThis(), ZEND_STRL(ROUTER_RULE_PROPERTIES_CLASS), 1 TSRMLS_CC);

    RETURN_ZVAL(class, 1, 0);
}

PHP_METHOD(linger_framework_router_rule, getClassMethod)
{
    zval *class_method;
    class_method = zend_read_property(router_rule_ce, getThis(), ZEND_STRL(ROUTER_RULE_PROPERTIES_CLASS_METHOD), 1 TSRMLS_CC);

    RETURN_ZVAL(class_method, 1, 0);
}

zend_function_entry router_rule_methods[] = {
    PHP_ME(linger_framework_router_rule, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(linger_framework_router_rule, getRequestMethod, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(linger_framework_router_rule, getUri, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(linger_framework_router_rule, getClass, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(linger_framework_router_rule, getClassMethod, NULL, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

LINGER_MINIT_FUNCTION(router_rule)
{
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "Linger\\Framework\\RouterRule", router_rule_methods);
    router_rule_ce = zend_register_internal_class(&ce TSRMLS_CC);
    zend_declare_property_null(router_rule_ce, ZEND_STRL(ROUTER_RULE_PROPERTIES_REQUEST_METHOD), ZEND_ACC_PRIVATE TSRMLS_CC);
    zend_declare_property_null(router_rule_ce, ZEND_STRL(ROUTER_RULE_PROPERTIES_URI), ZEND_ACC_PRIVATE TSRMLS_CC);
    zend_declare_property_null(router_rule_ce, ZEND_STRL(ROUTER_RULE_PROPERTIES_CLASS), ZEND_ACC_PRIVATE TSRMLS_CC);
    zend_declare_property_null(router_rule_ce, ZEND_STRL(ROUTER_RULE_PROPERTIES_CLASS_METHOD), ZEND_ACC_PRIVATE TSRMLS_CC);
    return SUCCESS;
}
