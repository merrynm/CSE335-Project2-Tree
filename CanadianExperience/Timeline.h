/**
 * \file Timeline.h
 *
 * \author Charles B. Owen
 *
 * The animation timeline class.
 */

#pragma once

#include <vector>

#include "AnimChannel.h"
#include "XmlNode.h"

/**
 * The animation timeline class.
 */
class CTimeline
{
public:
    CTimeline();
    virtual ~CTimeline();

    /** Copy constructor disabled */
    CTimeline(const CTimeline &) = delete;
    /** Assignment operator disabled */
    void operator=(const CTimeline &) = delete;

    /** Get the number of frames in the animation
    * \returns Number of frames in the animation
    */
    int GetNumFrames() const { return mNumFrames; }

    /** Set the number of frames in the animation
    * \param numFrames Number of frames in the animation
    */
    void SetNumFrames(int numFrames) { mNumFrames = numFrames; }

    /** Get the frame rate
    * \returns Animation frame rate in frames per second
    */
    int GetFrameRate() const { return mFrameRate; }

    /** Set the frame rate
    * \param frameRate Animation frame rate in frames per second
    */
    void SetFrameRate(int frameRate) { mFrameRate = frameRate; }

    /** Get the current time
    * \returns Current animation time in seconds
    */
    double GetCurrentTime() const { return mCurrentTime; }

    void SetCurrentTime(double t);


    /** Get the current frame.
    *
    * This is the frame associated with the current time
    * \returns Current frame
    */
    int GetCurrentFrame() const { return int(mCurrentTime * mFrameRate); }

    /** Get the animation duration
    * \returns Animation duration in seconds
    */
    double GetDuration() const { return (double)mNumFrames / mFrameRate; }
    void AddChannel(CAnimChannel *channel);
    void ClearKeyframe();

    void Save(std::shared_ptr<xmlnode::CXmlNode> root);
    void Load(std::shared_ptr<xmlnode::CXmlNode> root);

    void Clear();

private:
    void XmlChannel(const std::shared_ptr<xmlnode::CXmlNode> &node);

    int mNumFrames = 300;       ///< Number of frames in the animation
    int mFrameRate = 30;        ///< Animation frame rate in frames per second
    double mCurrentTime = 0;    ///< The current animation time

    /// List of all animation channels
    std::vector<CAnimChannel *> mChannels;

};

