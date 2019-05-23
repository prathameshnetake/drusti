#pragma once

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <iostream>

// custom
#include "src/utils/paramTypes.h"

namespace drusti {
  class DNNObjectDetect {
    public:
      DNNObjectDetect(DNNObjectDetectParams);
      ~DNNObjectDetect();
  };
};
