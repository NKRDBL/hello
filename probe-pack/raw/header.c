#include "unit_genericfx.h"

const __unit_header genericfx_unit_header_t unit_header = {
  .common = {
    .header_size = sizeof(genericfx_unit_header_t),
    .target = UNIT_TARGET_PLATFORM | k_unit_module_genericfx,
    .api = UNIT_API_VERSION,
    .dev_id = 0x0,
    .unit_id = 0x1001U,
    .version = 0x00010000U,
    .name = "RAW1SEC",
    .num_params = 0,
    .params = {
      {0,0,0,0,k_unit_param_type_none,0,0,0,{""}},
      {0,0,0,0,k_unit_param_type_none,0,0,0,{""}},
      {0,0,0,0,k_unit_param_type_none,0,0,0,{""}},
      {0,0,0,0,k_unit_param_type_none,0,0,0,{""}},
      {0,0,0,0,k_unit_param_type_none,0,0,0,{""}},
      {0,0,0,0,k_unit_param_type_none,0,0,0,{""}},
      {0,0,0,0,k_unit_param_type_none,0,0,0,{""}},
      {0,0,0,0,k_unit_param_type_none,0,0,0,{""}}
    },
  },
  .default_mappings = {
    {k_genericfx_param_assign_none,k_genericfx_curve_linear,k_genericfx_curve_unipolar,0,0,0},
    {k_genericfx_param_assign_none,k_genericfx_curve_linear,k_genericfx_curve_unipolar,0,0,0},
    {k_genericfx_param_assign_none,k_genericfx_curve_linear,k_genericfx_curve_unipolar,0,0,0},
    {k_genericfx_param_assign_none,k_genericfx_curve_linear,k_genericfx_curve_unipolar,0,0,0},
    {k_genericfx_param_assign_none,k_genericfx_curve_linear,k_genericfx_curve_unipolar,0,0,0},
    {k_genericfx_param_assign_none,k_genericfx_curve_linear,k_genericfx_curve_unipolar,0,0,0},
    {k_genericfx_param_assign_none,k_genericfx_curve_linear,k_genericfx_curve_unipolar,0,0,0},
    {k_genericfx_param_assign_none,k_genericfx_curve_linear,k_genericfx_curve_unipolar,0,0,0}
  }
};
