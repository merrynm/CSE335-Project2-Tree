/**
 * \file /CanadianExperience/CanadianExperience/BasketAdaptor.h
 *
 * \author Merryn Marderosian
 *
 */

#pragma once
#include "Drawable.h"
#include "Tree.h"
#include "Basket.h"

///The basket adaptor class
class CBasketAdaptor : public CDrawable
{
public:
	CBasketAdaptor(const std::wstring& name);
	~CBasketAdaptor();

	/** \brief Default constructor disabled */
	CBasketAdaptor() = delete;
	/** \brief Copy constructor disabled */
	CBasketAdaptor(const CBasketAdaptor&) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CBasketAdaptor&) = delete;

	virtual void Draw(Gdiplus::Graphics* graphics) override;

	///Overridden hittest, not needed.
	///\param pos The position
	///\return bool false.
	virtual bool HitTest(Gdiplus::Point pos) override { return false; }

private:
	///The basket pointer
	std::shared_ptr<CBasket> mBasket;

	///The timeline object
	CTimeline* mTimeline;
};
