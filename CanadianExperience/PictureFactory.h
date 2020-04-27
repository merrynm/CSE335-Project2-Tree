/**
 * \file PictureFactory.h
 *
 * \author Charles B. Owen
 *
 * A factory class that builds our picture.
 */

#pragma once

#include <memory>

#include "Picture.h"

/**
 * A factory class that builds our picture.
 */
class CPictureFactory
{
public:
    CPictureFactory();
    virtual ~CPictureFactory();

    std::shared_ptr<CPicture> Create();
};

