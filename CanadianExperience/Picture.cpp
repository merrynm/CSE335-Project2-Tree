/**
 * \file Picture.cpp
 *
 * \author Charles B. Owen
 */

#include "pch.h"
#include "Picture.h"
#include "Actor.h"

using namespace Gdiplus;
using namespace xmlnode;

/**
 * Constructor
 */
CPicture::CPicture()
{
}


/**
 * Destructor
 */
CPicture::~CPicture()
{
}

/** Set the current animation time
*
* This forces the animation of all
* objects to the current animation location.
* \param time The new time.
*/
void CPicture::SetAnimationTime(double time)
{
    mTimeline.SetCurrentTime(time);
    UpdateObservers();

    for (auto actor : mActors)
    {
        actor->GetKeyframe();
    }
}

/** Add an observer to this picture.
* \param observer The observer to add
*/
void CPicture::AddObserver(CPictureObserver *observer)
{
    mObservers.push_back(observer);
}

/** Remove an observer from this picture
* \param observer The observer to remove
*/
void CPicture::RemoveObserver(CPictureObserver *observer)
{
    auto loc = find(std::begin(mObservers), std::end(mObservers), observer);
    if (loc != std::end(mObservers))
    {
        mObservers.erase(loc);
    }
}

/** Update all observers to indicate the picture has changed.
*/
void CPicture::UpdateObservers()
{
    for (auto observer : mObservers)
    {
        observer->UpdateObserver();
    }
}

/** Draw this picture on a device context
* \param graphics The device context to draw on
*/
void CPicture::Draw(Gdiplus::Graphics *graphics)
{
    for (auto actor : mActors)
    {
        actor->Draw(graphics);
    }
}


/** Add an actor to this picture.
* \param actor The actor to add
*/
void CPicture::AddActor(std::shared_ptr<CActor> actor)
{
    mActors.push_back(actor);
    actor->SetPicture(this);
}

/** Get the current animation time.
* \returns The current animation time
*/
double CPicture::GetAnimationTime()
{
    return mTimeline.GetCurrentTime();
}


/**
* Save the picture animation to a file
* \param filename File to save to.
*/
void CPicture::Save(const std::wstring &filename)
{
    //
    // Create an XML document
    //
    auto root = CXmlNode::CreateDocument(L"anim");

    // Save the timeline animation into the XML
    mTimeline.Save(root);

    //
    // It is possible to add attributes to the root node here
    //
    //root->SetAttribute(L"something", mSomething);

    try
    {
        root->Save(filename);
    }
    catch (CXmlNode::Exception ex)
    {
        AfxMessageBox(ex.Message().c_str());
    }
}



/**
* Load a picture animation from a file
* \param filename file to load from
*/
void CPicture::Load(const std::wstring &filename)
{
    // We surround with a try/catch to handle errors
    try
    {
        // Open the document to read
        auto root = CXmlNode::OpenDocument(filename);
        
        // Load the animation from the XML
        mTimeline.Load(root);

        //
        // It is possible to load attributes from the root node here
        //
        // mSomething = root->GetAttributeIntValue(L"something", 123);

        SetAnimationTime(0);
        UpdateObservers();
    }
    catch (CXmlNode::Exception ex)
    {
        AfxMessageBox(ex.Message().c_str());
    }

}
