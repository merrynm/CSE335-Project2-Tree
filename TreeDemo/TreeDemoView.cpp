/**
 * \file TreeDemoView.cpp
 *
 * \author Charles Owen
 */

#include "pch.h"
#include "TreeDemo.h"
#include "TreeDemoView.h"
#include "DoubleBufferDC.h"
#include "TreeFactory.h"

using namespace Gdiplus;

// Window class name for this view
#define VIEWER_CLASSNAME    _T("CTreeDemoView")  // Window class name

/// Offset of the bottom of view from bottom of parent view in pixels
const int TreeBottomOffset = 10;

IMPLEMENT_DYNAMIC(CTreeDemoView, CWnd)

/**
 * Constructor
 */
CTreeDemoView::CTreeDemoView()
{
    RegisterWindowClass();

    //
    // Use a factory to create the tree and basket objects
    //
    CTreeFactory factory;
    mTree = factory.CreateTree();
    mBasket = factory.CreateBasket();
}

/**
 * Destructor
 */
CTreeDemoView::~CTreeDemoView()
{
}

/**
 * Register this view as  a window
 * \return TRUE if successful
 */
BOOL CTreeDemoView::RegisterWindowClass()
{
    WNDCLASS wndcls;
    HINSTANCE hInst = AfxGetInstanceHandle();

    if (!(::GetClassInfo(hInst, VIEWER_CLASSNAME, &wndcls)))
    {
        // otherwise we need to register a new class
        wndcls.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
        wndcls.lpfnWndProc = ::DefWindowProc;
        wndcls.cbClsExtra = wndcls.cbWndExtra = 0;
        wndcls.hInstance = hInst;
        wndcls.hIcon = NULL;
        wndcls.hCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
        wndcls.hbrBackground = (HBRUSH)(COLOR_3DFACE + 1);
        wndcls.lpszMenuName = NULL;
        wndcls.lpszClassName = VIEWER_CLASSNAME;

        if (!AfxRegisterClass(&wndcls))
        {
            AfxThrowResourceException();
            return FALSE;
        }
    }

    return TRUE;
}


/**
 * Create the view
 * \param pParentWnd Optional parent window
 * \param rect View rectanlge
 * \param nID ID for the view
 * \param dwStyle Window style
 * \returns true if successful
 */
BOOL CTreeDemoView::Create(CWnd* pParentWnd, const RECT& rect, UINT nID, DWORD dwStyle /*=WS_VISIBLE*/)
{
    int rootX = rect.right / 2;
    int rootY = rect.bottom - TreeBottomOffset;
    mTree->SetRootLocation(rootX, rootY);
    mBasket->SetBasketLocation(rect.right / 4, rootY);

    return CWnd::Create(VIEWER_CLASSNAME, _T(""), dwStyle, rect, pParentWnd, nID);
}

/** \cond */
BEGIN_MESSAGE_MAP(CTreeDemoView, CWnd)
    ON_WM_PAINT()
    ON_WM_ERASEBKGND()
END_MESSAGE_MAP()
/** \endcond */


/**
 * Paint the view
 */
void CTreeDemoView::OnPaint()
{
    CPaintDC paintDC(this);     // device context for painting
    CDoubleBufferDC dc(&paintDC); // device context for painting

    Graphics graphics(dc.m_hDC);    // Create GDI+ graphics context

    mTree->DrawTree(&graphics);
    mBasket->DrawBasket(&graphics);
}


/**
 * Handle an erase background message. Since we use CDoubleBufferDC, we ignore it
 * \param pDC Device context
 * \returns FALSE
 */
BOOL CTreeDemoView::OnEraseBkgnd(CDC* pDC)
{
    return FALSE;
}


/**
 * Set the current view frame
 * \param frame Frame number
 */
void CTreeDemoView::SetFrame(int frame) 
{
    mTree->SetTreeFrame(frame);
    Invalidate();
}


/**
 * Set the wind speed
 * \param speed Wind speed in miles per hour
 */
void CTreeDemoView::SetWindSpeed(double speed)
{
    mTree->SetWindSpeed(speed);
    Invalidate();
}


/**
 * Set the tree seed
 * \param seed Seed integer value
 */
void CTreeDemoView::SetSeed(int seed)
{
    mTree->SetSeed(seed);
}

/**
* Handle the Harvest button press
*/
void CTreeDemoView::Harvest()
{
    auto harvest = mTree->Harvest();
    mBasket->AddToBasket(harvest);
    Invalidate();
}

/**
* Handle the Empty Basket button press
*/
void CTreeDemoView::EmptyBasket()
{
    mBasket->EmptyBasket();
    Invalidate();
}