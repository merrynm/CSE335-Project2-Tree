/**
 * \file AnimChannel.h
 *
 * \author Charles B. Owen
 *
 * Base class for an animation channel
 */

#pragma once

#include <string>
#include <vector>
#include <memory>
#include "XmlNode.h"

class CTimeline;

/**
 * Base class for an animation channel
 */
class CAnimChannel
{
public:
    CAnimChannel();
    virtual ~CAnimChannel();

    /** Copy constructor disabled */
    CAnimChannel(const CAnimChannel &) = delete;
    /** Assignment operator disabled */
    void operator=(const CAnimChannel &) = delete;

    /** Set the channel name 
     * \param name The new name to set */
    void SetName(const std::wstring &name) { mName = name; }

    /** Get the channel name
     * \return Channel name */
    std::wstring GetName() const { return mName; }

    /** Set the timeline for this channel 
     * \param timeline The timeline to use */
    void SetTimeline(CTimeline *timeline) { mTimeline = timeline; }

    /** Get the timeline for this channel 
     * \returns The timeline pointer */
    CTimeline *GetTimeline() { return mTimeline; }


    void SetFrame(int currFrame);

    /** Class that represents a keyframe */
    class Keyframe
    {
    public:
        /** Default constructor disabled */
        Keyframe() = delete;
        /** Copy constructor disabled */
        Keyframe(const Keyframe &) = delete;
        /** Assignment operator disabled */
        void operator=(const Keyframe &) = delete;

        /** Get the frame for this keyframe 
         * \returns The keyframe frame number */
        int GetFrame() const { return mFrame; }

        /** Set the frame for this keyframe 
         * \param f The new frame number to set */
        void SetFrame(int f) { mFrame = f; }

        /// Indicates this keyframe is used as Keyframe1
        virtual void UseAs1() = 0;

        /// Indicates this keyframe is used as Keyframe2
        virtual void UseAs2() = 0;

        /// Indicates this is the only keyframe
        virtual void UseOnly() = 0;

        virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node);

    private:
        /// The channel this keyframe is associated with
        CAnimChannel *mChannel;

    protected:
        /** Constructor
        * \param channel Channel we are associated with */
        Keyframe(CAnimChannel *channel) : mChannel(channel) {}

        int mFrame; ///< The frame number for the keyframe
    };

    /** Is the channel valid, meaning has keyframes?
    * \returns true if the channel is valid. */
    bool IsValid() { return mKeyframe1 >= 0 || mKeyframe2 >= 0; }
    void ClearKeyframe();

    virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node);
    virtual void Clear();

    virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node);


protected:
    void InsertKeyframe(std::shared_ptr<Keyframe> keyframe);

    /** Channel type specific loading and keyframe creation 
     * \param node Node to load from */
    virtual void XmlLoadKeyframe(const std::shared_ptr<xmlnode::CXmlNode> &node) = 0;

    /** Tween between two keyframes 
     * \param t The T value (0 to 1) */
    virtual void Tween(double t) = 0;

private:
    std::wstring mName;     ///< The channel name
    int mKeyframe1 = -1;    ///< The first keyframe
    int mKeyframe2 = -1;    ///< The second keyframe

    /// The timeline object
    CTimeline *mTimeline = nullptr;

    /// The collection of keyframes for this channel
    std::vector<std::shared_ptr<Keyframe>> mKeyframes;
};

