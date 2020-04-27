/**
 * \file IsFruitVisitor.cpp
 *
 * \author Merryn Marderosian
 */

#include "pch.h"
#include "IsFruitVisitor.h"

/*
* Visits a CFruit object
*/
void CIsFruitVisitor::VisitFruit(CActualFruit* fruit)
{
	mIsFruit = true;
}
