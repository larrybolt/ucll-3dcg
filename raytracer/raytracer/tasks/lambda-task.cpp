#include "tasks/lambda-task.h"

using namespace tasks;


namespace
{
    class LambdaTask : public Task
    {
    public:
        LambdaTask(std::function<void()> lambda)
            : m_lambda(lambda)
        {
            // NOP
        }

        void perform() override
        {
            m_lambda();
        }

    private:
        std::function<void()> m_lambda;
    };
}

std::shared_ptr<Task> tasks::from_lambda(std::function<void()> lambda)
{
    return std::make_shared<LambdaTask>(lambda);
}
