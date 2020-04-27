/**
 * \file ImageDrawable.cpp
 *
 * \author Charles B. Owen
 */

#include "pch.h"
#include "ImageDrawable.h"

using namespace std;
using namespace Gdiplus;

/// Constant ratio to convert radians to degrees
const double RtoD = 57.295779513;

/** Constructor
 * \param name The drawable name
 * \param filename The filename for the image */
CImageDrawable::CImageDrawable(const std::wstring &name, const std::wstring &filename) : 
    CDrawable(name)
{
    LoadImage(filename);
}


CImageDrawable::~CImageDrawable()
{
}


/**
 * Draw the image drawable
 * \param graphics Graphics context to draw on
 */
void CImageDrawable::Draw(Gdiplus::Graphics *graphics)
{
    DrawImage(graphics, mPlacedPosition, mPlacedR);
}


/**
 * Test to see if we clicked on the image.
 * \param pos Position to test
 * \returns True if clicked on
 */
bool CImageDrawable::HitTest(Gdiplus::Point pos)
{
    Matrix mat;
    mat.Translate((float)mCenter.X, (float)mCenter.Y);
    mat.Rotate((float)(mPlacedR * RtoD));
    mat.Translate((float)-mPlacedPosition.X, (float)-mPlacedPosition.Y);

    Point points[] = { pos };
    mat.TransformPoints(points, 1);

    double wid = mImage->GetWidth();
    double hit = mImage->GetHeight();

    double testX = points[0].X;
    double testY = points[0].Y;

    // Test to see if x, y are in the image
    if (testX < 0 || testY < 0 || testX >= wid || testY >= hit)
    {
        // We are outside the image
        return false;
    }

    // Test to see if x, y are in the drawn part of the image
    auto format = mImage->GetPixelFormat();
    if (format == PixelFormat32bppARGB || format == PixelFormat32bppPARGB)
    {
        // This image has an alpha map, which implements the 
        // transparency. If so, we should check to see if we
        // clicked on a pixel where alpha is not zero, meaning
        // the pixel shows on the screen.
        Color color;
        mImage->GetPixel((int)testX, (int)testY, &color);
        return color.GetAlpha() != 0;
    }
    else {
        return true;
    }
}
