
#include "forge_png.hpp"

#include "forge_model_run.hpp"

#include <opencv2/imgcodecs.hpp>

//using namespace cv;
//using namespace std;

namespace forge_model
{
  ForgePng::ForgePng(int rows, int cols) :
    mat_{cv::Size{cols, rows}, CV_8UC3}
  {
    mat_ = cv::BGR 128;
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

  static void createAlphaMat(cv::Mat &mat)
  {
    CV_Assert(mat.channels() == 4);
    for (int i = 0; i < mat.rows; ++i) {
      for (int j = 0; j < mat.cols; ++j) {
        cv::Vec4b &bgra = mat.at<cv::Vec4b>(i, j);
//        bgra[0] = UCHAR_MAX; // Blue
        bgra[0] = cv::saturate_cast<uchar>(std::min((float(mat.cols - j)) / ((float) mat.cols), (float(mat.rows - i)) / ((float) mat.rows)) * UCHAR_MAX); // Blue
        bgra[1] = cv::saturate_cast<uchar>((float(j)) / ((float) mat.cols) * UCHAR_MAX); // Green
        bgra[2] = cv::saturate_cast<uchar>((float(i)) / ((float) mat.rows) * UCHAR_MAX); // Red
//        bgra[3] = cv::saturate_cast<uchar>(1.0 * (bgra[1] + bgra[2])); // Alpha
        bgra[3] = cv::saturate_cast<uchar>(255.0); // Alpha
      }
    }
  }

  int forge_png_example()
  {
    // Create mat with alpha channel
    cv::Mat mat(480, 640, CV_8UC4);
    createAlphaMat(mat);
    std::vector<int> compression_params;
    compression_params.push_back(cv::IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(9);
    bool result = false;
    try {
      result = imwrite("alpha.png", mat, compression_params);
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