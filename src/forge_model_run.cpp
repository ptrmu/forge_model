
#include "forge_model_run.hpp"

int main()
{
  forge_model::aruco_6x6_models(64, "aruco_6x6_markers");
  forge_model::charuco_12x9_aruco_5x5_model("charuco_12x9_aruco_5x5");
}

