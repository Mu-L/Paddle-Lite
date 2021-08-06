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

#include "lite/core/mir/fusion/fpga_concat_fuse_pass.h"
#include <memory>
#include <vector>
#include "lite/core/mir/fusion/fpga_concat_fuser.h"
#include "lite/core/mir/pass_registry.h"

namespace paddle {
namespace lite_metal {
namespace mir {

void FpgaConcatFusePass::Apply(const std::unique_ptr<SSAGraph>& graph) {
  fusion::FpgaConcatFuser fuser;
  fuser(graph.get());
}

}  // namespace mir
}  // namespace lite
}  // namespace paddle

REGISTER_MIR_PASS(fpga_concat_fuse_pass, paddle::lite_metal::mir::FpgaConcatFusePass)
    .BindTargets({TARGET(kFPGA)});