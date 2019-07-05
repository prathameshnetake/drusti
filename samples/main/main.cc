#include <iostream>
#include <inference_engine.hpp>
#include <opencv2/opencv.hpp>
#include "src/utils/ocv_common.h"
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
    InferenceEngine::InferencePlugin plugin = InferenceEngine::PluginDispatcher().getPluginByDevice("GPU");
    printPluginVersion(plugin, std::cout);
    InferenceEngine::CNNNetReader cnnNet;
    cnnNet.ReadNetwork("C:/Users/Alex/open_model_zoo/model_downloader/Retail/object_detection/pedestrian/rmnet_ssd/0013/dldt/person-detection-retail-0013.xml");
    cnnNet.getNetwork().setBatchSize(1);
    cnnNet.ReadWeights("C:/Users/Alex/open_model_zoo/model_downloader/Retail/object_detection/pedestrian/rmnet_ssd/0013/dldt/person-detection-retail-0013.bin");
    std::cout << "Model read successfully" << std::endl;
    InferenceEngine::InputsDataMap inputInfo = cnnNet.getNetwork().getInputsInfo();
    std::cout << inputInfo.begin()->first << std::endl;
    InferenceEngine::InputInfo::Ptr& input = inputInfo.begin()->second;
    auto inputName = inputInfo.begin()->first;
    input->setPrecision(InferenceEngine::Precision::U8);
    input->getInputData()->setLayout(InferenceEngine::Layout::NCHW);

    // output blob info
    InferenceEngine::OutputsDataMap outputInfo = cnnNet.getNetwork().getOutputsInfo();
    auto outName = outputInfo.begin()->first;
    InferenceEngine::DataPtr& output = outputInfo.begin()->second;
    InferenceEngine::SizeVector size = output->getTensorDesc().getDims();
    int objectSize = size[3];
    output->setPrecision(InferenceEngine::Precision::FP32);
    output->setLayout(InferenceEngine::Layout::NCHW);

    // load CNN net into the plugin
    InferenceEngine::ExecutableNetwork exeNet = plugin.LoadNetwork(cnnNet.getNetwork(), {});
    InferenceEngine::InferRequest::Ptr infRequest = exeNet.CreateInferRequestPtr();
    cv::Mat frame = cv::imread("C:/Users/Alex/Pictures/people.png");

    //process the blob
    InferenceEngine::Blob::Ptr a = infRequest->GetBlob(inputName);
    matU8ToBlob<uint8_t>(frame, a);
    std::cout << a->getTensorDesc().getDims()[1] << std::endl;

    // start inference
    infRequest->StartAsync();
    if (InferenceEngine::StatusCode::OK == infRequest->Wait(InferenceEngine::IInferRequest::WaitMode::RESULT_READY)) {
        const float *detections = infRequest->GetBlob(outName)->buffer().as<InferenceEngine::PrecisionTrait<InferenceEngine::Precision::FP32>::value_type*>();
        const size_t height = (size_t) frame.size().height;
        const size_t width = (size_t) frame.size().width;
        for(int i = 0; i < 200; i++) {
            float image_id = detections[i * objectSize + 0];
            if (image_id < 0) {
                std::cout << "Only " << i << " proposals found" << std::endl;
                break;
            }
            float confidence = detections[i * objectSize + 2];
            if (confidence > 0.1) {
                auto label = static_cast<int>(detections[i * objectSize + 1]);
                float xmin = detections[i * objectSize + 3] * width;
                float ymin = detections[i * objectSize + 4] * height;
                float xmax = detections[i * objectSize + 5] * width;
                float ymax = detections[i * objectSize + 6] * height;
                std::cout << "[" << i << "," << label << "] element, prob = " << confidence <<
                                    "    (" << xmin << "," << ymin << ")-(" << xmax << "," << ymax << ")"
                                    << ((confidence > 0.5) ? " WILL BE RENDERED!" : "") << std::endl;
                cv::rectangle(frame, cv::Point2f(xmin, ymin), cv::Point2f(xmax, ymax), cv::Scalar(0, 0, 255));
            }
        }
        cv::imshow("window", frame);
        cv::waitKey(0);
    }
    return 0;
}