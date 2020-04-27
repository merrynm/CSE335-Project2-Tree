/**
* \file ItemVisitor.h
*
* \author Merryn Marderosian
*
* Visitor Base Class
*/

#pragma once

class CLeaf;
class CBranch;
class CFruit;
class CActualFruit;

/// The item visitor base class
class CItemVisitor
{
public:
	/// destructor
	virtual ~CItemVisitor() {};

	/** Visit a CLeaf object
	* \param leaf The Leaf we are visiting*/
	virtual void VisitLeaf(CLeaf* leaf) {};

	/** Visit a Branch object
	* \param branch The Branch we are visiting*/
	virtual void VisitBranch(CBranch* branch) {};

	/** Visit a CFruit object
	* \param fruit The Fruit we are visiting*/
	virtual void VisitFruit(CActualFruit* fruit) {};

	/// Resets all data for the visitor
	virtual void Reset() = 0;
};

