/**
 * \file Fruit.h
 *
 * \author Charles Owen
 *
 * Abstract base class for a fruit that can be placed in the basket.
 */

#pragma once

/**
 * Abstract base class for a fruit that can be placed in the basket.
 *
 * AFX_EXT_CLASS is a Microsoft directive that indicates
 * that this class can be used outside the DLL. Do not change
 * it or add it to any other classes.
 */
class AFX_EXT_CLASS CFruit
{
public:
    /// Constructor
    CFruit() {}

    /// Destructor
    virtual ~CFruit() {}

    /**
     * Set the position of the fruit in the basket
     *
     * This position is relative to the basket, so 
     * it will be added to the basket location passed
     * to DrawInBasket when we draw it 
     * \param x X position in pixels
     * \param y Y position in pixels
     */
    virtual void SetBasketPosition(int x, int y) = 0;

    /**
     * Draw the fruit in the basket
     * \param graphics The graphics object to draw on 
     * \param x X location of the basket
     * \param y Y location of the basket 
     */
    virtual void DrawInBasket(Gdiplus::Graphics *graphics, int x, int y) = 0;
};

