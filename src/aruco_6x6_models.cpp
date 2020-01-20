
#include "forge_png.hpp"
#include "opencv2/aruco/dictionary.hpp"

namespace forge_model
{
  void aruco_6x6_models(int n) {

    ForgePng img{600, 800};

    auto dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_1000);

//    dictionary->drawMarker(0, 25, img.img(), 3);

    img.save("marker_x.png");
  }
}
