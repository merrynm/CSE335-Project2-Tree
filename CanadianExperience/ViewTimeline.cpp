/**
 * \file ViewTimeline.cpp
 *
 * \author Charles B. Owen
 */


#include "pch.h"
#include "CanadianExperience.h"
#include "ViewTimeline.h"
#include "DoubleBufferDC.h"

#include "MainFrm.h"
#include "Timeline.h"
#include "Picture.h"
#include "Actor.h"

#include <sstream>

using namespace std;
using namespace Gdiplus;

/// The window height
const int WindowHeight = 65;

/// The spacing between ticks in the timeline
const int TickSpacing = 3;

/// The length of a short tick mark
const int TickShort = 10;

/// The length of a long tick mark
const int TickLong = 20;

/// The amount of space to leave under the tick marks
const int TickUnder = 10;

/// Space to the left of the scale
const int BorderLeft = 10;

/// Space to the right of the scale
const int BorderRight = 10;

IMPLEMENT_DYNCREATE(CViewTimeline, CScrollView)

/** Constructor */
CViewTimeline::CViewTimeline()
{
    mPointer = unique_ptr<Bitmap>(Bitmap::FromFile(L"images/pointer.png"));
}

/** Destructor */
CViewTimeline::~CViewTimeline()
{
}


BEGIN_MESSAGE_MAP(CViewTimeline, CScrollView)
    ON_WM_CREATE()
    ON_WM_ERASEBKGND()
    ON_WM_MOUSEMOVE()
    ON_WM_LBUTTONDOWN()
    ON_COMMAND(ID_EDIT_SETKEYFRAME, &CViewTimeline::OnEditSetkeyframe)
    ON_COMMAND(ID_EDIT_DELETEKEYFRAME, &CViewTimeline::OnEditDeletekeyframe)
    ON_COMMAND(ID_FILE_SAVEAS, &CViewTimeline::OnFileSaveas)
    ON_COMMAND(ID_FILE_OPEN32782, &CViewTimeline::OnFileOpen32782)
    ON_COMMAND(ID_PLAY_PLAY, &CViewTimeline::OnPlayPlay)
    ON_COMMAND(ID_PLAY_PLAYFROMBEGINNING, &CViewTimeline::OnPlayPlayfrombeginning)
    ON_COMMAND(ID_PLAY_STOP, &CViewTimeline::OnPlayStop)
    ON_WM_TIMER()
END_MESSAGE_MAP()


/** Handle the initial update for this window */
void CViewTimeline::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

    int sbHeight = GetSystemMetrics(SM_CXHSCROLL);
    CSize sizeTotal(200, Height - sbHeight - 20);
	SetScrollSizes(MM_TEXT, sizeTotal);
}

/** Draw this window 
 * \param pDC Device context */
void CViewTimeline::OnDraw(CDC* pDC)
{
    // Get the timeline
    CTimeline *timeline = GetPicture()->GetTimeline();

    // Set the scroll system correctly
    CSize sizeTotal(timeline->GetNumFrames() * TickSpacing + BorderLeft + BorderRight, WindowHeight);
    SetScrollSizes(MM_TEXT, sizeTotal);

    CDoubleBufferDC dbDC(pDC);

    Graphics graphics(dbDC.m_hDC);    // Create GDI+ graphics context

    CRect rect;
    GetClientRect(&rect);
    int hit = rect.Height();
    int wid = rect.Width();

    Pen tickpen(Color::Black);
    SolidBrush brush(Color::Black);
    FontFamily fontFamily(L"Arial");
    Gdiplus::Font font(&fontFamily, 10);

    int bottom = hit - TickUnder;

    for (int tickNum = 0; tickNum <= timeline->GetNumFrames(); tickNum++)
    {
        int x = BorderLeft + tickNum * TickSpacing;
        int top = bottom - TickShort;
        bool onSecond = (tickNum % timeline->GetFrameRate()) == 0;
        if (onSecond)
        {
            top = bottom - TickLong;

            // Convert the tick number to seconds in a string
            std::wstringstream str;
            str << tickNum / timeline->GetFrameRate();
            std::wstring wstr = str.str();

            RectF size;
            PointF origin(0.0f, 0.0f);
            graphics.MeasureString(wstr.c_str(), wstr.size(), &font, origin, &size);

            graphics.DrawString(wstr.c_str(), wstr.size(), &font, PointF(x - size.Width / 2, bottom - TickLong - size.Height), &brush);
        }

        graphics.DrawLine(&tickpen, x, bottom, x, top);
    }

    //
    // Draw the pointer
    //
    int pw = mPointer->GetWidth();
    int ph = mPointer->GetHeight();
    int x = BorderLeft + (int)(timeline->GetCurrentTime() * timeline->GetFrameRate() * TickSpacing);
    graphics.DrawImage(mPointer.get(),
        x - mPointer->GetWidth() / 2, (int)(bottom - mPointer->GetHeight()),
        mPointer->GetWidth(), mPointer->GetHeight()
        );
}

/** Force an update of this window when the picture changes.
*/
void CViewTimeline::UpdateObserver()
{
    Invalidate();
}


/** Erase the background
 *
 * This is disabled to eliminate flicker
 * \param pDC Device context 
 * \returns FALSE */
BOOL CViewTimeline::OnEraseBkgnd(CDC* pDC)
{
    return FALSE;
}


