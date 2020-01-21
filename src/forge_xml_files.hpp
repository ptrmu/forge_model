
#ifndef _FORGE_XML_FILES_HPP
#define _FORGE_XML_FILES_HPP

#include <string>

namespace forge_model
{
  void generate_model_config(const std::string &model_name,
                             const std::string &file_path);

  void generate_model_sdf(const std::string &model_name,
                          const std::string &marker_size,
                          const std::string &file_path);

  void generate_model_material(const std::string &model_name,
                               const std::string &file_path);
}

#endif //_FORGE_XML_FILES_HPP
