/**
 * \file /CanadianExperience/TreeLib/ActualTree.cpp
 *
 * \author Merryn Marderosian
 */

#include "pch.h"
#include "ActualTree.h"
#include "Branch.h"
#include "PseudoRandom.h"
#include "IsFruitVisitor.h"
#include "ActualBasket.h"

using namespace Gdiplus;
using namespace std;

/// pi constant
const double pi = 3.14159;

/** Constructor */
CActualTree::CActualTree()
{
	mLeafImage = std::shared_ptr<Gdiplus::Bitmap>(Bitmap::FromFile(L"images/pink_cloud2.png"));
	mFruitImage = std::shared_ptr<Gdiplus::Bitmap>(Bitmap::FromFile(L"images/lolli2.png"));

	mRoot = make_shared<CBranch>();

	Reset();
}

void CActualTree::SetRootLocation(int x, int y)
{

	mRoot->SetX(x);
	mRoot->SetY(y);
}

void CActualTree::DrawTree(Gdiplus::Graphics* graphics)
{
	double rootStartAngle = 3 * pi / 2 + 0.001;
	double x = mRoot->GetX();
	double y = mRoot->GetY();
	mRoot->DrawItem(graphics, rootStartAngle, x, y);
	mRoot->SetTree(this);
}

void CActualTree::SetTreeFrame(int frame)
{
	if (frame < mCurrFrame)
	{
		Reset();
	}

	while (mCurrFrame < frame) {
		mCurrFrame++;
		mRoot->Update();
	}
}


void CActualTree::SetWindSpeed(double speed)
{
	mWindSpeed = speed;
	mRoot->UpdateWind(speed);
}

void CActualTree::SetSeed(int seed)
{
	mRandom.Seed(seed);
	mSeed = seed;
	mRandom.Reset();
}

int CActualTree::GetSeed()
{
	return mSeed;
}

/** Resets the tree so reversing the frames works. */
void CActualTree::Reset()
{
	mRandom.Seed(mSeed);
	mRandom.Reset();
	int x = (int)mRoot->GetX();
	int y = (int)mRoot->GetY();
	mRoot = make_shared<CBranch>();
	mCurrFrame = 0;
	mMaxDepth = 0;
	mRoot->SetTree(this);
	SetRootLocation(x, y);
}

std::vector<std::shared_ptr<CFruit>> CActualTree::Harvest()
{
	mFruits.clear();
	CIsFruitVisitor fruitVisitor;
	mRoot->Harvest(&fruitVisitor);

	return mFruits;
}
