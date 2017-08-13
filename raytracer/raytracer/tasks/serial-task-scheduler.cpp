#include "tasks/serial-task-scheduler.h"

using namespace tasks;


namespace
{
    /// <summary>
    /// Performs tasks one after the other (i.e. not in parallel).
    /// </summary>
    class SerialTaskScheduler : public tasks::schedulers::_private_::TaskSchedulerImplementation
    {
    public:
        void perform(std::vector<std::shared_ptr<Task>> tasks) const
        {
            for (auto task : tasks)
            {
                task->perform();
            }
        }
    };
}

TaskScheduler tasks::schedulers::serial()
{
    return TaskScheduler(std::make_shared<SerialTaskScheduler>());
}
