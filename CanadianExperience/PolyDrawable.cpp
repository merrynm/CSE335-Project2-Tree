/**
 * \file PolyDrawable.cpp
 *
 * \author Charles B. Owen
 */

#include "pch.h"
#include "PolyDrawable.h"

using namespace Gdiplus;
using namespace std;

/** Constructor for a polygon object
 * \param name The drawable name */
CPolyDrawable::CPolyDrawable(const std::wstring &name) : CDrawable(name)
{
}


/**
 * Destructor
 */
CPolyDrawable::~CPolyDrawable()
{
}


/** Draw our polygon.
 * \param  graphics The graphics context to draw on
 */
void CPolyDrawable::Draw(Gdiplus::Graphics *graphics)
{
    SolidBrush brush(mColor);

    // Transform the points
    vector<Point> points;
    for (auto point : mPoints)
    {
        points.push_back(RotatePoint(point, mPlacedR) + mPlacedPosition);
    }

    graphics->FillPolygon(&brush, &points[0], (int)points.size());
}


/** Test to see if we hit this object with a mouse click
 * \param pos Click position
 * \returns true it hit
 */
bool CPolyDrawable::HitTest(Gdiplus::Point pos)
{
    // Transform the points
    vector<Point> points;
    for (auto point : mPoints)
    {
        points.push_back(RotatePoint(point, mPlacedR) + mPlacedPosition);
    }

    GraphicsPath path;
    path.AddPolygon(&points[0], (int)points.size());
    return path.IsVisible(pos) ? true : false;
}


/**
 * Add a point to the polygon
 * \param point Point to add
 */
void CPolyDrawable::AddPoint(Gdiplus::Point point)
{
    mPoints.push_back(point);
}
