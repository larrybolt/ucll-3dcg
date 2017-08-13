#pragma once

#include "tasks/task.h"
#include <memory>
#include <vector>


namespace tasks
{
    namespace schedulers
    {
        namespace _private_
        {
            class TaskSchedulerImplementation
            {
            public:
                /// <summary>
                /// Performs each task in the given <paramref name="tasks" />.
                /// No guarantee is made with regards to order or whether these tasks are performed in parallel.
                /// </summary>
                virtual void perform(std::vector<std::shared_ptr<Task>> tasks) const = 0;
            };
        }
    }

    class TaskScheduler
    {
    public:
        explicit TaskScheduler(std::shared_ptr<tasks::schedulers::_private_::TaskSchedulerImplementation> implementation = nullptr)
            : m_implementation(implementation) { }

        tasks::schedulers::_private_::TaskSchedulerImplementation* operator ->() const
        {
            return m_implementation.get();
        }

    private:
        std::shared_ptr<tasks::schedulers::_private_::TaskSchedulerImplementation> m_implementation;
    };
}
