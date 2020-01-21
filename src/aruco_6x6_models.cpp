
#include "forge_png.hpp"
#include "forge_xml_files.hpp"
#include "opencv2/aruco/dictionary.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "string_printf.hpp"
#include <experimental/filesystem>

#include <iostream>

namespace forge_model
{
  void aruco_6x6_png(int id, std::string name) {
    int marker_size = 6;
    int pixels_per_square = 90;
    int border_bits = 1;

    auto dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_1000);

    ForgePng img{};
    dictionary->drawMarker(id, pixels_per_square * (marker_size + 2 * border_bits), img.img(), border_bits);

    img.save(ros2_shared::string_printf("%s.png", name.c_str()));
  }

  void aruco_6x6_model(int id, std::string folder_name)
  {
    std::error_code errorCode;
    std::string model_name{ros2_shared::string_printf("aruco_6x6_marker_%02d", id)};

    std::string model_path{ros2_shared::string_printf("%s/%s", folder_name.c_str(), model_name.c_str())};
    if (!std::experimental::filesystem::create_directory(model_path, errorCode)) {
      std::cout << "error creating directory: " << model_path << " error: " << errorCode.message() << std::endl;
      return;
    }

    std::string materials_path{ros2_shared::string_printf("%s/materials", model_path.c_str())};
    if (!std::experimental::filesystem::create_directory(materials_path, errorCode)) {
      std::cout << "error creating directory: " << materials_path << " error: " << errorCode.message() << std::endl;
      return;
    }

    std::string scripts_path{ros2_shared::string_printf("%s/scripts", materials_path.c_str())};
    if (!std::experimental::filesystem::create_directory(scripts_path, errorCode)) {
      std::cout << "error creating directory: " << scripts_path << " error: " << errorCode.message() << std::endl;
      return;
    }

    std::string textures_path{ros2_shared::string_printf("%s/textures", materials_path.c_str())};
    if (!std::experimental::filesystem::create_directory(textures_path, errorCode)) {
      std::cout << "error creating directory: " << textures_path << " error: " << errorCode.message() << std::endl;
      return;
    }

    std::string png_filename{ros2_shared::string_printf("%s/%s", textures_path.c_str(), model_name.c_str())};
    aruco_6x6_png(id, png_filename);

    generate_model_config(model_name, model_path);

    generate_model_sdf(model_name, "0.1778", model_path);

    generate_model_material(model_name, model_path);
  }

  void aruco_6x6_models(int n, const std::string &folder_name)
  {
    std::error_code errorCode;
    if (!std::experimental::filesystem::remove_all(folder_name, errorCode) && errorCode.value() != 0) {
      std::cout << "error removing directory: '" << folder_name << "' error: " << errorCode.message() << std::endl;
      return;
    }

    if (!std::experimental::filesystem::create_directory(folder_name, errorCode)) {
      std::cout << "error creating directory: " << folder_name << " error: " << errorCode.message() << std::endl;
      return;
    }


    for (int id = 0; id < n; id += 1) {
      aruco_6x6_model(id, folder_name);
    }
  }
}
