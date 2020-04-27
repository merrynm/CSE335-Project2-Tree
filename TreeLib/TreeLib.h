/**
 * \file TreeLib.h
 *
 * \author Charles Owen
 *
 * Windows libraries require an application class to register them. 
 */

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


/**
 * Application class
 */
class CTreeLibApp : public CWinApp
{
public:
	CTreeLibApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
