/**
 * \file PolyDrawable.h
 *
 * \author Charles B. Owen
 *
 * A drawable based on polygon images.
 */

#pragma once
#include "Drawable.h"

#include <vector>

/**
 * A drawable based on polygon images.
 *
 * This class has a list of points and draws a polygon
 * drawable based on those points.
 */
class CPolyDrawable :
    public CDrawable
{
public:
    CPolyDrawable(const std::wstring &name);
    virtual ~CPolyDrawable();

    /** Default constructor disabled */
    CPolyDrawable() = delete;
    /** Copy constructor disabled */
    CPolyDrawable(const CPolyDrawable &) = delete;
    /** Assignment operator disabled */
    void operator=(const CPolyDrawable &) = delete;

    virtual void Draw(Gdiplus::Graphics *graphics) override;
    virtual bool HitTest(Gdiplus::Point pos) override;

    void AddPoint(Gdiplus::Point point);

    /** Set the color for the polygon
     * \param color New color to set */
    void SetColor(Gdiplus::Color color) { mColor = color; }

    /** Get the drawable color 
     * \return Color */
    Gdiplus::Color GetColor() const { return mColor; }

private:
    /// The polygon color
    Gdiplus::Color mColor = Gdiplus::Color::Black;

    /// The array of point objects
    std::vector<Gdiplus::Point> mPoints;
};

