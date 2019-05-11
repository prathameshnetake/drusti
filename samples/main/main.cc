#include "src/DNNObjectDetect/DNNObjectDetect.h"

int main() {
  DNNObjectDetectParams params;
  params.modelCfgPath = "";
  params.modelWeigthPath = "";
  drusti::DNNObjectDetect* a = new drusti::DNNObjectDetect(params);
  return 0;
}