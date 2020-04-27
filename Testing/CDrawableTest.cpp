#include "pch.h"
#include "CppUnitTest.h"
#include <cmath>

#include "Drawable.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
    /** Drawable mock class for testing */
    class CDrawableMock : public CDrawable
    {
    public:
        /** Constructor 
         * \param name A name for the drawable */
        CDrawableMock(const std::wstring &name) : CDrawable(name) {}

        /** Draw dummy function 
         * \param graphics Graphics object to draw on */
        virtual void Draw(Gdiplus::Graphics *graphics) override {}

        /** HitTest dummy function 
         * \param pos Position to test
         * \returns true if we hit the drawable */
        virtual bool HitTest(Gdiplus::Point pos) override { return false; }

    };

    TEST_CLASS(CDrawableTest)
    {
    public:
        
        TEST_METHOD(TestCDrawableName)
        {
            CDrawableMock drawable(L"Arm");
            Assert::AreEqual(std::wstring(L"Arm"), drawable.GetName()); 
        }

        TEST_METHOD(TestCDrawablePosition)
        {
            CDrawableMock drawable(L"Arm");
            Assert::AreEqual(0, drawable.GetPosition().X);
            Assert::AreEqual(0, drawable.GetPosition().Y);

            drawable.SetPosition(Gdiplus::Point(123, 456));
            Assert::AreEqual(123, drawable.GetPosition().X);
            Assert::AreEqual(456, drawable.GetPosition().Y);
        }

        TEST_METHOD(TestCDrawableRotation)
        {
            CDrawableMock drawable(L"Arm");
            Assert::AreEqual(0, drawable.GetRotation(), 0.00001);

            drawable.SetRotation(1.23);
            Assert::AreEqual(1.23, drawable.GetRotation(), 0.00001);

            double a = 0.333;
            double b = acos(cos(a));
            Assert::AreEqual(a, b, 0.000000001);
        }

        TEST_METHOD(TestCDrawableAssociation)
        {
            CDrawableMock body(L"Body");
            auto arm = std::make_shared<CDrawableMock>(L"Arm");
            auto leg = std::make_shared<CDrawableMock>(L"Leg");

            body.AddChild(arm);
            body.AddChild(leg);

            Assert::IsTrue(arm->GetParent() == &body);
            Assert::IsTrue(leg->GetParent() == &body);
        }


    };
}