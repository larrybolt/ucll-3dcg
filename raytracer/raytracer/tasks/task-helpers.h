#pragma once

#include "tasks/lambda-task.h"
#include <vector>


namespace tasks
{
    template<typename T>
    std::vector<std::shared_ptr<Task>> range(T from, T to, std::function<void(T)> lambda)
    {
        std::vector<std::shared_ptr<Task>> tasks;

        for (auto i = from; i < to; ++i)
        {
            std::function<void()> specialized_lambda = std::bind(lambda, i);
            auto task = tasks::from_lambda(specialized_lambda);

            tasks.push_back(task);
        }

        return tasks;
    }
}
