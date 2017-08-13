#pragma once

#include "tasks/task.h"
#include <functional>
#include <memory>


namespace tasks
{
    std::shared_ptr<Task> from_lambda(std::function<void()> lambda);
}