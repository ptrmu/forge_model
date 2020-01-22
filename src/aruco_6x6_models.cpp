
#include "forge_model_run.hpp"

#include "forge_png.hpp"
#include "forge_model_files.hpp"
#include "forge_xml_files.hpp"
#include "opencv2/aruco/dictionary.hpp"
#include "string_printf.hpp"

namespace forge_model
{
  static void aruco_6x6_png(int id, const std::string &name)
  {
    int marker_size = 6;
    int pixels_per_pip = 90; // a pip is one of the squares inside an aruco marker
    int border_bits = 1;

    auto dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_1000);

    ForgePng img{};
    dictionary->drawMarker(id, pixels_per_pip * (marker_size + 2 * border_bits), img.img(), border_bits);

    img.save(ros2_shared::string_printf("%s.png", name.c_str()));
  }

  static void aruco_6x6_model(int id, const std::string &folder_name)
  {
    std::string model_name{ros2_shared::string_printf("aruco_6x6_marker_%02d", id)};

    ModelFiles mf{folder_name, model_name};
    mf.create_model_directory_structure();

    aruco_6x6_png(id, mf.png_filename_);

    generate_model_config(mf);

    generate_model_sdf(mf, "0.1778", "0.1778");

    generate_model_material(mf);
  }

  void aruco_6x6_models(int n, const std::string &folder_name)
  {
    if (!ModelFiles::clean_and_create_folder(folder_name)) {
      return;
    }

    for (int id = 0; id < n; id += 1) {
      aruco_6x6_model(id, folder_name);
    }
  }
}
