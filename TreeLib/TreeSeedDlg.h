/**
 * \file TreeSeedDlg.h
 *
 * \author Charles Owen
 *
 * Class that implements a dialog box for tree seeds
 */

#pragma once

#include <memory>

class CTree;

/**
* Exported dialog box class for entering a tree seed
*
* You can't open a Dialog Box from a remote DLL, so
* this class is a wrapper that creates and calls DoModal
* on the dialog box in this class.
*
* You are not allowed to change this class in any way!
*
* AFX_EXT_CLASS is a Microsoft directive that indicates
* that this class can be used outside the DLL. Do not change
* it or add it to any other classes.
*/
class AFX_EXT_CLASS CTreeSeedDlg
{
public:
    /**
     * Constructor
     * \param tree Tree we are editing the seed for 
     */
    CTreeSeedDlg(std::shared_ptr<CTree> tree);
    INT_PTR DoModal();

private:
    /// Tree we are editing
    std::shared_ptr<CTree> mTree;
};

/**
 * Dialog box class for entering a Tree Seed.
 *
 * This is the actual MFC dialog box class.
 *
 * \cond
 */
class CTreeSeedActualDlg : public CDialog
{
	DECLARE_DYNAMIC(CTreeSeedActualDlg)

public:
	CTreeSeedActualDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTreeSeedActualDlg();

    virtual INT_PTR DoModal() override;

    int GetSeed() { return mSeed; }
    void SetSeed(int seed) { mSeed = seed; }

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButtonrandom();

private:
    int mSeed = 99;

    CBrush mBrushBack;

public:
    virtual BOOL OnInitDialog();
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

/// \endcond
