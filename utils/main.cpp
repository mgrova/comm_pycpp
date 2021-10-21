#include <comm_pycpp/PyToCppWrapper.h>
#include <memory>
 
int main(int argc, char **argv) 
{
    auto node = std::make_unique<comm_pycpp::PyToCppWrapper>();
    node->initialize("");
    node->runInference("/home/mgrova/Downloads/zidane.jpg");
    return 0;
}