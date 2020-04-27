/**
 * \file TreeDemoDlg.cpp
 *
 * \author Charles Owen
 */

#include "pch.h"
#include <string>
#include <sstream>

#include "TreeDemo.h"
#include "TreeDemoDlg.h"
#include "TreeSeedDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

/// The bottom border below the tree window in pixels
const int BottomBorder = 100;

/// Maximum wind speed in miles per hour
const double MaxWindSpeed = 70;

/**
 * Constructor
 * \param pParent Parent window (optional)
 */
CTreeDemoDlg::CTreeDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTreeDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

    srand((unsigned int)time(NULL));
}

/**
 * Exchange data between the dialog box and variables
 * \param pDX Data exchange object
 */
void CTreeDemoDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TIMESLIDER, mTimeSlider);
    DDX_Control(pDX, IDC_FRAME, mFrame);
    DDX_Control(pDX, IDC_WINDSLIDER, mWindSlider);
    DDX_Control(pDX, IDC_TREESEED, mSeedView);
}

/** \cond */
BEGIN_MESSAGE_MAP(CTreeDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_WM_HSCROLL()
    ON_WM_SIZE()
    ON_BN_CLICKED(IDC_BUTTONNEWTREE, &CTreeDemoDlg::OnBnClickedButtonnewtree)
    ON_BN_CLICKED(IDC_BUTTONHARVEST, &CTreeDemoDlg::OnBnClickedButtonharvest)
    ON_BN_CLICKED(IDC_BUTTONEMPTY, &CTreeDemoDlg::OnBnClickedButtonempty)
END_MESSAGE_MAP()
/** \endcond */


/**
 * Initialize the dialog box
 * \returns TRUE on success
 */
BOOL CTreeDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

    mTimeSlider.SetRange(0, 300, TRUE);
    mTimeSlider.SetPageSize(30);
    mTimeSlider.SetTicFreq(30);

    mWindSlider.SetRange(0, 100, TRUE);
    mWindSlider.SetPageSize(10);
    mWindSlider.SetTicFreq(10);

   // mTreeView.SetSeed(2);

    CRect rect;
    GetClientRect(&rect);

    mTreeView.Create(this, CRect(0, 0, rect.Width(), rect.Height() - BottomBorder), 1, WS_VISIBLE);

    UpdateUI();

	return TRUE;  // return TRUE  unless you set the focus to a control
}



/**
 * Paint the dialog box
 */
void CTreeDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

/**
 * The system calls this function to obtain the cursor to display while the user drags
 * the minimized window. 
 * \return Cursor handle
 */
HCURSOR CTreeDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





/**
 * Handle a horizontal scroll message
 * \param nSBCode Message code
 * \param nPos Position of the scroll
 * \param pScrollBar Source scroll bar object
 */
void CTreeDemoDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    mFrameNum = mTimeSlider.GetPos();
    mWindSpeed = mWindSlider.GetPos() * MaxWindSpeed / mWindSlider.GetRangeMax();
    UpdateUI();

    CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

/**
 * Update the user interface to match the current object state 
 */
void CTreeDemoDlg::UpdateUI() 
{
    wstringstream str;
    str << "Frame: " << mFrameNum << endl;
    mFrame.SetWindowTextW(str.str().c_str());


    mTreeView.SetFrame(mFrameNum);
    mTreeView.SetWindSpeed(mWindSpeed);

    wstringstream str2;
    str2 << "Seed: " << mTreeView.GetTree()->GetSeed() << endl;
    mSeedView.SetWindowTextW(str2.str().c_str());

}


/**
 * Handle a size message
 * \param nType Type of size request
 * \param cx New width
 * \param cy New height
 */
void CTreeDemoDlg::OnSize(UINT nType, int cx, int cy)
{
    CDialogEx::OnSize(nType, cx, cy);

    CRect rect;
    GetClientRect(&rect);

    if (IsWindow(mTreeView.m_hWnd)) {
        mTreeView.MoveWindow(0, 0, rect.Width(), rect.Height() - BottomBorder);
    }
}
    


/**
 * Handle the New Tree button press
 */
void CTreeDemoDlg::OnBnClickedButtonnewtree()
{
    CTreeSeedDlg dlg(mTreeView.GetTree());
    if (dlg.DoModal() == IDOK) {
        UpdateUI();
        mTreeView.SetFrame(0);
        mTreeView.SetFrame(mFrameNum);
    }
}

/**
 * Handle the Harvest button press 
 */
void CTreeDemoDlg::OnBnClickedButtonharvest()
{
    mTreeView.Harvest();
}

/**
 * Handle the Empty Basket button press
 */
void CTreeDemoDlg::OnBnClickedButtonempty()
{
    mTreeView.EmptyBasket();
}
