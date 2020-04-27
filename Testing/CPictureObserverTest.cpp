#include "pch.h"
#include "CppUnitTest.h"

#include "Picture.h"
#include "PictureObserver.h"

using namespace std;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
    /** CPictureObserver mock testing class */
    class CPictureObserverMock : public CPictureObserver
    {
    public:
        /// Constructor
        CPictureObserverMock() : CPictureObserver() {}

        /** Update an observer */
        virtual void UpdateObserver() override { mUpdated = true; }

        /// Flag indicating that the class was updated
        bool mUpdated = false;
    };

    TEST_CLASS(CPictureObserverTest)
    {
    public:
        
        TEST_METHOD(TestConstruct)
        {
            CPictureObserverMock observer;
        }

        TEST_METHOD(TestOneObserver)
        {
            // Allocate a CPicture object
            shared_ptr<CPicture> picture = make_shared<CPicture>();

            // Create a mock observer object
            CPictureObserverMock observer;

            // And set it for the observer:
            observer.SetPicture(picture);

            picture->UpdateObservers();

            Assert::IsTrue(observer.mUpdated);
        }

        TEST_METHOD(TestGetPicture)
        {
            // Allocate a CPicture object
            shared_ptr<CPicture> picture = make_shared<CPicture>();

            // Create a mock observer object
            CPictureObserverMock observer;

            // And set it for the observer:
            observer.SetPicture(picture);

            Assert::IsTrue(observer.GetPicture() == picture);
        }

        TEST_METHOD(TestTwoObservers)
        {
            // Allocate a CPicture object
            shared_ptr<CPicture> picture = make_shared<CPicture>();

            // Create mock observer objects
            CPictureObserverMock observer1;
            CPictureObserverMock observer2;

            // And set it for the observer:
            observer1.SetPicture(picture);
            observer2.SetPicture(picture);

            picture->UpdateObservers();

            Assert::IsTrue(observer1.mUpdated);
            Assert::IsTrue(observer2.mUpdated);
        }

        TEST_METHOD(TestDestroyedObservers)
        {
            // Allocate a CPicture object
            shared_ptr<CPicture> picture = make_shared<CPicture>();

            // Create mock observer objects
            CPictureObserverMock observer1;
            observer1.SetPicture(picture);

            {
                CPictureObserverMock observer2;

                // And set it for the observer:
                observer2.SetPicture(picture);
            }

            picture->UpdateObservers();

            Assert::IsTrue(observer1.mUpdated);
        }

    };
}