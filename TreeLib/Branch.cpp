/**
 * \file Branch.cpp
 *
 * \author Merryn Marderosian
 *
 */

#include "pch.h"
#include "Branch.h"
#include "ActualTree.h"
#include "PseudoRandom.h"
#include "Leaf.h"
#include "ActualFruit.h"

using namespace Gdiplus;

///The growth multiplier
const double GrowRate = 0.4;

/// conversion from radians to degrees
const double RtoD = 57.295779513;

/// Brown pen
const Color BrownPen = Color(139, 69, 19);

/// Pink pen
const Color PinkPen = Color(255, 121, 185);

/// Orange pen
const Color OrangePen = Color(250, 139, 80);

/// Yellow pen
const Color YellowPen = Color(236, 241, 126);

/// Green Pen
const Color GreenPen = Color(118, 255, 111);

/// Blue Pen
const Color BluePen = Color(55, 253, 243);

/// Purple pen
const Color PurplePen = Color(187, 60, 255);


/** Constructor */
CBranch::CBranch()
{

}

/** Destructor */
CBranch::~CBranch()
{

}

/** Sets the angle of the branch
 * \param angle The angle we are setting
 */
void CBranch::SetAngle(double angle)
{
	mOffsetAngle = angle;
	mAngle = angle;
}

/** Updates the branch and its children 
* This is the function wherer spawining is handled
*/
void CBranch::Update()
{
	double delta = mTree->GetDelta();
	double growRate = pow((1.0 + GrowRate), delta);

	if (mTree->GetMaxDepth() < mDepth)
	{
		mTree->SetMaxDepth(mDepth);
	}

	if (mTree->GetMaxDepth() < 11)
	{
		if (mWidth <= mMaxWidth)
		{
			mWidth *= growRate;
		}
		if (mLength <= mMaxLength)
		{
			mLength *= growRate;
		}

		if (mLength > 6.9 && mChildren.size() == 0)
		{
			if (mDepth > 5 && mTree->GetRandom()->Random(0, 1) < 0.7)
			{
				auto child1 = std::make_shared<CLeaf>();
				child1->SetAngle(mAngle);
				mChildren.push_back(child1);
			}
			else
			{
				auto child1 = std::make_shared<CBranch>();
				child1->SetAngle(mTree->GetRandom()->Random(-0.3, 0.3));
				mChildren.push_back(child1);
			}
			if (mDepth > 7 && mTree->GetRandom()->Random(0, 1) < 0.02)
			{
				auto child2 = std::make_shared<CActualFruit>();
				child2->SetAngle(mAngle);
				mChildren.push_back(child2);
				mTree->AddFruit(child2);
			}
			else
			{
				auto child2 = std::make_shared<CBranch>();
				child2->SetAngle(mTree->GetRandom()->Random(-1.2, 1.2));
				mChildren.push_back(child2);
			}

			for (auto child : mChildren)
			{
				child->SetTree(mTree);
				child->SetDepth(mDepth + 1);
			}
		}

		for (auto child : mChildren)
		{
			child->Update();
		}
	}
	

}

/** Draws the branch child
* \param graphics The graphics object
* \param angle The angle this branch will grow
* \param x The x location of this branch
* \param y The y location of this branch
*/
void CBranch::DrawItem(Gdiplus::Graphics* graphics, double angle, double x, double y)
{
	double useAngle = mAngle + angle;
	double dx = cos(useAngle) * mLength;
	double dy = sin(useAngle) * mLength;

	Color usePen;

	if (mDepth % 6 == 0)
	{
		usePen = PinkPen;
	}
	else if(mDepth % 6 == 1)
	{
		usePen = OrangePen;
	}
	else if (mDepth % 6 == 2)
	{
		usePen = YellowPen;
	}
	else if (mDepth % 6 == 3)
	{
		usePen = GreenPen;
	}
	else if (mDepth % 6 == 4)
	{
		usePen = BluePen;
	}
	else if (mDepth % 6 == 5)
	{
		usePen = PurplePen;
	}

	Pen pen(usePen, (REAL)mWidth);
	pen.SetEndCap(LineCapRound);
	graphics->DrawLine(&pen, Point((int)x, (int)y), Point((int)x + (int)dx, (int)y + (int)dy));

	if (mChildren.size() == 2)
	{
		for (auto child : mChildren)
		{
			child->DrawItem(graphics, useAngle, x + dx, y + dy);
		}
	}
}

/** Updates the angle of the branches based on wind speed
 * \param speedConst The current wind speed
 */
void CBranch::UpdateWind(double speedConst)
{
	mAngle = sin(speedConst / 300) + mOffsetAngle;
	if (mChildren.size() != 0)
	{
		for (auto child : mChildren)
		{
			child->UpdateWind(speedConst);
		}
	}
}

/** Harvests the fruit
 * \param visitor The visitor
 */
void CBranch::Harvest(CIsFruitVisitor *visitor)
{
	std::vector<std::shared_ptr<CTreeItem>> itemsToDelete;
	std::vector<std::shared_ptr<CTreeItem>>::iterator deleteThis = mChildren.begin();
	bool deleteIt = false;

	for (auto i = mChildren.begin(); i != mChildren.end(); i++)
	{
		(*i)->Accept(visitor);
		if (visitor->IsFruitVisitor())
		{
			deleteIt = true;
			deleteThis = i;
		}

		else
		{
			visitor->Reset();
			(*i)->Harvest(visitor);
		}
	}

	if (deleteIt)
	{
		mChildren.erase(deleteThis);
	}
	visitor->Reset();
}
