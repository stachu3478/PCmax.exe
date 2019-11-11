#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string>

class Processor
{
    public:
        /// Constructor - as a task processor
        /// \param taskArraySize - size of the task array
        Processor(int taskArraySize);

        /// Destructor - deletes its array of tasks
        ~Processor();

        /// Operand allows to add task with += operator
        /// \param task
        /// \return total load of the processor
        unsigned int operator+=(const unsigned int task);

        /// Declares array of intances of Processor to init task assign
        /// \param num - number of processors to initialize
        /// \param nTasks - number of tasks to assign
        /// \return - num
        static unsigned int setNumberProcessors(int num, int nTasks);

        /// Finds element in processor with least time assigned
        /// \return - offset of s_processors
        static unsigned int findMin();

        /// Finds element in processor with highest time assigned
        /// \return - offset of s_processors
        static unsigned int findMax();

        /// Assigns task to least loaded processor
        /// \param task - the weight of the task
        /// \return - task
        static unsigned int assignTask(const unsigned int task);

        /// Solves problem and sends the most overloaded processor to the stdout
        /// \param file - path to file to read from
        static void solve(char* file);
        /// Same as solve but sorts the array
        static void solveSorted(char* file);

    protected:

    private:
        /// Array of processors
        static Processor* s_processors;

        /// Number of processors
        static int s_nProcessors;

        /// Number of tasks
        static int s_nTasks;

        /// Total load of all tasks
        static int s_weight;

        /// Number of assigned tasks in single processorNumber of assigned tasks in single processor
        unsigned int m_total;

        /// Load of all assigned tasks in single processor
        unsigned int m_weight;

        /// Array of tasks
        unsigned int* m_tasks;
};

#endif // PROCESSOR_H
