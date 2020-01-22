
#include "forge_model_files.hpp"
#include "forge_xml_files.hpp"
#include "string_printf.hpp"

#include <fstream>
#include <iostream>

namespace forge_model
{
  static void find_and_replace(std::string &data, const std::string &toSearch, const std::string &replaceStr)
  {
    // Get the first occurrence
    size_t pos = data.find(toSearch);

    // Repeat till end is reached
    while (pos != std::string::npos) {
      // Replace this occurrence of Sub String
      data.replace(pos, toSearch.size(), replaceStr.c_str());
      // Get the next occurrence from the current position
      pos = data.find(toSearch, pos + replaceStr.size());
    }
  }

  static void save_text(const std::string &filename, const std::string &output_text)
  {
    std::ofstream os(filename);
    if (!os) {
      std::cout << "Error writing to file: " << filename << std::endl;
    } else {
      os << output_text;
    }
  }

  static const std::string model_config_text =
    R"(<?xml version="1.0" ?>
<model>
    <name>###marker_name###</name>
    <version>1.0</version>
    <sdf version="1.6">model.sdf</sdf>
    <author>
        <name></name>
        <email></email>
    </author>
    <description></description>
</model>
)";

  void generate_model_config(const ModelFiles &mf)
  {
    std::string model_config{model_config_text};
    find_and_replace(model_config, "###marker_name###", mf.model_name_);
    save_text(ros2_shared::string_printf("%s/model.config", mf.model_path_.c_str()), model_config);
  }


  static const std::string model_sdf_text =
    R"(<?xml version='1.0'?>
<sdf version='1.5'>
  <model name='###marker_name###'>

    <link name='marker'>
      <pose frame=''>0 0 0 0 0 0</pose>
      <visual name='visual'>
        <geometry>
          <box>
            <size>###marker_size_x### ###marker_size_y### 1e-5</size>
          </box>
        </geometry>
        <material>
          <script>
            <uri>model://###marker_name###/materials/scripts</uri>
            <uri>model://###marker_name###/materials/textures</uri>
            <name>visual_###marker_name###/Marker</name>
          </script>
          <ambient>1 1 1 1</ambient>
          <diffuse>1 1 1 1</diffuse>
          <specular>0 0 0 1</specular>
          <emissive>1 1 1 0</emissive>
          <shader type='vertex'>
            <normal_map>__default__</normal_map>
          </shader>
        </material>
        <pose frame=''>0 0 0 0 0 0</pose>
        <cast_shadows>1</cast_shadows>
        <transparency>0</transparency>
      </visual>
      <collision name='collision'>
        <laser_retro>0</laser_retro>
        <max_contacts>10</max_contacts>
        <pose frame=''>0 0 0 0 0 0</pose>
        <geometry>
          <box>
            <size>###marker_size_x### ###marker_size_y### 1e-05</size>
          </box>
        </geometry>
      </collision>
    </link>

    <link name='marker_pad'>
      <pose frame='marker'>0 0 -1e-3 0 0 0</pose>
      <visual name='visual'>
        <geometry>
          <box>
            <size>###marker_size_x### ###marker_size_y### 1e-5</size>
          </box>
        </geometry>
        <material>
          <lighting>1</lighting>
          <script>
            <uri>file://media/materials/scripts/gazebo.material</uri>
            <name>Gazebo/White</name>
          </script>
          <ambient>0.3 0.3 0.3 1</ambient>
          <diffuse>0.7 0.7 0.7 1</diffuse>
          <specular>0.01 0.01 0.01 1</specular>
          <emissive>1 1 1 0</emissive>
          <shader type='vertex'>
            <normal_map>__default__</normal_map>
          </shader>
        </material>
        <cast_shadows>1</cast_shadows>
        <transparency>0</transparency>
      </visual>
      <collision name='collision'>
        <laser_retro>0</laser_retro>
        <max_contacts>10</max_contacts>
        <pose frame=''>0 0 0 0 0 0</pose>
        <geometry>
          <box>
            <size>###marker_size_x### ###marker_size_y### 1e-5</size>
          </box>
        </geometry>
      </collision>
    </link>

    <joint name='marker_JOINT_marker_pad' type='revolute'>
      <parent>marker</parent>
      <child>marker_pad</child>
      <pose frame=''>0 0 0 0 0 0</pose>
      <axis>
        <xyz>0 0 1</xyz>
        <limit>
          <upper>0</upper>
          <lower>0</lower>
        </limit>
      </axis>
    </joint>

    <static>1</static>
    <allow_auto_disable>1</allow_auto_disable>

  </model>
</sdf>
)";

  void generate_model_sdf(const ModelFiles &mf,
                          const std::string &marker_size_x,
                          const std::string &marker_size_y)
  {
    std::string model_sdf{model_sdf_text};
    find_and_replace(model_sdf, "###marker_name###", mf.model_name_);
    find_and_replace(model_sdf, "###marker_size_x###", marker_size_x);
    find_and_replace(model_sdf, "###marker_size_y###", marker_size_y);
    save_text(ros2_shared::string_printf("%s/model.sdf", mf.model_path_.c_str()), model_sdf);
  }

  static const std::string model_material_text =
    R"(material visual_###marker_name###/Marker
{
	technique
	{
		pass
		{
			texture_unit
			{
				texture ###marker_name###.png
			}
		}
	}
})";

  void generate_model_material(const ModelFiles &mf)
  {
    std::string model_material{model_material_text};
    find_and_replace(model_material, "###marker_name###", mf.model_name_);
    save_text(ros2_shared::string_printf("%s/%s.material",
                                         mf.scripts_path_.c_str(), mf.model_name_.c_str()),
              model_material);
  }
}
