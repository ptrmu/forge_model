
#ifndef _FORGE_MODEL_FILES_HPP
#define _FORGE_MODEL_FILES_HPP

#include <string>

namespace forge_model
{
  struct ModelFiles
  {
    const std::string folder_path_;
    const std::string model_name_;
    const std::string model_path_;
    const std::string materials_path_;
    const std::string scripts_path_;
    const std::string textures_path_;
    const std::string png_filename_;

    ModelFiles(const std::string &folder_path, const std::string &model_name);

    static bool clean_and_create_folder(const std::string &folder_path);

    bool create_model_directory_structure();
  };
}

#endif //_FORGE_MODEL_FILES_HPP
