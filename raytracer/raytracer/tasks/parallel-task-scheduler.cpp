#include "tasks/parallel-task-scheduler.h"
#include <thread>
#include <atomic>

using namespace tasks;


namespace
{
	/// <summary>
	/// Performs tasks in parallel.
	/// </summary>
	class ParallelTaskScheduler : public tasks::schedulers::_private_::TaskSchedulerImplementation
	{
	protected:

		static void *execute(std::vector<std::shared_ptr<Task>> tasks)
		{
			// Check if there are tasks left to perform
			if (tasks.size() > 0)
			{
				// Create a task from the back of the tasks list.
				auto task = tasks.back();

				// Remove task from list.
				tasks.pop_back();

				// Perform the task.
				task->perform();

				// Call recursively until all tasks have been performed.
				execute(tasks);
			}
			return 0;
		}

	public:
		void perform(std::vector<std::shared_ptr<Task>> tasks) const
		{
			std::vector<std::thread> th;

			unsigned int num_threads = std::thread::hardware_concurrency() - 1;

			for (unsigned i = 0; i < num_threads; i++)
			{
				th.push_back(std::thread(&ParallelTaskScheduler::execute, tasks));
			}

			for (auto &t : th)
			{
				t.join();
			}
		}

		
	};
}

TaskScheduler tasks::schedulers::parallel()
{
	return TaskScheduler(std::make_shared<ParallelTaskScheduler>());
}
