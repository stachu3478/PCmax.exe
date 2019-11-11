#include <iostream>
#include <fstream>
#include <Processor.h>
#include <chrono>

using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    auto start = std::chrono::system_clock::now();
    Processor::solve("m30.txt");
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "Elapsed time: " << elapsed_seconds.count() << "s\n";
    return 0;
}
