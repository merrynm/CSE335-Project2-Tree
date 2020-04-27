/**
 * \file AnimChannelAngle.cpp
 *
 * \author Charles B. Owen
 */

#include "pch.h"
#include "AnimChannelAngle.h"
#include "Timeline.h"

using namespace std;

/**
 * Constructor
 */
CAnimChannelAngle::CAnimChannelAngle()
{
}


/**
 * Destructor
 */
CAnimChannelAngle::~CAnimChannelAngle()
{
}


/**
* Set a keyframe
*
* This function allocates a new keyframe and sends it to
* CAnimChannel, which will insert it into the collection of keyframes.
* \param angle Angle for the keyframe.
*/
void CAnimChannelAngle::SetKeyframe(double angle)
{
    // Create a keyframe of the appropriate type
    // Telling it this channel and the angle
    shared_ptr<KeyframeAngle> keyframe = make_shared<KeyframeAngle>(this, angle);

    // Insert it into the collection
    InsertKeyframe(keyframe);
}


/**
 * Tween between two angle keyframes
 * \param t The t value between the frames
 */
void CAnimChannelAngle::Tween(double t)
{
    mAngle = mKeyframe1->GetAngle() * (1 - t) +
        mKeyframe2->GetAngle() * t;
}

/** Save this keyframe to an XML node
* \param node The node we are going to be a child of
* \returns Allocated XML node.
*/
std::shared_ptr<xmlnode::CXmlNode> CAnimChannelAngle::KeyframeAngle::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
    auto itemNode = CAnimChannel::Keyframe::XmlSave(node);
    itemNode->SetAttribute(L"angle", mAngle);

    return itemNode;
}



/**
* Handle loading this channel's keyframe type
* \param node keyframe tag node
*/
void CAnimChannelAngle::XmlLoadKeyframe(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
    double angle = node->GetAttributeDoubleValue(L"angle", 0);

    // Set a keyframe there
    SetKeyframe(angle);
}


CAnimChannelAngle::KeyframeAngle::~KeyframeAngle()
{

}