/**
 * \file /CanadianExperience/CanadianExperience/TreeAdaptor.cpp
 *
 * \author Merryn Marderosian
 *
 */

#include "pch.h"
#include "TreeAdaptor.h"
#include "TreeFactory.h"
#include "Timeline.h"

using namespace Gdiplus;
using namespace std;


/** Constructor 
 * \param name The name of this drawable
 */
CTreeAdaptor::CTreeAdaptor(const std::wstring& name) : CDrawable(name)
{
	CTreeFactory factory;
	mTree= factory.CreateTree();
}

/** Destructor */
CTreeAdaptor::~CTreeAdaptor()
{

}

/** Draw the tree
 * \param graphics The graphics object
 */
void CTreeAdaptor::Draw(Gdiplus::Graphics* graphics)
{
	int currFrame = mTimeline->GetCurrentFrame();
	if (currFrame >= mStart)
	{
		mTree->SetTreeFrame(currFrame - mStart);
		auto state = graphics->Save();
		graphics->TranslateTransform((float)mPlacedPosition.X, (float)mPlacedPosition.Y);
		mTree->DrawTree(graphics);
		graphics->Restore(state);
	}
}

/** Set the timeline object
 * \param timeline The timeline object
 */
void CTreeAdaptor::SetTimeline(CTimeline* timeline)
{
	CDrawable::SetTimeline(timeline);
	mTimeline = timeline;
}


/** Set the Seed
 * \param seed The seed we are setting for this tree.
 */

void CTreeAdaptor::SetSeed(int seed)
{
	mTree->SetSeed(seed);
}