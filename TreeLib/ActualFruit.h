/**
 * \file ActualFruit.h
 *
 * \author Merryn Marderosian
 *
 * The class for the tree's fruit
 */

#pragma once
#include "TreeItemImage.h"
#include "Fruit.h"

/// The tree fruit class
class CActualFruit :
	public CTreeItemImage, public CFruit
{
public:
	CActualFruit();
	~CActualFruit();

	/** \brief Copy constructor disabled */
	CActualFruit(const CActualFruit&) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CActualFruit&) = delete;

	virtual void Update() override;

	void DrawItem(Gdiplus::Graphics* graphics, double angle, double x, double y) override;

	/// Set the angle of the fruit
	/// \param angle The angle we are setting
	void SetAngle(double angle) override { mAngle = angle; }

	/// Set the tree this fruit belongs to
	/// \param tree The tree this fruit belongs to
	void SetTree(CActualTree* tree) override { mTree = tree; }

	/// Set the depth of this fruit
	/// \param depth The depth of this fruit in the tree
	void SetDepth(int depth) override { mDepth = depth; }

	/// Accept a visitor
	/// \param visitor The visitor for this object
	virtual void Accept(CItemVisitor* visitor) override;

	/**
	* Set the position of the fruit in the basket
	*
	* This position is relative to the basket, so
	* it will be added to the basket location passed
	* to DrawInBasket when we draw it
	* \param x X position in pixels
	* \param y Y position in pixels
	*/
	virtual void SetBasketPosition(int x, int y){}

	/**
	 * Draw the fruit in the basket
	 * \param graphics The graphics object to draw on
	 * \param x X location of the basket
	 * \param y Y location of the basket
	 */
	virtual void DrawInBasket(Gdiplus::Graphics* graphics, int x, int y) ;

private:
	/// The image of this fruit
	std::shared_ptr<Gdiplus::Bitmap> mFruitImage;

	///The tree this leaf is part of
	CActualTree* mTree = nullptr;

	///The current depth
	int mDepth = 0;

	/// The parent's angle
	double mAngle = 0;

	///The current scale of the image
	double mScale = 0.01;
};

