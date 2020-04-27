/**
 * \file TreeLib.cpp
 *
 * \author Charles Owen
 */


#include "pch.h"
#include "TreeLib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


BEGIN_MESSAGE_MAP(CTreeLibApp, CWinApp)
END_MESSAGE_MAP()


/**
 * Constructor
 */
CTreeLibApp::CTreeLibApp()
{
}


/// The one and only CTreeLibApp object
CTreeLibApp theApp;


/**
 * CTreeLibApp initialization
 * \returns 
 */
BOOL CTreeLibApp::InitInstance()
{
	CWinApp::InitInstance();
    srand((unsigned int)time(nullptr));
	return TRUE;
}

