/**
 * \file HeadTop.h
 *
 * \author Charles B. Owen
 *
 * Implements the top of a characters head, 
 * which has special functionality.
 */

#pragma once

#include "ImageDrawable.h"
#include "AnimChannelPoint.h"

/** Implements the top of a characters head, 
* which has special functionality.
*/
class CHeadTop :
    public CImageDrawable
{
public:
    CHeadTop(const std::wstring &name, const std::wstring &filename);
    ~CHeadTop();

    /** Default constructor disabled */
    CHeadTop() = delete;
    /** Copy constructor disabled */
    CHeadTop(const CHeadTop &) = delete;
    /** Assignment operator disabled */
    void operator=(const CHeadTop &) = delete;

    /// Is this drawable moveable?
    /// \returns true
    virtual bool IsMovable() { return true; }

    void Draw(Gdiplus::Graphics *graphics);
    void DrawEyebrow(Gdiplus::Graphics *graphics, Gdiplus::Point p1, Gdiplus::Point p2);
    void DrawEye(Gdiplus::Graphics *graphics, Gdiplus::Point p1);

    /** Get a pointer to the left eye bitmap
    * \returns Pointers to the left eye bitmap
    */
    CRotatedBitmap *GetLeftEye() { return &mLeftEye; }

    /** Get a pointer to the left eye bitmap
    * \returns Pointers to the left eye bitmap
    */
    CRotatedBitmap *GetRightEye() { return &mRightEye; }

    /** Set the location for the center of the eyes
    * \param center New eyes center location
    */
    void SetEyesCenter(Gdiplus::Point center) { mEyesCenter = center; }

    /** Get the eyes center location
    * \returns Eyes center location
    */
    Gdiplus::Point GetEyesCenter() const { return mEyesCenter; }

    /** Set the distance between the eyes
    * \param d Distance between the eyes in pixels
    */
    void SetInterocularDistance(int d) { mInterocularDistance = d; }

    /** Get the distance between the eyes
    * \returns Distance between the eyes in pixels
    */
    int GetInterocularDistance() const { return mInterocularDistance; }

    virtual void SetActor(CActor *actor) override;
    virtual void SetTimeline(CTimeline *timeline) override;
    virtual void SetKeyframe() override;
    virtual void GetKeyframe() override;

private:
    Gdiplus::Point TransformPoint(Gdiplus::Point p);

    CRotatedBitmap mLeftEye;        ///< Bitmap for the left eye
    CRotatedBitmap mRightEye;       ///< Bitmap for the right eye

    /// Location of the center of the eyes
    Gdiplus::Point mEyesCenter = Gdiplus::Point(55, 79);
     
    /// Distance between the eyes in pixels
    int mInterocularDistance = 27;       

    /// Channel for the head position
    CAnimChannelPoint mPositionChannel;
};

