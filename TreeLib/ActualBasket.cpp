/**
 * \file ActualBasket.cpp
 *
 * \author Merryn Marderosian
 *
 */

#include "pch.h"
#include "ActualBasket.h"
#include "ActualFruit.h"
#include <string>
#include <cstdlib>

using namespace Gdiplus;


/** Constructor */
CActualBasket::CActualBasket()
{
	mBasketBack = std::shared_ptr<Gdiplus::Bitmap>(Bitmap::FromFile(L"images/candyjar.png"));
	mBasketFront = std::shared_ptr<Gdiplus::Bitmap>(Bitmap::FromFile(L"images/candyjar_front.png"));
}

/** Sets the location of the basket on the screen 
* \param x The x location
* \param y The y location
*/
void CActualBasket::SetBasketLocation(int x, int y)
{
	mX = x;
	mY = y;
}

/** Draws the basket images on the screen 
* \param graphics The graphics object 
*/
void CActualBasket::DrawBasket(Gdiplus::Graphics* graphics)
{
	graphics->TranslateTransform((float)mX, (float)mY);
	graphics->DrawImage(mBasketBack.get(), -(int)mBasketBack->GetWidth() / 2, -(int)mBasketBack->GetHeight(), mBasketBack->GetWidth(), mBasketBack->GetHeight());
	for (auto fruit : mFruitsToDraw)
	{
		//double maxX = mX + mBasketBack->GetWidth() / 2;
		//double minX = mX - mBasketBack->GetWidth() / 2;
		//double maxY = mY + mBasketBack->GetHeight() / 2;
		//double minY = mY - mBasketBack->GetHeight() / 2;
		//double randX = mTree->GetRandom->Random(minX, maxX);
		//double randY = mTree->GetRandom->Random(minY, maxY);

		//fruit->DrawItem(graphics, randX, randY);
	}
	graphics->DrawImage(mBasketFront.get(), -(int)mBasketFront->GetWidth() / 2, -(int)mBasketFront->GetHeight(), mBasketFront->GetWidth(), mBasketFront->GetHeight());
}

/** Adds the fruits to the basket 
* \param fruit The fruit we are adding
*/
void CActualBasket::AddToBasket(std::vector < std::shared_ptr<CFruit>> fruit)
{
	for (auto fruit : mFruitsToDraw)
	{
		mFruitsToDraw.push_back(fruit);
	}
}

/** removes the fruits from the basket */
void CActualBasket::EmptyBasket()
{
	mFruitsToDraw.clear();
}
