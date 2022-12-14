/*
 * Copyright 2022 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "include/core/SkBlendMode.h"
#include "include/core/SkBlender.h"
#include "modules/skottie/src/SkottieJson.h"
#include "modules/skottie/src/SkottiePriv.h"
#include "modules/sksg/include/SkSGRenderEffect.h"

namespace skottie::internal {

namespace {

static sk_sp<SkBlender> get_blender(const skjson::ObjectValue& jobject,
                                    const AnimationBuilder* abuilder) {
    static constexpr SkBlendMode kBlendModeMap[] = {
        SkBlendMode::kSrcOver,    // 0:'normal'
        SkBlendMode::kMultiply,   // 1:'multiply'
        SkBlendMode::kScreen,     // 2:'screen'
        SkBlendMode::kOverlay,    // 3:'overlay
        SkBlendMode::kDarken,     // 4:'darken'
        SkBlendMode::kLighten,    // 5:'lighten'
        SkBlendMode::kColorDodge, // 6:'color-dodge'
        SkBlendMode::kColorBurn,  // 7:'color-burn'
        SkBlendMode::kHardLight,  // 8:'hard-light'
        SkBlendMode::kSoftLight,  // 9:'soft-light'
        SkBlendMode::kDifference, // 10:'difference'
        SkBlendMode::kExclusion,  // 11:'exclusion'
        SkBlendMode::kHue,        // 12:'hue'
        SkBlendMode::kSaturation, // 13:'saturation'
        SkBlendMode::kColor,      // 14:'color'
        SkBlendMode::kLuminosity, // 15:'luminosity'
        SkBlendMode::kPlus,       // 16:'add'
    };

    const size_t mode = ParseDefault<size_t>(jobject["bm"], 0);

    // Special handling of src-over, so we can detect the trivial/no-fancy-blending case
    // (a null blender is equivalent to src-over).
    if (!mode) {
        return nullptr;
    }

    // Modes that are expressible as SkBlendMode.
    if (mode < std::size(kBlendModeMap)) {
        return SkBlender::Mode(kBlendModeMap[mode]);
    }

    // Modes that require custom blenders.
    // TODO: add custom blenders

    abuilder->log(Logger::Level::kWarning, &jobject, "Unsupported blend mode %zu\n", mode);
    return nullptr;
}

}  // namespace

sk_sp<sksg::RenderNode> AnimationBuilder::attachBlendMode(const skjson::ObjectValue& jobject,
                                                          sk_sp<sksg::RenderNode> child) const {
    if (auto blender = get_blender(jobject, this)) {
        fHasNontrivialBlending = true;
        child = sksg::BlenderEffect::Make(std::move(child), std::move(blender));
    }

    return child;
}

}  // namespace skottie::internal
