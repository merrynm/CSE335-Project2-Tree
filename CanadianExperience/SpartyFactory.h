/**
 * \file SpartyFactory.h
 *
 * \author Charles B. Owen
 *
 * Factory that builds the Sparty actor.
 */

#pragma once
#include "ActorFactory.h"


/**
 * Factory that builds the Sparty actor.
 */
class CSpartyFactory :
    public CActorFactory
{
public:
    CSpartyFactory();
    virtual ~CSpartyFactory();

    std::shared_ptr<CActor> Create();

};

