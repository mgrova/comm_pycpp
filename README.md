# comm_pycpp

This repo shows how to embed inside a C++ object any Python class. In that way, we could easily integrate functionalities developed in Python with our C++ code. 

An example use case, which is shown in this repo, is to embed the inference of a deep learning model implemented in Python inside a C++ object.

## Dependencies

The only required dependencies are Python3 and PyBind11. To show the use case, Opencv has also been added.

* PyBind11: Follow the [basics steps](https://pybind11.readthedocs.io/en/stable/basics.html) to install it.

* Python3

```
sudo apt install python3-dev
```

* OpenCV

```
sudo apt install libopencv-dev
```

## Build
```
git clone https://github.com/mgrova/comm_pycpp & cd comm_pycpp && \
mkdir build && cd build && \
cmake -DCMAKE_BUILD_TYPE=Release .. && make
```

## Usage

Add your classes to py_src folder and take a look to the [PyToCppWrapper](https://github.com/mgrova/comm_pycpp/blob/master/src/PyToCppWrapper.cpp) class. It should be easy to adapt it to your own needs.

After build the repo, we have the following executable to run it:
```
./build/comm_pycpp/wrap_example
```