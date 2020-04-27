/**
 * \file PictureFactory.cpp
 *
 * \author Charles B. Owen
 */

#include "pch.h"
#include "PictureFactory.h"
#include "HaroldFactory.h"
#include "SpartyFactory.h"
#include "ImageDrawable.h"
#include "TreeFactory.h"
#include "BasketAdaptor.h"
#include "TreeAdaptor.h"

using namespace std;
using namespace Gdiplus;

CPictureFactory::CPictureFactory()
{
}


CPictureFactory::~CPictureFactory()
{
}


/** Factory method to create a new picture.
* \returns The created picture
*/
std::shared_ptr<CPicture> CPictureFactory::Create()
{
    shared_ptr<CPicture> picture = make_shared<CPicture>();

    // Create the background and add it
    auto background = make_shared<CActor>(L"Background");
    background->SetClickable(false);
    background->SetPosition(Point(-100, 0));
    auto backgroundI = make_shared<CImageDrawable>(L"Background", L"images/Background.png");
    background->AddDrawable(backgroundI);
    background->SetRoot(backgroundI);
    picture->AddActor(background);

	//Create and add a tree
	auto treeActor = make_shared<CActor>(L"Tree");
	auto tree = make_shared<CTreeAdaptor>(L"Tree");
	tree->SetSeed(30757);
	treeActor->AddDrawable(tree);
	treeActor->SetRoot(tree);
	treeActor->SetPosition(Point(150, 475));
	picture->AddActor(treeActor);

	//Create and add another tree
	auto treeActor2 = make_shared<CActor>(L"Tree2");
	auto tree2 = make_shared<CTreeAdaptor>(L"Tree2");
	tree2->SetStart(100);
	treeActor2->AddDrawable(tree2);
	treeActor2->SetRoot(tree2);
	treeActor2->SetPosition(Point(600, 500));
	picture->AddActor(treeActor2);

    // Create and add Harold
    CHaroldFactory factory;
    auto harold = factory.Create();

    // This is where Harold will start out.
    harold->SetPosition(Point(400, 500));

    picture->AddActor(harold);

    // Create and add Sparty
    CSpartyFactory sfactory;
    auto sparty = sfactory.Create();

    sparty->SetPosition(Point(200, 500));
    picture->AddActor(sparty);

	//Create and add the basket
	auto basketActor = make_shared<CActor>(L"Basket");
	auto basket = make_shared<CBasketAdaptor>(L"Basket");
	basketActor->AddDrawable(basket);
	basketActor->SetRoot(basket);
	picture->AddActor(basketActor);

    return picture;
}
