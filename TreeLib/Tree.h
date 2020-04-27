/**
 * \file Tree.h
 *
 * \author Charles Owen
 *
 * Class that represents a tree.
 *
 * You are not allowed to change this class in any way!
 */

#pragma once

#include <vector>
#include <memory>

class CFruit;
class CTreeStandin;

/**
 * Class that represents a tree.
 *
 * This uses a standin class to provide a way to develop
 * the adapter class first if you so choose.
 *
 * You are not allowed to change this class in any way!
 *
 * AFX_EXT_CLASS is a Microsoft directive that indicates
 * that this class can be used outside the DLL. Do not change
 * it or add it to any other classes.
 */
class AFX_EXT_CLASS CTree
{
public:
    /// Constructor
    CTree();

    /// Destructor
    virtual ~CTree() {}

    /// Copy constructor/disabled
    CTree(const CTree &) = delete;

    /// Assignment operator/disabled
    void operator=(const CTree &) = delete;

    /**
    * Set the position for the root of the tree
    * \param x X location (pixels)
    * \param y Y location (pixels)
    */
    virtual void SetRootLocation(int x, int y);

    /**
    * Draw the tree at the currently specified location
    * \param graphics GDI+ Graphics object
    */
    virtual void DrawTree(Gdiplus::Graphics *graphics);

    /**
    * Set the current tree frame
    * \param frame Frame number
    */
    virtual void SetTreeFrame(int frame);

    /**
    * Set  the wind speed
    * \param speed Wind speed in miles per hour
    */
    virtual void SetWindSpeed(double speed);

    /**
    * Set the tree seed
    * \param seed An integer number. Each number makes a different tree
    */
    virtual void SetSeed(int seed);

    /**
     * Get the current tree seed
     * \return Tree seed integer
     */
    virtual int GetSeed();

    /**
     * Harvest all of the fruit
     * \return Vector of objects of type CFruit
     */
    virtual std::vector<std::shared_ptr<CFruit>> Harvest();

private:
    /**
     * A stand-in tree class. 
     *
     * This draws simple stand-in graphics
     * so you can see where the tree will be and what its state
     * is. This makes it easy to develop code that uses the
     * tree before you have the tree working.
     *
     * And no, you may not change this to point to your
     * tree implementation!
     */
    std::shared_ptr<CTreeStandin> mStandin;
};

