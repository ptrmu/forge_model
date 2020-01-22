
#ifndef _FORGE_XML_FILES_HPP
#define _FORGE_XML_FILES_HPP

#include <string>

namespace forge_model
{
  struct ModelFiles;

  void generate_model_config(const ModelFiles &mf);

  void generate_model_sdf(const ModelFiles &mf,
                          const std::string &marker_size_x,
                          const std::string &marker_size_y);

  void generate_model_material(const ModelFiles &mf);
}

#endif //_FORGE_XML_FILES_HPP
