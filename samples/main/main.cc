#include <iostream>
#include <inference_engine.hpp>
#include <opencv2/opencv.hpp>
/**
 * @class PluginVersion
 * @brief A PluginVersion class stores plugin version and initialization status
 */
struct PluginVersion : public InferenceEngine::Version {
    bool initialized = false;

    explicit PluginVersion(const InferenceEngine::Version *ver) {
        if (nullptr == ver) {
            return;
        }
        InferenceEngine::Version::operator=(*ver);
        initialized = true;
    }

    operator bool() const noexcept {
        return initialized;
    }
};

inline void printPluginVersion(InferenceEngine::InferenceEnginePluginPtr ptr, std::ostream& stream) {
    const InferenceEngine::Version *version;
    ptr->GetVersion(version);
    stream << PluginVersion(version) << std::endl;
}


int main() {
    std::cout << "InferenceEngine: " << InferenceEngine::GetInferenceEngineVersion() << std::endl;
    InferenceEngine::InferencePlugin plugin = InferenceEngine::PluginDispatcher().getPluginByDevice("CPU");
    printPluginVersion(plugin, std::cout);
    InferenceEngine::CNNNetReader cnnNet;
    cnnNet.ReadNetwork("/home/aitoe/open_model_zoo/model_downloader/Retail/object_detection/pedestrian/rmnet_ssd/0013/dldt/person-detection-retail-0013.xml");
    cnnNet.getNetwork().setBatchSize(1);
    cnnNet.ReadWeights("/home/aitoe/open_model_zoo/model_downloader/Retail/object_detection/pedestrian/rmnet_ssd/0013/dldt/person-detection-retail-0013.bin");
    std::cout << "Model is read successfully" << std::endl;
    InferenceEngine::InputsDataMap inputInfo = cnnNet.getNetwork().getInputsInfo();
    std::cout << inputInfo.begin()->first << std::endl;

    // output blob info
    InferenceEngine::OutputsDataMap outputInfo = cnnNet.getNetwork().getOutputsInfo();
    auto outName = outputInfo.begin()->first;
    InferenceEngine::DataPtr& output = outputInfo.begin()->second;
    InferenceEngine::SizeVector size = output->getDims();
    std::cout << size[2] << size[3] << std::endl;
    output->setPrecision(InferenceEngine::Precision::FP32);
    output->setLayout(InferenceEngine::Layout::NCHW);

    // load CNN net into the plugin
    InferenceEngine::ExecutableNetwork exeNet = plugin.LoadNetwork(cnnNet.getNetwork(), {});

    std::cout << "Executable network is intialized into a plug in" << std::endl;

    return 0;
}