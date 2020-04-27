/**
 * \file TreeStandin.h
 *
 * \author Charles Owen
 *
 * This class is a stand-in class that will allow you to
 * develop the tree adapter class first if you so choose.
 *
 * You are not allowed to change this class in any way!
 */

#pragma once

#include <string>
#include <vector>
#include <memory>

class CFruit;


/**
 * This class is a stand-in class that will allow you to
 * develop the tree adapter class first if you so choose.
 *
 * You are not allowed to change this class in any way!
 */
class CTreeStandin
{
public:
    CTreeStandin();
    virtual ~CTreeStandin();

    /**
    * Set the position for the root of the tree
    * \param x X location (pixels)
    * \param y Y location (pixels)
    */
    void SetRootLocation(int x, int y) { mX = x; mY = y; }

    void DrawTree(Gdiplus::Graphics *graphics);

    /**
    * Set the current tree frame
    * \param frame Frame number
    */
    void SetTreeFrame(int frame) { mFrame = frame; mHarvested = false; }

    /**
    * Set  the wind speed
    * \param speed Wind speed in miles per hour
    */
    void SetWindSpeed(double speed) { mWindSpeed = speed; }

    /**
    * Set the tree seed
    * \param seed An integer number. Each number makes a different tree
    */
    void SetSeed(int seed) { mSeed = seed; }

    /**
    * Get the current tree seed
    * \return Tree seed integer
    */
    virtual int GetSeed() { return mSeed; }

    /**
    * Harvest all of the fruit
    * \return Vector of objects of type CFruit
    */
    std::vector<std::shared_ptr<CFruit>> Harvest()
    {
        mHarvested = true;
        return std::vector<std::shared_ptr<CFruit>>();
    }

private:
    void CenteredString(Gdiplus::Graphics *graphics, const std::wstring &str, int x, int y, int dy);

    int mX = 0;     ///< Tree X location
    int mY = 0;     ///< Tree Y location
    int mFrame = 0; ///< Current frame
    double mWindSpeed = 0;  ///< Wind speed
    int mSeed = 0;  ///< Tree seed
    bool mHarvested = false;    ///< Has it been harvested?
};

