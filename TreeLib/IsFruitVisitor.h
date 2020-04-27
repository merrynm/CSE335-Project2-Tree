/**
 * \file IsFruitVisitor.h
 *
 * \author Merryn Marderosian
 */

#pragma once
#include "ItemVisitor.h"

/// Class that determines if a visitor is a fruit visitor
class CIsFruitVisitor :
	public CItemVisitor
{
public:
	/// Constructor
	CIsFruitVisitor() { mIsFruit = false; }

	/** Visit Fruit object
	* \param fruit The Fruit we're looking at */
	virtual void VisitFruit(CActualFruit* fruit) override;

	/** Checks if visitor is fruit visitor
	* \return bool mIsFruit */
	bool IsFruitVisitor() { return mIsFruit; }

	/// Resets member data
	void Reset() override { mIsFruit = false; }

private:
	/// bool of whether visited object is a fruit
	bool mIsFruit = false;
};

