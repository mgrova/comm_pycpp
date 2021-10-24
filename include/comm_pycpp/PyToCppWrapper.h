#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include<opencv2/opencv.hpp>

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

    void initializeDetector();

    void runInference(const cv::Mat &);

private:
    std::unique_ptr<pybind11::object> _custom_detector;
};
}