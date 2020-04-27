/**
 * \file Branch.h
 *
 * \author Merryn Marderosian
 *
 * This is the class that implements the root and branches of the tree.
 *
 */

#pragma once
#include "TreeItem.h"

#include <memory>
#include <string>
#include <vector>


/// The branch class
class CBranch :
	public CTreeItem
{
public:
	CBranch();

	/** \brief Copy constructor disabled */
	CBranch(const CBranch&) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CBranch&) = delete;

	virtual ~CBranch();

	virtual void Update() override;

	void DrawItem(Gdiplus::Graphics* graphics, double angle, double x, double y) override;

	virtual void UpdateWind(double speedConst) override;

	/** Iterator that iterates over the actors in a picture */
	class BranchIter
	{
	public:
		/** Constructor
		* \param branch Picture we are iterating
		* \param pos Starting position */
		BranchIter(CBranch* branch, int pos) : mBranch(branch), mPos(pos) {}

		/** Test for end of the iterator
		* \param other Other object to test against
		* \returns True if we this position equals not equal to the other position */
		bool operator!=(const BranchIter& other) const
		{
			return mPos != other.mPos;
		}

		/** Get value at current position
		* \returns Value at mPos in the collection */
		std::shared_ptr<CTreeItem> operator *() const { return mBranch->mChildren[mPos]; }

		/** Increment the iterator
		* \returns Reference to this iterator */
		const BranchIter& operator++()
		{
			mPos++;
			return *this;
		}

	private:
		CBranch* mBranch; ///< Picture we are iterating over
		int mPos;           ///< Position in the collection
	};

	/** Get an iterator for the beginning of the collection
	* \returns Iter object at position 0 */
	BranchIter begin() { return BranchIter(this, 0); }

	/** Get an iterator for the end of the collection
	* \returns Iter object at position past the end */
	BranchIter end() { return BranchIter(this, mChildren.size()); }

	void SetAngle(double angle) override;

	/// Returns the current angle of the branch
	/// \returns mAngle the angle
	double GetAngle() { return mAngle; }

	/// Sets this branch's tree
	/// \param tree The branch's tree
	void SetTree(CActualTree* tree) override { mTree = tree; }

	/// Sets the depth of this branch
	/// \param depth The depth we are setting
	void SetDepth(int depth) override { mDepth = depth; }

	/// Sets the X location of the root
	/// \param x The x location we are setting
	void SetX(double x) { mRootX = x; }

	/// sets the y location of the root
	/// \param y The y location we are setting
	void SetY(double y) { mRootY = y; }

	///Gets the X root location
	/// \return the root x location
	double GetX() { return mRootX; }

	///Gets the Y root location
	/// \return the root y location
	double GetY() { return mRootY; }

	/// Gets the vector of children
	/// \return the vector of children
	std::vector<std::shared_ptr<CTreeItem>> GetChildren() { return mChildren; }

	void Harvest(CIsFruitVisitor *visitor)override;

	/// Accept a visitor
	/// \param visitor The visitor for this object
	void Accept(CItemVisitor* visitor) override { visitor->VisitBranch(this); }

private:
	///The starting branch width
	double mWidth = 1;

	///The maximum branch width
	double mMaxWidth = 30;

	///The starting length of a branch
	double mLength = 5;

	///The maximum Y value
	double mMaxLength = 150;

	///The current depth
	int mDepth = 0;

	/// The parent's angle
	double mAngle = 0;

	/// The offset angle
	double mOffsetAngle = 0;

	///Starting root x location
	double mRootX = 0;

	///Starting root y location
	double mRootY = 0;

	/// Children branches
	std::vector<std::shared_ptr<CTreeItem>> mChildren;

	///The tree this brancg belongs to
	CActualTree* mTree = nullptr;
};

