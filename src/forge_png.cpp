
#include "forge_png.hpp"

#include "forge_model_run.hpp"

#include <opencv2/imgcodecs.hpp>

//using namespace cv;
//using namespace std;

namespace forge_model
{
  ForgePng::ForgePng(int rows, int cols) :
    mat_{cv::Size{cols, rows}, CV_8UC3, cv::Scalar(0, 0, 0)}
  {
  }

  ForgePng::ForgePng() :
    mat_{}
  {
  }

  int ForgePng::save(const std::string &filename)
  {
    std::vector<int> compression_params;
    compression_params.push_back(cv::IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(9);
    bool result = false;
    try {
      result = imwrite(filename, mat_, compression_params);
    }
    catch (const cv::Exception &ex) {
      fprintf(stderr, "Exception converting image to PNG format: %s\n", ex.what());
    }
    if (result)
      printf("Saved PNG file with alpha data.\n");
    else
      printf("ERROR: Can't save PNG file.\n");
    return result ? 0 : 1;
  }
}
