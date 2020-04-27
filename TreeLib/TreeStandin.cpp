/**
 * \file TreeStandin.cpp
 *
 * \author Charles Owen
 *
 * This file may not be changed.
 */

#include "pch.h"
#include "TreeStandin.h"
#include <sstream>

using namespace Gdiplus;
using namespace std;

/**
 * Constructor
 */
CTreeStandin::CTreeStandin()
{
}


/**
 * Destructor
 */
CTreeStandin::~CTreeStandin()
{
}


/**
* Draw the tree at the currently specified location
* \param graphics GDI+ Graphics object
*/
void CTreeStandin::DrawTree(Gdiplus::Graphics *graphics)
{
    const int LineSize = 16;
    const int LineSpacing = 25;

    Pen pen(Color(139, 69, 19), (REAL)3);
    pen.SetEndCap(LineCapRound);
    graphics->DrawLine(&pen, (REAL)mX, (REAL)mY, (REAL)(mX), (REAL)(mY - 100));

    Pen pen2(Color(139, 69, 19), (REAL)2);
    graphics->DrawLine(&pen, (REAL)(mX), (REAL)(mY - 100), (REAL)(mX + 40), (REAL)(mY - 140));
    graphics->DrawLine(&pen, (REAL)(mX), (REAL)(mY - 100), (REAL)(mX - 50), (REAL)(mY - 140));

    int y = mY - LineSize;
    CenteredString(graphics, L"Tree go here!", mX, y, LineSize);
    y -= LineSpacing;

    {
        wstringstream str;
        str << L"Seed: " << mSeed << ends;
        CenteredString(graphics, str.str(), mX, y, LineSize);
        y -= LineSpacing;
    }

    {
        wstringstream str;
        str << L"Frame: " << mFrame << ends;
        CenteredString(graphics, str.str(), mX, y, LineSize);
        y -= LineSpacing;
    }


    {
        wstringstream str;
        str << L"Wind Speed: " << mWindSpeed;
        CenteredString(graphics, str.str(), mX, y, LineSize);
        y -= LineSpacing;
    }

    if(mHarvested) 
    {
        CenteredString(graphics, L"Harvested", mX, y, LineSize);
        y -= LineSpacing;
    }

}


/**
 * Draw a centered string
 *
 * Yes, I know this function is repeated in both CTreeStandin
 * and CBasketStandin. Normally I would create a base class and
 * move this function into it. I'm not doing that to keep the number
 * of class students see minimal.
 *
 * \param graphics Graphics object
 * \param str String to draw
 * \param x X location of bottom center of string
 * \param y Y location of bottom center of string
 * \param dy String height
 */
void CTreeStandin::CenteredString(Gdiplus::Graphics *graphics, const std::wstring &str, int x, int y, int dy)
{
    y -= dy;

    FontFamily fontFamily(L"Arial");
    Gdiplus::Font font(&fontFamily, (REAL)dy);

    SolidBrush black(Color(0, 0, 0));
    RectF rect;
    graphics->MeasureString(str.c_str(), -1, &font, PointF((REAL)x, (REAL)y), &rect);
    graphics->DrawString(str.c_str(),  // String to draw
        -1,         // String length, -1 means it figures it out on its own
        &font,      // The font to use
        PointF((REAL)(x - rect.Width / 2), (REAL)y),   // Where to draw (top left corner)
        &black);    // The brush to draw the text with
}