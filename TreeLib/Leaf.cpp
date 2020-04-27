/**
 * \file Leaf.cpp
 *
 * \author Merryn Marderosian
 *
 */

#include "pch.h"
#include "Leaf.h"

/// The maximum scale of the leaf image
const double MaxScale = 0.7;

/// Radians to Degrees
const double RtoD = 57.295779513;

CLeaf::CLeaf()
{

}

CLeaf::~CLeaf()
{

}

/** Updates the size of the leaf */
void CLeaf::Update()
{
	if (mScale < MaxScale)
	{
		mScale += 0.01;
	}
}

/** Draws the leaf
 * \param graphics The graphics object
 * \param angle The angle we are drawing the leaf at
 * \param x The x location
 * \param y The y location
 */
void CLeaf::DrawItem(Gdiplus::Graphics* graphics, double angle, double x, double y)
{
	mLeafImage = mTree->GetLeafImage();
	auto state = graphics->Save();
	graphics->TranslateTransform((float)x, (float)y);
	graphics->ScaleTransform((float)mScale , (float)mScale);

	graphics->DrawImage(mLeafImage.get(), -(int)mLeafImage->GetWidth() / 2,-(int)mLeafImage->GetHeight()/2,mLeafImage->GetWidth(), mLeafImage->GetHeight());
	graphics->Restore(state);
}

