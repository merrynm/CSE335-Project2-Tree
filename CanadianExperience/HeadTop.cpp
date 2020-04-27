#include "pch.h"
#include "HeadTop.h"
#include "Actor.h"
#include "Timeline.h"

#include <sstream>
#include <iomanip>
#include <cstdlib>

using namespace Gdiplus;
using namespace std;

/// Constant ratio to convert radians to degrees
const double RtoD = 57.295779513;

/** Constructor for a top of the head object
 * \param name The drawable name to use
 * \param filename The filename for the image to use
 */
CHeadTop::CHeadTop(const std::wstring &name, const std::wstring &filename) : CImageDrawable(name, filename)
{
}


/**
 * Destructor
 */
CHeadTop::~CHeadTop()
{
}


/**
 * Set the actor. This is where we set the channel name
 * \param actor Actor to set
 */
void CHeadTop::SetActor(CActor *actor)
{
    CImageDrawable::SetActor(actor);

    // Set the channel name
    mPositionChannel.SetName(actor->GetName() + L":" + GetName() + L":position");

}


/**
 * Set the timeline. The tells the channel the timeline
 * \param timeline Timeline to set
 */
void CHeadTop::SetTimeline(CTimeline *timeline)
{
    CImageDrawable::SetTimeline(timeline);

    timeline->AddChannel(&mPositionChannel);
}


/** Set the keyframe based on the current status.
*/
void CHeadTop::SetKeyframe()
{
    CImageDrawable::SetKeyframe();

    mPositionChannel.SetKeyframe(GetPosition());
}

/** Get the current channel from the animation system.
*/
void CHeadTop::GetKeyframe()
{
    CImageDrawable::GetKeyframe();

    if (mPositionChannel.IsValid())
        SetPosition(mPositionChannel.GetPoint());
}



/**
* Draw the head
* \param graphics Graphics context to draw on
*/
void CHeadTop::Draw(Gdiplus::Graphics *graphics)
{
    CImageDrawable::Draw(graphics);

    // Distance horizontally from each eye center to the center
    int d2 = mInterocularDistance / 2;

    // Compute a left and right eye center X location
    int rightX = mEyesCenter.X - d2;
    int leftX = mEyesCenter.X + d2;

    // Eye center Y value
    int eyeY = mEyesCenter.Y;

    DrawEyebrow(graphics, Point(rightX - 10, eyeY - 16), Point(rightX + 4, eyeY - 18));
    DrawEyebrow(graphics, Point(leftX - 4, eyeY - 20), Point(leftX + 9, eyeY - 18));

    if (mLeftEye.IsLoaded() && mRightEye.IsLoaded()) 
    {
        // Determine the point on the screen were we will draw the left eye
        Point leye = TransformPoint(Point(leftX, eyeY));
        // And draw the bitmap there
        mLeftEye.DrawImage(graphics, leye, mPlacedR);

        // Repeat the process for the right eye.
        Point reye = TransformPoint(Point(rightX, eyeY));
        mRightEye.DrawImage(graphics, reye, mPlacedR);
    } 
    else
    {
        DrawEye(graphics, Point(leftX, eyeY));
        DrawEye(graphics, Point(rightX, eyeY));
    }

    //SolidBrush brush(Color::Black);
    //FontFamily fontFamily(L"Arial");
    //Gdiplus::Font font(&fontFamily, 30);

    //wstringstream str;
    //double rotation = GetRotation();
    //str << fixed << setprecision(1) << rotation;
    //RectF bb;
    //graphics->MeasureString(str.str().c_str(), str.str().length(), &font, PointF(0, 0), &bb);
    //graphics->DrawString(str.str().c_str(), str.str().length(), &font, PointF((float)(mPlacedPosition.X - bb.Width / 2), (float)mPlacedPosition.Y - 40), &brush);

}

/** Draw an eye using an Ellipse
 * \param graphics The graphics context to draw on
 * \param p1 Where to draw before transformation */
void CHeadTop::DrawEye(Gdiplus::Graphics *graphics, Gdiplus::Point p1)
{
    SolidBrush brush(Color::Black);

    Point e1 = TransformPoint(p1);

    float wid = 15.0f;
    float hit = 20.0f;

    auto state = graphics->Save();
    graphics->TranslateTransform((float)e1.X, (float)e1.Y);
    graphics->RotateTransform((float)(-mPlacedR * RtoD));
    graphics->FillEllipse(&brush, -wid/2, -hit/2, wid, hit);
    graphics->Restore(state);
}

/**
 * Draw an eyebrow, automatically transforming the points
 *
 * Draw a line from (x1, y1) to (x2, y2) after transformation
 * to the local coordinate system.
 * \param graphics Graphics context to draw on
 * \param p1 First point
 * \param p2 Second point
 */
void CHeadTop::DrawEyebrow(Gdiplus::Graphics *graphics, Gdiplus::Point p1, Gdiplus::Point p2)
{
    Point eb1 = TransformPoint(p1);
    Point eb2 = TransformPoint(p2);

    Pen eyebrowPen(Color::Black, 2);
    graphics->DrawLine(&eyebrowPen, eb1, eb2);
}

/** Transform a point from a location on the bitmap to
*  a location on the screen.
* \param  p Point to transform
* \returns Transformed point
*/
Gdiplus::Point CHeadTop::TransformPoint(Gdiplus::Point p)
{
    // Make p relative to the image center
    p = p - GetCenter();

    // Rotate as needed and offset
    return RotatePoint(p, mPlacedR) + mPlacedPosition;
}