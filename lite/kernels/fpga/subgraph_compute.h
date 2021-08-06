// Copyright (c) 2019 PaddlePaddle Authors. All Rights Reserved.
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

#pragma once

#include <memory>
#include <string>
#include <vector>
#include "lite/core/kernel.h"
#include "lite/core/program.h"

namespace paddle {
namespace lite_metal {
namespace kernels {
namespace fpga {

class SubgraphCompute
    : public KernelLite<TARGET(kFPGA), PRECISION(kAny), DATALAYOUT(kNHWC)> {
 public:
  using param_t = operators::SubgraphParam;

  void PrepareForRun() override;

  void Run() override;

  virtual ~SubgraphCompute() = default;

 private:
  std::unique_ptr<RuntimeProgram> program_;
};

}  // namespace xpu
}  // namespace kernels
}  // namespace lite
}  // namespace paddle