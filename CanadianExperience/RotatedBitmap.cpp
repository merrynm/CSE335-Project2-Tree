/**
 * \file RotatedBitmap.cpp
 *
 * \author Charles B. Owen
 */

#include "pch.h"
#include "RotatedBitmap.h"

using namespace std;
using namespace Gdiplus;

/// Constant ratio to convert radians to degrees
const double RtoD = 57.295779513;


/**
 * Constructor.
 */
CRotatedBitmap::CRotatedBitmap()
{
}


/**
 * Destructor
 */
CRotatedBitmap::~CRotatedBitmap()
{
}


/**
 * Load the image from a file.
 * \param filename File to load
 */
void CRotatedBitmap::LoadImage(const std::wstring &filename)
{
    mImage = unique_ptr<Bitmap>(Bitmap::FromFile(filename.c_str()));
    if (mImage->GetLastStatus() != Ok)
    {
        wstring msg(L"Failed to open ");
        msg += filename;
        AfxMessageBox(msg.c_str());
    } 
    else
    {
        mLoaded = true;
    }
}


/**
 * Draw the bitmap
 * \param graphics The graphics context to draw on
 * \param position The position to draw at
 * \param angle The rotation angle
 */
void CRotatedBitmap::DrawImage(Gdiplus::Graphics *graphics, Gdiplus::Point position, double angle)
{
    auto state = graphics->Save();
    graphics->TranslateTransform((float)position.X, (float)position.Y);
    graphics->RotateTransform((float)(-angle * RtoD));
    graphics->DrawImage(mImage.get(), -mCenter.X, -mCenter.Y,
        mImage->GetWidth(), mImage->GetHeight());
    graphics->Restore(state);
}