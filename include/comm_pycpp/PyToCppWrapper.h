#pragma once

#include <iostream>
#include <vector>
#include <memory>

namespace pybind11
{
class object;
class handle;
}

namespace comm_pycpp
{
class PyToCppWrapper
{
public:
    PyToCppWrapper();
    ~PyToCppWrapper();

    bool initialize(const std::string &);

    void runInference(const std::string &);

private:
    std::unique_ptr<pybind11::object> _customDetector;
};
}