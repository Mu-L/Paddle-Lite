// Copyright (c) 2022 PaddlePaddle Authors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "operation/log_softmax.h"
#include "core/types.h"
#include "operation/math/log_softmax.h"
#include "utility/debug.h"
#include "utility/logging.h"
#include "utility/micros.h"
#include "utility/modeling.h"
#include "utility/utility.h"

namespace nnadapter {
namespace operation {

NNADAPTER_EXPORT bool ValidateLogSoftmax(const core::Operation* operation) {
  return true;
}

NNADAPTER_EXPORT int PrepareLogSoftmax(core::Operation* operation) {
  LOG_SOFTMAX_OPERATION_EXTRACT_INPUTS_OUTPUTS

  // Infer the shape and type of output operands
  CopyOperandTypeExceptQuantParams(&output_operand->type, input_operand->type);
  NNADAPTER_VLOG(5) << "output: " << OperandToString(output_operand);
  return NNADAPTER_NO_ERROR;
}

NNADAPTER_EXPORT int ExecuteLogSoftmax(core::Operation* operation) {
  LOG_SOFTMAX_OPERATION_EXTRACT_INPUTS_OUTPUTS

  // Allocate and calculate the output operands
  int status = -1;
  auto& input_type = input_operand->type;
  auto input_shape = std::vector<int32_t>(
      input_type.dimensions.data,
      input_type.dimensions.data + input_type.dimensions.count);
  const auto input_buffer = input_operand->buffer;
  NNADAPTER_CHECK(input_buffer);
  auto& output_type = output_operand->type;
  auto output_buffer = AllocateOperand(output_operand);
  NNADAPTER_CHECK_EQ(input_type.precision, output_type.precision);
  if (input_type.precision == NNADAPTER_FLOAT32) {
    const auto input_data = reinterpret_cast<const float*>(input_buffer);
    auto output_data = reinterpret_cast<float*>(output_buffer);
    status =
        math::log_softmax<float>(input_data, input_shape, axis, output_data);
  } else if (input_type.precision == NNADAPTER_QUANT_INT8_SYMM_PER_LAYER) {
    const auto input_data = reinterpret_cast<const int8_t*>(input_buffer);
    auto output_data = reinterpret_cast<int8_t*>(output_buffer);
    status = math::log_softmax(input_data,
                               input_shape,
                               input_type.symm_per_layer_params.scale,
                               axis,
                               output_data,
                               output_type.symm_per_layer_params.scale);
  } else {
    NNADAPTER_LOG(FATAL) << "Unsupported precision code("
                         << OperandPrecisionCodeToString(input_type.precision)
                         << ") for " << OperationTypeToString(operation->type)
                         << " is found!";
  }
  NNADAPTER_CHECK_EQ(status, 0);
  return NNADAPTER_NO_ERROR;
}

}  // namespace operation
}  // namespace nnadapter
