/**
 * \file ActualBasket.h
 *
 * \author Merryn Marderosian
 *
 * This is the class that implements the actual basket.
 *
 */

#pragma once
#include "Basket.h"
#include "TreeItemImage.h"
#include "PseudoRandom.h"

/// The actual basket class
class CActualBasket :
	public CBasket
{
public:
	CActualBasket();

	/// Destructor
	virtual ~CActualBasket() {}

	/// Copy constructor/disabled
	CActualBasket(const CActualBasket&) = delete;

	/// Assignment operator/disabled
	void operator=(const CActualBasket&) = delete;

	/**
	* Set the position for the basket.
	* \param x X location (pixels)
	* \param y Y location (pixels)
	*/
	virtual void SetBasketLocation(int x, int y);

	/**
	* Draw the basket at the currently specified location
	* \param graphics GDI+ Graphics object
	*/
	virtual void DrawBasket(Gdiplus::Graphics* graphics);

	/**
	 * Add fruit to the basket
	 * \param fruit Vector of fruit objects
	 */
	virtual void AddToBasket(std::vector < std::shared_ptr<CFruit>> fruit);

	/**
	 * Empty all fruit from the basket
	 */
	virtual void EmptyBasket();

private:
	/// The back of the basket image
	std::shared_ptr<Gdiplus::Bitmap> mBasketBack;

	/// The front of the basket image
	std::shared_ptr<Gdiplus::Bitmap> mBasketFront;
	
	/// The x location 
	double mX = 450;

	/// The y locaiton
	double mY = 500;

	///The vector of fruits we want to draw inside the basket
	std::vector < std::shared_ptr<CFruit>> mFruitsToDraw;
};

