
#include "forge_model_run.hpp"

#include "forge_png.hpp"
#include "forge_xml_files.hpp"
#include "forge_model_files.hpp"
#include "opencv2/aruco/charuco.hpp"
#include "opencv2/aruco/dictionary.hpp"
#include "string_printf.hpp"

namespace forge_model
{

  static void charuco_12x9_aruco_5x5_board(const ModelFiles &mf)
  {
    int squaresX = 12;
    int squaresY = 9;
    double squareLength = 0.030;
    double markerLength = 0.0225;

    auto dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_5X5_100);

    auto charuco_board{cv::aruco::CharucoBoard::create(squaresX, squaresY,
                                                       static_cast<float>(squareLength),
                                                       static_cast<float>(markerLength),
                                                       dictionary)};

    int marker_size = 5;
    int pixels_per_pip = 90; // a pip is one of the squares inside an aruco marker
    int border_bits = 1;
    int aruco_side_pixels = pixels_per_pip * (marker_size + 2 * border_bits);
    int square_side_pixels = std::ceil(aruco_side_pixels * squareLength / markerLength);

    ForgePng img{};
    charuco_board->draw(cv::Size(squaresX * square_side_pixels, squaresY * square_side_pixels), img.img());
    img.save(ros2_shared::string_printf("%s.png", mf.png_filename_.c_str()));

    // Generate the other files.
    generate_model_config(mf);

    // Not quite sure whey the X and Y are interchanged. :)
    generate_model_sdf(mf,
                       ros2_shared::string_printf("%7.4f", squaresY * squareLength),
                       ros2_shared::string_printf("%7.4f", squaresX * squareLength));

    generate_model_material(mf);

  }

  void charuco_12x9_aruco_5x5_model(const std::string &folder_name)
  {
    if (!ModelFiles::clean_and_create_folder(folder_name)) {
      return;
    }

    std::string model_name{"charuco_12x9_aruco_5x5_target"};

    ModelFiles mf{folder_name, model_name};
    mf.create_model_directory_structure();

    charuco_12x9_aruco_5x5_board(mf);
  }

}