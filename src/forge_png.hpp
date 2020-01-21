
#ifndef _FORGE_PNG_HPP
#define _FORGE_PNG_HPP

#include <opencv2/core.hpp>

namespace forge_model
{
  class ForgePng
  {
    cv::Mat mat_;

  public:
    ForgePng(int rows, int cols);

    ForgePng();

    int save(const std::string &filename);

    cv::Mat &img() {
      return mat_;
    }
  };
}

#endif //_FORGE_PNG_HPP
