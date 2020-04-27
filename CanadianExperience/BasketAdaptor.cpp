/**
 * \file /CanadianExperience/CanadianExperience/BasketAdaptor.cpp
 *
 * \author Merryn Marderosian
 *
 */

#include "pch.h"
#include "BasketAdaptor.h"
#include "TreeFactory.h"

/** Constructor 
 * \param name The name of this basket drawable
 */
CBasketAdaptor::CBasketAdaptor(const std::wstring& name) : CDrawable(name)
{
	CTreeFactory factory;
	mBasket = factory.CreateBasket();

}

/** Destructor */
CBasketAdaptor::~CBasketAdaptor()
{

}

/** Draw the basket
 * \param graphics The graphics object
 */
void CBasketAdaptor::Draw(Gdiplus::Graphics* graphics)
{
	mBasket->SetBasketLocation(500, 500);
	mBasket->DrawBasket(graphics);
}