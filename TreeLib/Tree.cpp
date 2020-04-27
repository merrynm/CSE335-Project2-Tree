/**
 * \file Tree.cpp
 *
 * \author Charles Owen
 *
 * You are not allowed to change this class in any way!
 *
 * This is a simple adapter class that routes all of the 
 * operations to the class CTreeStandin, which is a standin
 * for an actual tree in the system.
 */

#include "pch.h"
#include "Tree.h"
#include "TreeStandin.h"

using namespace Gdiplus;
using namespace std;


CTree::CTree() 
{
    mStandin = make_shared<CTreeStandin>();
}

void CTree::SetRootLocation(int x, int y)
{
    mStandin->SetRootLocation(x, y);
}

void CTree::DrawTree(Gdiplus::Graphics *graphics)
{
    mStandin->DrawTree(graphics);
}


void CTree::SetTreeFrame(int frame) 
{
    mStandin->SetTreeFrame(frame);
}


void CTree::SetWindSpeed(double speed) 
{
    mStandin->SetWindSpeed(speed);
}


void CTree::SetSeed(int seed) 
{
    mStandin->SetSeed(seed);
}


int CTree::GetSeed()
{
    return mStandin->GetSeed();
}

std::vector<std::shared_ptr<CFruit>> CTree::Harvest()
{
    return mStandin->Harvest();
}
