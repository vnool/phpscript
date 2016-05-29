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

#ifndef __php5as_classfactory_h__
#define __php5as_classfactory_h__
/* IClassFactory Implementation */

#include <unknwn.h>

// {CF108A38-59A9-468a-AF45-1368D7855DAE}
DEFINE_GUID(CLSID_PHPActiveScriptEngine,
0xcf108a38, 0x59a9, 0x468a, 0xaf, 0x45, 0x13, 0x68, 0xd7, 0x85, 0x5d, 0xae);

// {AD504760-D6B9-4537-AEAC-512FFB359009}
DEFINE_GUID(CLSID_PHPActiveScriptEngineMarshal,
0xad504760, 0xd6b9, 0x4537, 0xae, 0xac, 0x51, 0x2f, 0xfb, 0x35, 0x90, 0x9);

#if 0
/* this was for PHP 4 */
// {A0AD8E7A-95EC-4819-986F-78D93895F2AE}
DEFINE_GUID(CLSID_PHPActiveScriptEngine, 
0xa0ad8e7a, 0x95ec, 0x4819, 0x98, 0x6f, 0x78, 0xd9, 0x38, 0x95, 0xf2, 0xae);
#endif

class TPHPClassFactory:
	public IClassFactory
{
protected:
	volatile LONG m_refcount;

	static volatile LONG factory_count;
	static volatile LONG object_count;
	
public: /* IUnknown */
	STDMETHODIMP QueryInterface(REFIID iid, void **ppvObject);
	STDMETHODIMP_(DWORD) AddRef(void);
	STDMETHODIMP_(DWORD) Release(void);
public: /* IClassFactory */
	STDMETHODIMP CreateInstance(IUnknown *pUnkOuter, REFIID iid, void **ppvObject);
	STDMETHODIMP LockServer(BOOL fLock);

	TPHPClassFactory();
	~TPHPClassFactory();

	static void AddToObjectCount(void);
	static void RemoveFromObjectCount(void);
	static int CanUnload(void);
};

#endif //__php5as_classfactory_h__