/**
* Handle mouse click of left button
* \param nFlags Flags associated with the mouse movement
* \param point Current mouse location
*/
void CViewTimeline::OnLButtonDown(UINT nFlags, CPoint point)
{
    // Convert mouse coordinates to logical coordinates
    CClientDC dc(this);
    OnPrepareDC(&dc);
    dc.DPtoLP(&point);


    int x = point.x;

    // Get the timeline
    CTimeline *timeline = GetPicture()->GetTimeline();
    int pointerX = (int)(timeline->GetCurrentTime() * timeline->GetFrameRate() * TickSpacing + BorderLeft);

    mMovingPointer = x >= pointerX - (int)mPointer->GetWidth() / 2 && x <= pointerX + (int)mPointer->GetWidth() / 2;
    if (mMovingPointer)
    {
        int xx = 0;
    }

    __super::OnLButtonDown(nFlags, point);
}


/**
 * Handle mouse movement
 * \param nFlags Flags associated with the mouse movement
 * \param point Current mouse location
 */
void CViewTimeline::OnMouseMove(UINT nFlags, CPoint point)
{
    // Convert mouse coordinates to logical coordinates
    CClientDC dc(this);
    OnPrepareDC(&dc);
    dc.DPtoLP(&point);

    CTimeline *timeline = GetPicture()->GetTimeline();
    if (mMovingPointer && nFlags & MK_LBUTTON)
    {
        double time = (double)(point.x - BorderLeft) / (timeline->GetFrameRate() * TickSpacing);
        if (time < 0)
        {
            time = 0;
        }
        else if (time > timeline->GetDuration())
        {
            time = timeline->GetDuration();
        }

        GetPicture()->SetAnimationTime(time);
        UpdateWindow();
    }
    else
    {
        mMovingPointer = false;
    }

    __super::OnMouseMove(nFlags, point);
}



/**
 * Handle the Edit Set Keyframe menu option.
 */
void CViewTimeline::OnEditSetkeyframe()
{
    for (auto actor : *GetPicture())
    {
        actor->SetKeyframe();
    }
}


/**
 * Handle a delete keyframe menu option
 */
void CViewTimeline::OnEditDeletekeyframe()
{
    auto picture = GetPicture();

    picture->GetTimeline()->ClearKeyframe();
    picture->SetAnimationTime(picture->GetAnimationTime());
}


/**
 * Handle the File/Save Animation As menu option
 */
 void CViewTimeline::OnFileSaveas()
 {
     CFileDialog dlg(false,  // false = Save dialog box
         L".anim",           // Default file extension
         nullptr,            // Default file name (none)
         OFN_OVERWRITEPROMPT,      // Flags (none)
         L"Animation Files (*.anim)|*.anim|All Files (*.*)|*.*||");    // Filter 
     if (dlg.DoModal() != IDOK)
         return;

     wstring filename = dlg.GetPathName();
     GetPicture()->Save(filename);
 }


/**
 * Handle the File/Open Animation menu option
 */
 void CViewTimeline::OnFileOpen32782()
 {
     CFileDialog dlg(true,  // true = Open dialog box
         L".anim",           // Default file extension
         nullptr,            // Default file name (none)
         0,      // Flags (none)
         L"Animation Files (*.anim)|*.anim|All Files (*.*)|*.*||");    // Filter 
     if (dlg.DoModal() != IDOK)
         return;

     wstring filename = dlg.GetPathName();
     GetPicture()->Load(filename);
 }

 /**
  * Handle the Play>Play menu option
  */
 void CViewTimeline::OnPlayPlay()
 {
     if (!mPlaying)
     {
         /*
         * Initialize the elapsed time system
         */
         LARGE_INTEGER time, freq;
         QueryPerformanceCounter(&time);
         QueryPerformanceFrequency(&freq);

         mLastTime = time.QuadPart;
         mTimeFreq = double(freq.QuadPart);

         // Set playing true
         mPlaying = true;

         // Start the timer
         SetTimer(1, 30, nullptr);
     }
 }


 /**
 * Handle the Play>Play from Beginning menu option
 */
 void CViewTimeline::OnPlayPlayfrombeginning()
 {
     // Set to beginning
     GetPicture()->SetAnimationTime(0);

     OnPlayPlay();
 }

 /**
 * Handle the Play>Stop menu option
 */
 void CViewTimeline::OnPlayStop()
 {
     if (mPlaying)
     {
         KillTimer(1);
         mPlaying = false;
     }
 }

 /**
 * Timer event handler
 * \param nIDEvent Timer event ID
 */
 void CViewTimeline::OnTimer(UINT_PTR nIDEvent)
 {
     auto picture = GetPicture();
     auto timeline = picture->GetTimeline();

     /*
     * Compute the elapsed time since the last timer call
     */
     LARGE_INTEGER time;
     QueryPerformanceCounter(&time);
     long long diff = time.QuadPart - mLastTime;
     double elapsed = double(diff) / mTimeFreq;
     mLastTime = time.QuadPart;

	 double newTime = picture->GetAnimationTime() + elapsed;
	 if (newTime >= timeline->GetDuration())
	 {
		 OnPlayStop();
		 picture->SetAnimationTime(timeline->GetDuration());
	 }
	 else
	 {
		 picture->SetAnimationTime(newTime);
	 }


     __super::OnTimer(nIDEvent);
 }