#include <comm_pycpp/PyToCppWrapper.h>

#include <pybind11/pybind11.h>
#include <pybind11/embed.h>  // python interpreter
#include <pybind11/stl.h>  // type conversion

#include <comm_pycpp/ConversionUtils.h>


namespace comm_pycpp
{

PyToCppWrapper::PyToCppWrapper()
{
    pybind11::initialize_interpreter();
}

PyToCppWrapper::~PyToCppWrapper()
{
    pybind11::finalize_interpreter();
}

bool PyToCppWrapper::initialize(const std::string &)
{
    std::cout << "Starting pybind" << std::endl;

    // append source dir to sys.path, and python interpreter would find your custom python file
    pybind11::module_ sys = pybind11::module_::import("sys");
    pybind11::list path = sys.attr("path");
    path.attr("append")("../py_src");

    /// \note. Method 1. Create class object and call its methods
    pybind11::module_ detector = pybind11::module_::import("yolo_v5");
    pybind11::type detectorClass = detector.attr("YoloV5Detector");
    _customDetector = std::make_unique<pybind11::object>(detectorClass());

    /// \todo. Method 2. Create function callback

    // pybind11::function min_rosen =
    //     pybind11::reinterpret_borrow<pybind11::function>(   // cast from 'object' to 'function - use `borrow` (copy) or `steal` (move)
    //         pybind11::module::import("exec_numpy").attr("min_rosen")  // import method "min_rosen" from python "module"
    //     );
    // pybind11::object result = min_rosen(std::vector<double>{1,2,3,4,5});  // automatic conversion from `std::vector` to `numpy.array`, imported in `pybind11/stl.h`
    // bool success = result.attr("success").cast<bool>();
    // int num_iters = result.attr("nit").cast<int>();
    // double obj_value = result.attr("fun").cast<double>();

}

void PyToCppWrapper::runInference(const std::string &path)
{
    cv::Mat img = cv::imread(path);
    cv::cvtColor(img, img, cv::COLOR_BGR2RGB);

    pybind11::array_t<unsigned char> img_to_py = cv_mat_uint8_3c_to_numpy(img);

    pybind11::gil_scoped_acquire gil;
    
    pybind11::object res = _customDetector->attr("inference")(img_to_py);
    auto py_img = res.cast<pybind11::array_t<unsigned char>>();
    cv::Mat infer_img = numpy_uint8_3c_to_cv_mat(py_img);
    cv::cvtColor(img, img, cv::COLOR_BGRA2BGR);

    cv::imshow("dd", infer_img);
    cv::waitKey(0);

    // pybind11::object pyObj = _customDetector->attr("get_image");

    // std::cout << "size: " << data.size() << std::endl;
    // auto pyArray = pybind11::array_t<unsigned char>(_customDetector->attr("get_image"));
    // pybind11::array_t<unsigned char> pyArray = _customDetector->attr("get_image");


    pybind11::gil_scoped_release nogil;

}

}