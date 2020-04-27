/**
 * \file TreeItem.h
 * \author Merryn Marderosian
 *
 */

#pragma once

#include <memory>
#include <vector>
#include <string>
#include "ActualTree.h"
#include "ItemVisitor.h"
#include "IsFruitVisitor.h"

//class CActualTree;
///The tree items class
class CTreeItem
{

public:
	CTreeItem();

	/** \brief Copy constructor disabled */
	CTreeItem(const CTreeItem&) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CTreeItem&) = delete;

	//virtual void Accept(CItemVisitor visitor);
	virtual void Update();
	virtual void Harvest(CIsFruitVisitor *visitor);
	virtual void DrawItem(Gdiplus::Graphics* graphics, double angle, double x, double y);

	/// Updates the wind speed
	/// \param speedConst the wind speed
	virtual void UpdateWind(double speedConst) {};

	/// Sets the angle
	/// \param angle The angle we are setting
	virtual void SetAngle(double angle) {}

	/// Sets the Tree
	/// \param tree The Tree we are setting
	virtual void SetTree(CActualTree* tree) {}

	/// Sets the Depth
	/// \param depth The depth we are setting
	virtual void SetDepth(int depth) {}

	/// Accept a visitor
	/// \param visitor The visitor for this object
	virtual void Accept(CItemVisitor* visitor) =0;
};

