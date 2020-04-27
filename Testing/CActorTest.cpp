#include "pch.h"
#include "CppUnitTest.h"

#include "Actor.h"

#include "PolyDrawable.h"
#include "Picture.h"
#include <memory>
using namespace std;
using namespace Gdiplus;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
    TEST_CLASS(CActorTest)
    {
    public:
        
        TEST_METHOD(TestCActorConstructor)
        {
            CActor actor(L"Harold");
            Assert::AreEqual(std::wstring(L"Harold"), actor.GetName());
        }


        TEST_METHOD(TestCActorEnabled)
        {
            CActor actor(L"Harold");
            Assert::IsTrue(actor.IsEnabled());
            actor.SetEnabled(false);
            Assert::IsFalse(actor.IsEnabled());
        }

        TEST_METHOD(TestCActorClickable)
        {
            CActor actor(L"Harold");
            Assert::IsTrue(actor.IsClickable());
            actor.SetClickable(false);
            Assert::IsFalse(actor.IsClickable());
        }

        TEST_METHOD(TestCActorPosition)
        {
            CActor actor(L"Harold");
            Assert::AreEqual(0, actor.GetPosition().X);
            Assert::AreEqual(0, actor.GetPosition().Y);

            actor.SetPosition(Gdiplus::Point(123, 456));
            Assert::AreEqual(123, actor.GetPosition().X);
            Assert::AreEqual(456, actor.GetPosition().Y);
        }

        TEST_METHOD(TestCActorSetPicture)
        {
            // Create a picture object
            auto picture = make_shared<CPicture>();

            // Create an actor and add it to the picture
            auto actor = make_shared<CActor>(L"Actor");

            // Create a drawable for the actor
            auto drawable = make_shared<CPolyDrawable>(L"Drawable");
            actor->SetRoot(drawable);
            actor->AddDrawable(drawable);

            picture->AddActor(actor);

            auto channel = drawable->GetAngleChannel();
            Assert::IsTrue(channel->GetTimeline() == picture->GetTimeline());
        }

        /** This tests that the animation of the position of an actor works */
        TEST_METHOD(TestCActorAnimation)
        {
            // Create a picture object
            auto picture = make_shared<CPicture>();

            // Create an actor and add it to the picture
            auto actor = make_shared<CActor>(L"Actor");
            picture->AddActor(actor);

            auto channel = actor->GetPositionChannel();

            // First we will ensure it works with no keyframes set
            picture->SetAnimationTime(0);
            actor->SetPosition(Point(1234, 9833));

            // The channel should not be valid
            Assert::IsFalse(channel->IsValid());

            // Getting a keyframe should not changle the position
            actor->GetKeyframe();
            Assert::AreEqual(1234, actor->GetPosition().X);
            Assert::AreEqual(9833, actor->GetPosition().Y);

            // Now we'll set one keyframe and see if that works
            picture->SetAnimationTime(1.5);
            actor->SetPosition(Point(101, 655));
            actor->SetKeyframe();

            // Change position
            actor->SetPosition(Point(1234, 9833));
            Assert::AreEqual(1234, actor->GetPosition().X);
            Assert::AreEqual(9833, actor->GetPosition().Y);

            // Wherever we move, now, the keyframe angle should be used
            picture->SetAnimationTime(0);
            Assert::AreEqual(101, actor->GetPosition().X);
            Assert::AreEqual(655, actor->GetPosition().Y);

            actor->SetPosition(Point(1234, 9833));
            picture->SetAnimationTime(1.5);
            Assert::AreEqual(101, actor->GetPosition().X);
            Assert::AreEqual(655, actor->GetPosition().Y);

            actor->SetPosition(Point(1234, 9833));
            picture->SetAnimationTime(3);
            Assert::AreEqual(101, actor->GetPosition().X);
            Assert::AreEqual(655, actor->GetPosition().Y);

            // We'll set a second keyframe and see if that works
            picture->SetAnimationTime(3.0);
            actor->SetPosition(Point(202, 1000));
            actor->SetKeyframe();

            // Test before the keyframes
            actor->SetPosition(Point(1234, 9833));
            picture->SetAnimationTime(0);
            Assert::AreEqual(101, actor->GetPosition().X);
            Assert::AreEqual(655, actor->GetPosition().Y);

            // Test at first keyframe
            actor->SetPosition(Point(1234, 9833));
            picture->SetAnimationTime(1.5);
            Assert::AreEqual(101, actor->GetPosition().X);
            Assert::AreEqual(655, actor->GetPosition().Y);

            // Test at second keyframe
            actor->SetPosition(Point(1234, 9833));
            picture->SetAnimationTime(3);
            Assert::AreEqual(202, actor->GetPosition().X);
            Assert::AreEqual(1000, actor->GetPosition().Y);

            // Test after second keyframe
            actor->SetPosition(Point(1234, 9833));
            picture->SetAnimationTime(4);
            Assert::AreEqual(202, actor->GetPosition().X);
            Assert::AreEqual(1000, actor->GetPosition().Y);

            // Test between the two keyframs
            actor->SetPosition(Point(1234, 9833));
            picture->SetAnimationTime(2.25);
            Assert::AreEqual((101 + 202) / 2, actor->GetPosition().X);
            Assert::AreEqual((655 + 1000) / 2, actor->GetPosition().Y);

            actor->SetPosition(Point(1234, 9833));
            picture->SetAnimationTime(2.0);    // 1/3 between the two keyframes
            Assert::AreEqual((int)(101 + 1.0 / 3.0 * (202 - 101)), actor->GetPosition().X);
            Assert::AreEqual((int)(655 + 1.0 / 3.0 * (1000 - 655)), actor->GetPosition().Y);
        }
    };
}