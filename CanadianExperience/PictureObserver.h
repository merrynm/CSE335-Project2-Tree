/**
 * \file PictureObserver.h
 *
 * \author Charles B. Owen
 *
 * Observer base class for a picture
 */

#pragma once

class CPicture;

#include <memory>

/**
 * Observer base class for a picture.
 *
 * This class implements the base class functionality for
 * an observer in the observer pattern.
 */
class CPictureObserver
{
public:
    virtual ~CPictureObserver();

    /// Copy Constructor (Disabled)
    CPictureObserver(const CPictureObserver &) = delete;
    /// Assignment Operator (Disabled)
    /// \return none
    CPictureObserver &operator=(const CPictureObserver &) = delete;

    /// This function is called to update any observers
    virtual void UpdateObserver() = 0;

    void CPictureObserver::SetPicture(std::shared_ptr<CPicture> picture);

    /** Get the picture this observer is associated with 
     * \return CPicture object */
    std::shared_ptr<CPicture> GetPicture() { return mPicture;  }

protected:
    CPictureObserver();

private:
    /// Picture we are observing
    std::shared_ptr<CPicture> mPicture;
};

