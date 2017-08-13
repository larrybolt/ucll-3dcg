#pragma once

#include "tasks/task-scheduler.h"


namespace tasks
{
    namespace schedulers
    {
        /// <summary>
        /// Creates a scheduler that performs each task one after the other.
        /// </summary>
        TaskScheduler serial();
    }
}