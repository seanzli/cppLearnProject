#pragma once

#include <string>
#include <memory>
#include <vector>

/**
 * generate process class base on configuration file
 * return a shared_ptr
 * input data should belong to first process
 * output data should belong to current process
 * whole process should be like a chain.
 */

namespace generate_process {


class Data {
public:
    virtual ~Data() {}
};

class Process {
public:
    virtual ~Process() {}
    virtual void setInputData(std::vector<std::shared_ptr<Data>>) {}
    virtual void setOutputData(std::vector<std::shared_ptr<Data>>) {}

protected:
    std::shared_ptr<Process> next = nullptr;
};

class InputData : Data {
};

class OutputData : Data {
};

class PreProcess : Process {
};

class MainProcess : Process {
};

class Generate {
public:
    Generate(const char* path) {}
    std::shared_ptr<Process> decodeConfig(const char* path) { return std::shared_ptr<Process>();}
};

}

