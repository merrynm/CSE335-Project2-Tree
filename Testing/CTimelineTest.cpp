#include "pch.h"
#include "CppUnitTest.h"
#include "Timeline.h"
#include "AnimChannelAngle.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(CTimelineTest)
	{
	public:
        TEST_METHOD(TestCTimelineNumFrames)
        {
            CTimeline timeline;

            // Default number of frames
            Assert::AreEqual(300, timeline.GetNumFrames());

            // Set and get
            timeline.SetNumFrames(123);
            Assert::AreEqual(123, timeline.GetNumFrames());
        }

        TEST_METHOD(TestCTimelineFrameRate)
        {
            CTimeline timeline;

            // Default number of frames
            Assert::AreEqual(30, timeline.GetFrameRate());

            // Set and get
            timeline.SetFrameRate(22);
            Assert::AreEqual(22, timeline.GetFrameRate());
        }


        TEST_METHOD(TestCTimelineCurrentTime)
        {
            CTimeline timeline;

            // Default number of frames
            Assert::AreEqual(0.0, timeline.GetCurrentTime(), 0.00001);

            // Set and get
            timeline.SetCurrentTime(1.23);
            Assert::AreEqual(1.23, timeline.GetCurrentTime(), 0.00001);
        }


		
        TEST_METHOD(TestCTimelineGetDuration)
        {
            CTimeline timeline;

            // Default value
            Assert::AreEqual(10, timeline.GetDuration(), 0.0001);

            // Changed duration
            timeline.SetFrameRate(375);
            Assert::AreEqual(300.0 / 375.0, timeline.GetDuration(), 0.0001);

            timeline.SetNumFrames(789);
            Assert::AreEqual(789.0 / 375.0, timeline.GetDuration(), 0.0001);
        }

        TEST_METHOD(TestCTimelineGetCurrentFrame)
        {
            CTimeline timeline;

            // Default value
            Assert::AreEqual(0, timeline.GetCurrentFrame());

            // Changed time
            timeline.SetCurrentTime(9.27);
            Assert::AreEqual(278, timeline.GetCurrentFrame());
        }

        TEST_METHOD(TestCTimelineAdd)
        {
            CTimeline timeline;
            CAnimChannelAngle channel;

            timeline.AddChannel(&channel);
            Assert::IsTrue(&timeline == channel.GetTimeline());
        }

	};
}