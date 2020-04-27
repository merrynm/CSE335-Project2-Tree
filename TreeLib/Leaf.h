/**
 * \file Leaf.h
 *
 * \author Merryn Marderosian
 *
 */

#pragma once
#include "TreeItemImage.h"

/// The leaf class
class CLeaf :
	public CTreeItemImage
{
public:
	CLeaf();
	~CLeaf();

	/** \brief Copy constructor disabled */
	CLeaf(const CLeaf&) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CLeaf&) = delete;

	virtual void Update() override;

	void DrawItem(Gdiplus::Graphics* graphics, double angle, double x, double y) override;

	/// Sets the angle
	/// \param angle The angle we are setting
	void SetAngle(double angle) override { mAngle = angle; }

	/// Sets the tree
	/// \param tree The tree we are setting
	void SetTree(CActualTree* tree) override { mTree = tree; }

	/// Sets the depth
	/// \param depth The depth we are setting
	void SetDepth(int depth) override { mDepth = depth; }

	/// Accept a visitor
	/// \param visitor The visitor for this object
	virtual void Accept(CItemVisitor* visitor) override { visitor->VisitLeaf(this); }

private:
	///The leaf image
	std::shared_ptr<Gdiplus::Bitmap> mLeafImage;

	///The tree this leaf is part of
	CActualTree* mTree = nullptr;

	///The current depth
	int mDepth = 0;

	/// The parent's angle
	double mAngle = 0;

	///The current scale of the image
	double mScale = 0.01;
};

