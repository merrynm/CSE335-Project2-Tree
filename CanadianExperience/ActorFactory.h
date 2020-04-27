/**
 * \file ActorFactory.h
 *
 * \author Charles B. Owen
 *
 * Abstract base class for actor factories.
 */

#pragma once

#include <memory>
#include "Actor.h"

/** 
 * Abstract base class for actor factories. 
 */
class CActorFactory
{
public:
    virtual ~CActorFactory();

    /** Create the actor 
     * \returns New actor object */
    virtual std::shared_ptr<CActor> Create() = 0;

protected:
    CActorFactory();
};

