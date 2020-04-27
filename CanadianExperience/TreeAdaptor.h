/**
 * \file /CanadianExperience/CanadianExperience/TreeAdaptor.h
 *
 * \author Merryn Marderosian
 *
 */

#pragma once
#include "Drawable.h"
#include "Tree.h"

///The tree adaptor class
class CTreeAdaptor : public CDrawable
{
public:
	CTreeAdaptor(const std::wstring& name);
	~CTreeAdaptor();

	/** \brief Default constructor disabled */
	CTreeAdaptor() = delete;
	/** \brief Copy constructor disabled */
	CTreeAdaptor(const CTreeAdaptor&) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CTreeAdaptor&) = delete;

	virtual void Draw(Gdiplus::Graphics* graphics) override;

	///Overridden hittest, not needed.
	///\param pos The position
	///\return bool false.
	virtual bool HitTest(Gdiplus::Point pos) override { return false; }

	virtual void SetTimeline(CTimeline* timeline) override;

	///Sets the starting frame to grow
	///\param start The starting frame
	void SetStart(int start) { mStart = start; }

	void SetSeed(int seed);

private:
	///The starting time
	double mStartTime = 0;

	///The harvesting time
	double mHarvestTime = 0;

	///Pointer to our tree
	std::shared_ptr<CTree> mTree = nullptr;

	///Pointer to the Timeline object
	CTimeline* mTimeline;

	///The start frame
	int mStart = 0;
};

