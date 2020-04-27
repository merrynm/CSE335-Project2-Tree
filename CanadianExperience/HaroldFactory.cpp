/**
 * \file HaroldFactory.cpp
 *
 * \author Charles B. Owen
 */

#include "pch.h"
#include "HaroldFactory.h"
#include "PolyDrawable.h"
#include "ImageDrawable.h"
#include "HeadTop.h"

using namespace Gdiplus;
using namespace std;

CHaroldFactory::CHaroldFactory()
{
}


CHaroldFactory::~CHaroldFactory()
{
}


/** This is a concrete factory method that creates our Harold actor.
* \returns Pointer to an actor object.
*/
std::shared_ptr<CActor> CHaroldFactory::Create()
{
    shared_ptr<CActor> actor = make_shared<CActor>(L"Harold");

	auto dress = make_shared<CImageDrawable>(L"Dress", L"images/Picture1.png");
	dress->SetCenter(Point(44, 138));
	dress->SetPosition(Point(0, -114));
	actor->SetRoot(dress);

	auto lleg = make_shared<CImageDrawable>(L"Left Leg", L"images/girl_lleg.png");
	lleg->SetCenter(Point(11, 9));
	lleg->SetPosition(Point(27, 0));
	dress->AddChild(lleg);

	auto rleg = make_shared<CImageDrawable>(L"Right Leg", L"images/girl_rleg.png");
	rleg->SetCenter(Point(35, 9));
	rleg->SetPosition(Point(-27, 0));
	dress->AddChild(rleg);

	auto headb = make_shared<CImageDrawable>(L"Head Bottom", L"images/girl_headb.png");
	headb->SetCenter(Point(44, 31));
	headb->SetPosition(Point(0, -130));
	dress->AddChild(headb);


	auto headt = make_shared<CHeadTop>(L"Head Top", L"images/girl_headt.png");
	headt->SetCenter(Point(75, 112));
	headt->SetPosition(Point(0, -31));
	headt->GetLeftEye()->LoadImage(L"images/eye.png");
	headt->GetLeftEye()->SetCenter(Point(0, 11));
	headt->GetRightEye()->LoadImage(L"images/eye.png");
	headt->GetRightEye()->SetCenter(Point(0, 11));
	headb->AddChild(headt);

	auto rarm = make_shared<CPolyDrawable>(L"Right Arm");
	rarm->SetColor(Color(208, 159, 118));
	rarm->SetPosition(Point(-43, -130));
	rarm->AddPoint(Point(-7, -7));
	rarm->AddPoint(Point(-7, 96));
	rarm->AddPoint(Point(8, 96));
	rarm->AddPoint(Point(8, -7));
	dress->AddChild(rarm);

	auto larm = make_shared<CPolyDrawable>(L"Left Arm");
	larm->SetColor(Color(208, 159, 118));
	larm->SetPosition(Point(50, -130));
	larm->AddPoint(Point(-7, -7));
	larm->AddPoint(Point(-7, 96));
	larm->AddPoint(Point(8, 96));
	larm->AddPoint(Point(8, -7));
	dress->AddChild(larm);

	auto rhand = make_shared<CPolyDrawable>(L"Right Hand");
	rhand->SetColor(Color(208, 159, 118));
	rhand->SetPosition(Point(2, 90));
	rhand->AddPoint(Point(-12, -2));
	rhand->AddPoint(Point(-12, 17));
	rhand->AddPoint(Point(11, 17));
	rhand->AddPoint(Point(11, -2));
	rarm->AddChild(rhand);

	auto lhand = make_shared<CPolyDrawable>(L"Left Hand");
	lhand->SetColor(Color(208, 159, 118));
	lhand->SetPosition(Point(0, 90));
	lhand->AddPoint(Point(-12, -2));
	lhand->AddPoint(Point(-12, 17));
	lhand->AddPoint(Point(11, 17));
	lhand->AddPoint(Point(11, -2));
	larm->AddChild(lhand);

	auto mug = make_shared<CImageDrawable>(L"Beer mug", L"images/mug.png");
	mug->SetCenter(Point(4, 24));
	mug->SetPosition(Point(10, 5));
	lhand->AddChild(mug);


    actor->AddDrawable(larm);
    actor->AddDrawable(rarm);
    actor->AddDrawable(rhand);
    actor->AddDrawable(lhand);
    actor->AddDrawable(rleg);
    actor->AddDrawable(lleg);
    actor->AddDrawable(dress);
    actor->AddDrawable(headb);
    actor->AddDrawable(headt);
	actor->AddDrawable(mug);

    return actor;
}
