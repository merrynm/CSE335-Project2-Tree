/**
 * \file TreeItemImage.h
 *
 * \author Merryn Marderosian
 *
 */

#pragma once
#include "TreeItem.h"

///The class for our tree items represented by images.
class CTreeItemImage :
	public CTreeItem
{
public:
	CTreeItemImage();
	~CTreeItemImage();

	/** \brief Copy constructor disabled */
	CTreeItemImage(const CTreeItemImage&) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CTreeItemImage&) = delete;

	virtual void Update();

	void Harvest(CIsFruitVisitor *visitor);

	virtual void DrawItem(Gdiplus::Graphics* graphics, double angle, double x, double y);

	/// Sets the angle
	/// \param angle The angle to set
	virtual void SetAngle(double angle) {}

	/// Sets the parent Tree
	/// \param tree The tree to set
	virtual void SetTree(CActualTree* tree) {}

	/// Sets the depth
	/// \param depth The depth to seet
	virtual void SetDepth(int depth) {}

	/// Accept a visitor
	/// \param visitor The visitor for this object
	virtual void Accept(CItemVisitor* visitor) override = 0;
};

