#include "pipeline/animation-processor.h"

using namespace animation;
using namespace raytracer;
using namespace raytracer::pipeline;


namespace
{
    class AnimationProducer : public Processor<animation::Animation<std::shared_ptr<Scene>>, std::shared_ptr<Scene>>
    {
    public:
        AnimationProducer(double fps)
            : m_fps(fps) { }

        void consume(animation::Animation<std::shared_ptr<Scene>> animation) override
        {
            LOG(INFO) << "Received animation of duration " << animation.duration();
            Duration frame_duration = Duration::from_seconds(1.0 / m_fps);
            unsigned frame_count = unsigned(animation.duration().seconds() * m_fps);
            LOG(INFO) << m_fps << " frames per second, " << frame_duration << " per frame, " << frame_count << " frames";
            TimeStamp now = TimeStamp::zero();

            for ( unsigned i = 0; i != frame_count; ++i )
            {
                LOG(INFO) << "Producing frame " << i << " (" << now << ")";

                std::shared_ptr<Scene> current_frame_scene = animation(now);
                produce(current_frame_scene);
                now += frame_duration;
            }
        }

    private:
        double m_fps;
    };
}

std::shared_ptr<Processor<animation::Animation<std::shared_ptr<Scene>>, std::shared_ptr<Scene>>> raytracer::pipeline::animation(double fps)
{
    return std::make_shared<AnimationProducer>(fps);
}
