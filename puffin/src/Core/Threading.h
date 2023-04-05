
#include <thread>

namespace puffin
{
    template<typename func, typename returnType>
    class ThreadWorkingGroup
    {
    private:
        int m_threadsInGroup;
        int m_workPerThread;
        int m_totalFunctionCalls;
        int m_currentFunctionCalls;

    public:
        template<typename... Args>
        returnType Work()
        {
            return func(std::forward<Args>(args)...);
        }

        ThreadWorkingGroup(int functionCalls, int threadsInGroup)
        {
            m_totalFunctionCalls = functionCalls;
            m_threadsInGroup = threadsInGroup;

            m_workPerThread = functionCalls / threadsInGroup;
        }
    };

    class Threading
    {
        static void CreateThread();
        static void CreateThreadGroup();
    };
} // namespace puffin

