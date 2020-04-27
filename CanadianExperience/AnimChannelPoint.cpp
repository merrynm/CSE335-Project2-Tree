/**
 * \file AnimChannelPoint.cpp
 *
 * \author Charles B. Owen
 */

#include "pch.h"
#include "AnimChannelPoint.h"
#include "Timeline.h"

using namespace std;
using namespace Gdiplus;


/**
 * Constructor
 */
CAnimChannelPoint::CAnimChannelPoint()
{
}


/**
 * Destructor
 */
CAnimChannelPoint::~CAnimChannelPoint()
{
}



/**
* Set a keyframe
*
* This function allocates a new keyframe and sends it to
* CAnimChannel, which will insert it into the collection of keyframes.
* \param point The point for the keyframe
*/
void CAnimChannelPoint::SetKeyframe(Gdiplus::Point point)
{
    // Create a keyframe of the appropriate type
    // Telling it this channel and the angle
    shared_ptr<KeyframePoint> keyframe = make_shared<KeyframePoint>(this, point);

    // Insert it into the collection
    InsertKeyframe(keyframe);
}

/** Compute a tweened point between to points
 * \param t The tweening t value 
 */
void CAnimChannelPoint::Tween(double t)
{
    Point a = mKeyframe1->GetPoint();
    Point b = mKeyframe2->GetPoint();

    mPoint = Point(int(a.X + t * (b.X - a.X)), int(a.Y + t * (b.Y - a.Y)));
}


/** Save this keyframe to an XML node
* \param node The node we are going to be a child of
* \returns Allocated XML node.
*/
std::shared_ptr<xmlnode::CXmlNode> CAnimChannelPoint::KeyframePoint::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
    auto itemNode = CAnimChannel::Keyframe::XmlSave(node);
    itemNode->SetAttribute(L"x", mPoint.X);
    itemNode->SetAttribute(L"y", mPoint.Y);

    return itemNode;
}



/**
* Handle loading this channel's keyframe type
* \param node keyframe tag node
*/
void CAnimChannelPoint::XmlLoadKeyframe(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
    int x = node->GetAttributeIntValue(L"x", 0);
    int y = node->GetAttributeIntValue(L"y", 0);

    // Set a keyframe there
    SetKeyframe(Gdiplus::Point(x, y));
}



