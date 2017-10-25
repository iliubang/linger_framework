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

#ifndef LINGER_VIEW_H_
#define LINGER_VIEW_H_

zval *linger_view_instance();
int linger_view_assign(zval *this, char *key, zval *val TSRMLS_DC);
zval *linger_view_getVars(zval *this TSRMLS_DC);
int linger_view_render(zval *this, zval *tpl, zval *ret TSRMLS_DC);
int linger_view_display(zval *this, zval *tpl, zval *ret TSRMLS_DC);

#endif /* LINGER_VIEW_H_ */
