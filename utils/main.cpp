#include <comm_pycpp/PyToCppWrapper.h>
#include <memory>
 
int main(int argc, char **argv) 
{
    auto node = std::make_unique<comm_pycpp::PyToCppWrapper>();
    node->initializeDetector();

    // cv::Mat image = cv::imread("https://ultralytics.com/images/zidane.jpg");
    // node->runInference(image);

    cv::VideoCapture cap;
    if(!cap.open(0))
        return 0;
    
    for(;;)
    {
        cv::Mat frame;
        cap >> frame;
        if(frame.empty()) 
            break;
        
        node->runInference(frame);
    }
    return 0;
}