/**
 * \file BasketStandin.h
 *
 * \author Charles Owen
 *
 * This class is a stand-in class that will allow you to
 * develop the basket adapter class first if you so choose.
 *
 * You are not allowed to change this class in any way!
 */

#pragma once

#include <string>
#include <vector>
#include <memory>

class CFruit;

/**
 * This class is a stand-in class that will allow you to
 * develop the basket adapter class first if you so choose.
 *
 * You are not allowed to change this class in any way!
 */
class CBasketStandin
{
public:
    CBasketStandin() {}
    virtual ~CBasketStandin() {}

    /**
    * Set the position for the basket.
    * \param x X location (pixels)
    * \param y Y location (pixels)
    */
    void SetBasketLocation(int x, int y) { mX = x; mY = y; }

    void DrawBasket(Gdiplus::Graphics *graphics);

    /**
    * Add fruit to the basket
    * \param fruit Vector of fruit objects
    */
    void AddToBasket(std::vector < std::shared_ptr<CFruit>> fruit) { mAdded = true; }

    /**
    * Empty all fruit from the basket
    */
    void EmptyBasket() { mAdded = false; }

private:
    void CenteredString(Gdiplus::Graphics *graphics, const std::wstring &str, int x, int y, int dy);

    int mX = 0;     ///< Basket X location
    int mY = 0;     ///< Basket Y location
    bool mAdded = false;    ///< Add has been called?
};

