/**
 * \file ImageDrawable.h
 *
 * \author Charles B. Owen
 *
 * A drawable based on drawing a bitmap image.
 */

#pragma once
#include "Drawable.h"
#include "RotatedBitmap.h"


/**
 * A drawable based on drawing a bitmap image.
 */
class CImageDrawable :
    public CDrawable, public CRotatedBitmap
{
public:
    CImageDrawable(const std::wstring &name, const std::wstring &filename);
    virtual ~CImageDrawable();

    /** Default constructor disabled */
    CImageDrawable() = delete;
    /** Copy constructor disabled */
    CImageDrawable(const CImageDrawable &) = delete;
    /** Assignment operator disabled */
    void operator=(const CImageDrawable &) = delete;

    virtual void Draw(Gdiplus::Graphics *graphics) override;
    virtual bool HitTest(Gdiplus::Point pos) override;


};

