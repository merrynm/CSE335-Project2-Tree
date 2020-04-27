/**
 * \file TreeDemoDlg.h
 * The tree demostration dialog box class
 * \author Charles Owen
 */


#pragma once
#include "afxcmn.h"
#include "afxwin.h"

#include "TreeDemoView.h"

/**
 * The tree demostration dialog box class
 */
class CTreeDemoDlg : public CDialogEx
{
public:
	CTreeDemoDlg(CWnd* pParent = NULL);	// standard constructor

    /// Dialog box ID
	enum { IDD = IDD_TREEDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;  ///< Icon handle

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnBnClickedButtonnewtree();

private:
    int mFrameNum = 0;      ///< Frame number, assumed 30 frames per second
    double mWindSpeed = 0;  ///< Wind speed in mile per hour

    void UpdateUI();
    CSliderCtrl mTimeSlider;    ///< The time/frame slider
    CStatic mFrame;             ///< Current frame
        
    CTreeDemoView mTreeView;    ///< The tree viewer window
    CSliderCtrl mWindSlider;    ///< The wind speed slider
   
    CStatic mSeedView;          ///< View were we put the tree seed

public:
    afx_msg void OnBnClickedButtonharvest();
    afx_msg void OnBnClickedButtonempty();
};
