/**
* \file Basket.cpp
*
* \author Charles Owen
*
* You are not allowed to change this class in any way!
*
* This is a simple adapter class that routes all of the
* operations to the class CBasketStandin, which is a standin
* for an actual basket in the system.
*/

#include "pch.h"
#include "Basket.h"
#include "BasketStandin.h"

using namespace Gdiplus;
using namespace std;

CBasket::CBasket() 
{
    mStandin = make_shared<CBasketStandin>();
}




void CBasket::SetBasketLocation(int x, int y) 
{
    mStandin->SetBasketLocation(x, y);
}


void CBasket::DrawBasket(Gdiplus::Graphics *graphics) 
{
    mStandin->DrawBasket(graphics);
}


void CBasket::AddToBasket(std::vector < std::shared_ptr<CFruit>> fruit) 
{
    mStandin->AddToBasket(fruit);
}


void CBasket::EmptyBasket() 
{
    mStandin->EmptyBasket();
}
