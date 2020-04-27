/**
 * \file TreeFactory.cpp
 *
 * \author Charles Owen
 *
 * You are allowed to change this file.
 */

#include "pch.h"
#include "TreeFactory.h"
#include "Tree.h"
#include "Basket.h"
#include "ActualTree.h"
#include "ActualBasket.h"

using namespace std;

/**
 * Constructor
 */
CTreeFactory::CTreeFactory()
{
}


/**
 * Destructor
 */
CTreeFactory::~CTreeFactory()
{
}


/**
 * Create a Tree object
 * \returns Object of type CTree
 */
std::shared_ptr<CTree> CTreeFactory::CreateTree()
{
    return make_shared<CActualTree>();
}


/**
 * Create a Basket object
 * \returns Object of type CBasket
 */
std::shared_ptr<CBasket> CTreeFactory::CreateBasket()
{
    return make_shared<CActualBasket>();
}
