/**
 * \file TreeSeedDlg.cpp
 *
 * \author Charles Owen
 *
 * You are not allowed to change these classes in any way!
 *
*/

#include "pch.h"
#include "TreeLib.h"
#include "TreeSeedDlg.h"
#include "afxdialogex.h"
#include "Tree.h"


/**
 * Open the dialog box as a modal dialog box
 * \returns Dialog box return value
 */
INT_PTR CTreeSeedDlg::DoModal()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    CTreeSeedActualDlg dlg;
    dlg.SetSeed(mTree->GetSeed());
    INT_PTR ret = dlg.DoModal();
    if (ret == IDOK)
    {
        int seed = dlg.GetSeed();
        mTree->SetSeed(seed);
    }
    return ret;
}



/** \cond */
IMPLEMENT_DYNAMIC(CTreeSeedActualDlg, CDialog)

CTreeSeedActualDlg::CTreeSeedActualDlg(CWnd* pParent /*=NULL*/)
    : CDialog(IDD_TREEDLG, pParent), mBrushBack(RGB(255, 255, 255))
{

}

INT_PTR CTreeSeedActualDlg::DoModal()
{
   // 
    return CDialog::DoModal();
}

CTreeSeedActualDlg::~CTreeSeedActualDlg()
{
}

void CTreeSeedActualDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDITSEED, mSeed);
}


BEGIN_MESSAGE_MAP(CTreeSeedActualDlg, CDialog)
    ON_BN_CLICKED(IDC_BUTTONRANDOM, &CTreeSeedActualDlg::OnBnClickedButtonrandom)
    ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

/**
 * Constructor
 */
CTreeSeedDlg::CTreeSeedDlg(std::shared_ptr<CTree> tree) : mTree(tree)
{

}


void CTreeSeedActualDlg::OnBnClickedButtonrandom()
{
    mSeed = rand();
    UpdateData(false);
}




BOOL CTreeSeedActualDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}


HBRUSH CTreeSeedActualDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hBrush = NULL;
    switch (nCtlColor)
    {
    case CTLCOLOR_DLG:
        // just return a not NULL brush handle
        hBrush = (HBRUSH)mBrushBack;
        break;

    default:
        // do the default processing
        hBrush = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
        break;
    }
    return hBrush;
}

/** \endcond */
