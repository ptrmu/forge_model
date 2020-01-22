
#include "forge_model_files.hpp"

#include <experimental/filesystem>
#include <iostream>
#include "string_printf.hpp"

namespace forge_model
{

  ModelFiles::ModelFiles(const std::string &folder_path, const std::string &model_name) :
    folder_path_{folder_path},
    model_name_{model_name},
    model_path_{ros2_shared::string_printf("%s/%s", folder_path.c_str(), model_name.c_str())},
    materials_path_{ros2_shared::string_printf("%s/materials", model_path_.c_str())},
    scripts_path_{ros2_shared::string_printf("%s/scripts", materials_path_.c_str())},
    textures_path_{ros2_shared::string_printf("%s/textures", materials_path_.c_str())},
    png_filename_{ros2_shared::string_printf("%s/%s", textures_path_.c_str(), model_name.c_str())}
  {}

  bool ModelFiles::clean_and_create_folder(const std::string &folder_path)
  {
    std::error_code errorCode;
    if (!std::experimental::filesystem::remove_all(folder_path, errorCode) && errorCode.value() != 0) {
      std::cout << "error removing directory: '" << folder_path << "' error: " << errorCode.message() << std::endl;
      return false;
    }

    if (!std::experimental::filesystem::create_directory(folder_path, errorCode)) {
      std::cout << "error creating directory: " << folder_path << " error: " << errorCode.message() << std::endl;
      return false;
    }

    return true;
  }

  bool ModelFiles::create_model_directory_structure()
  {
    std::error_code errorCode;
    if (!std::experimental::filesystem::create_directory(model_path_, errorCode)) {
      std::cout << "error creating directory: " << model_path_ << " error: " << errorCode.message() << std::endl;
      return false;
    }

    if (!std::experimental::filesystem::create_directory(materials_path_, errorCode)) {
      std::cout << "error creating directory: " << materials_path_ << " error: " << errorCode.message() << std::endl;
      return false;
    }

    if (!std::experimental::filesystem::create_directory(scripts_path_, errorCode)) {
      std::cout << "error creating directory: " << scripts_path_ << " error: " << errorCode.message() << std::endl;
      return false;
    }

    if (!std::experimental::filesystem::create_directory(textures_path_, errorCode)) {
      std::cout << "error creating directory: " << textures_path_ << " error: " << errorCode.message() << std::endl;
      return false;
    }

    return true;
  }

}
