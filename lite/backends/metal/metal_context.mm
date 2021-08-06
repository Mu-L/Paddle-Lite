// Copyright (c) 2021 PaddlePaddle Authors. All Rights Reserved.
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

#include "lite/backends/metal/metal_context.h"
#include "lite/backends/metal/metal_context_imp.h"

namespace paddle {
namespace lite_metal {

MetalContext::MetalContext() {
    mContext = (__bridge_retained void*)[[MetalContextImp alloc] init];
    if (mContext) {

    }
}

MetalContext::~MetalContext() {
    CFRelease(mContext);
    mContext = nullptr;
}

void MetalContext::set_program(RuntimeProgram* program) {
    program_ = program;
}

void MetalContext::wait_all_completed() {
    [(__bridge MetalContextImp*)mContext waitAllCompleted];
    [(__bridge MetalContextImp*)mContext fetch_data_from_gpu];
}

void MetalContext::set_metal_device(void* device) {
    [(__bridge MetalContextImp*)mContext setMetalDevice:device];
}

void MetalContext::set_metal_path(std::string path) {
    [(__bridge MetalContextImp*)mContext setMetalPath:path];
}

void MetalContext::resize_input(int64_t index, void* texture, std::vector<int64_t>& shape) {
    [(__bridge MetalContextImp*)mContext resizeInput:index
                                             texture:texture
                                                dims:shape];
}

}
}
