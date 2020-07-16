#ifndef GENERATOR_H
#define GENERATOR_H


class Generator
{
    public:
        /// Constructor - as a file generator
        /// \param proc_n - number of processors from the range [1,1000]
        /// \param task_n - number of tasks from the range[proc_n, 1000]
        Generator(int proc_n, int task_n);

        /// Destructor
        virtual ~Generator();

    protected:

    private:
};

#endif // GENERATOR_H
