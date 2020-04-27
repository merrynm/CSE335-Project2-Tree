/**
 * \file /CanadianExperience/TreeLib/ActualTree.h
 *
 * \author Merryn Marderosian
 *
 * This is the class that implements the actual tree.
 *
 */

#pragma once
#include "Tree.h"
#include "PseudoRandom.h"

class CBranch;

///The actual tree class
class CActualTree :
	public CTree
{

public:
	CActualTree();

	/// Destructor
	virtual ~CActualTree() {}

	/** \brief Copy constructor disabled */
	CActualTree(const CActualTree&) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CActualTree&) = delete;

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
	virtual void DrawTree(Gdiplus::Graphics* graphics);

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

	/// Gets delta
	/// \return delta
	double GetDelta() { return mDelta; }

	/// Gets the random object
	/// \return the random object
	CPseudoRandom* GetRandom() { return &mRandom; }

	/// Gets the current frame
	/// \return the current frame
	int GetFrame() { return mCurrFrame; }

	void Reset();

	/// Returns the wind speed
	/// \return thw wind speed
	double GetWind() { return mWindSpeed; }

	/// Gets the leaf image
	/// \return the leaf imge
	std::shared_ptr<Gdiplus::Bitmap> GetLeafImage() { return mLeafImage; }

	/// Gets the fruit image
	/// \return the fruit image
	std::shared_ptr<Gdiplus::Bitmap> GetFruitImage() { return mFruitImage; }

	//Add a fruit to the fruit vector
	/// \param fruit The fruit we are adding
	void AddFruit(std::shared_ptr<CFruit> fruit) { mFruits.push_back(fruit); }

	///Set the current maximum depth of the tree
	/// \param depth The max depth
	void SetMaxDepth(int depth) { mMaxDepth = depth; }

	///Get the current maximum depth of the tree
	/// \return the max depth
	int GetMaxDepth() { return mMaxDepth; }

private:
	///The tree's root
	std::shared_ptr<CBranch> mRoot;

	///The current frame
	int mCurrFrame = 0;

	/// The current speed
	double mWindSpeed = 0;

	/// Delta
	double mDelta = 1.0 / 30.0;

	/// the Random object
	CPseudoRandom mRandom;

	/// This tree's seed
	int mSeed;

	/// The image of the Leaf
	std::shared_ptr<Gdiplus::Bitmap> mLeafImage;

	/// The image of the fruit
	std::shared_ptr<Gdiplus::Bitmap> mFruitImage;

	///The vector of fruits
	std::vector<std::shared_ptr<CFruit>> mFruits;

	///The current maximum depth
	int mMaxDepth = 0;
};

