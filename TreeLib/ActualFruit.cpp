/**
 * \file ActualFruit.cpp
 *
 * \author Merryn Marderosian
 *
 */

#include "pch.h"
#include "ActualFruit.h"
#include "ActualBasket.h"

/// the maximum scale of the fruit
const double MaxScale = 0.9;

/// for conversion from radians to degrees
const double RtoD = 57.295779513;

/** Constructor */
CActualFruit::CActualFruit()
{

}

/** Destructor */
CActualFruit::~CActualFruit()
{

}

/**
 * Updates the size of the fruit
 */
void CActualFruit::Update()
{
	if (mScale < MaxScale)
	{
		mScale += 0.02;
	}
}

/** Draws the fruit item on the tree
 * \param graphics The graphics object
 * \param angle The angle it's branch is set at
 * \param x The x location of its parent branch
 * \param y The y location of its parent branch
 */
void CActualFruit::DrawItem(Gdiplus::Graphics* graphics, double angle, double x, double y)
{
	mFruitImage = mTree->GetFruitImage();
	auto state = graphics->Save();
	graphics->TranslateTransform((float)x, (float)y);
	graphics->ScaleTransform((float)mScale, (float)mScale);

	graphics->DrawImage(mFruitImage.get(), (int)mFruitImage->GetWidth() / 2, (int)mFruitImage->GetHeight()/2, -(int)mFruitImage->GetWidth(), -(int)mFruitImage->GetHeight());
	graphics->Restore(state);
}

void CActualFruit::Accept(CItemVisitor* visitor)
{ 
	visitor->VisitFruit(this); 

}

void CActualFruit::DrawInBasket(Gdiplus::Graphics* graphics, int x, int y)
{

}