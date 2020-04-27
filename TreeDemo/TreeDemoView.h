/**
 * \file TreeDemoView.h
 *
 * \author Charles Owen
 *
 * A view window that displays a single tree object
 */

#pragma once

#include <memory>
#include "Tree.h"
#include "Basket.h"

/**
 * A view window that displays a single tree object
 */
class CTreeDemoView : public CWnd
{
	DECLARE_DYNAMIC(CTreeDemoView)

public:
	CTreeDemoView();
	virtual ~CTreeDemoView();

    void SetFrame(int frame);
    void SetWindSpeed(double speed);
    void SetSeed(int seed);

    void Harvest();
    void EmptyBasket();

    /**
     * Get the tree object
     * 
     * You are not allowed to do this in your adapter class!
     * \return CTree object
     */
    std::shared_ptr<CTree> GetTree() { return mTree; }

protected:
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnPaint();
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);

    BOOL Create(CWnd* pParentWnd, const RECT& rect, UINT nID, DWORD dwStyle);

private:
    BOOL RegisterWindowClass();

    std::shared_ptr<CTree> mTree;       ///< Tree we are displaying
    std::shared_ptr<CBasket> mBasket;   ///< Basket
};


