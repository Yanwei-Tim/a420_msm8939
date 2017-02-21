/*
 * Copyright (C) 2015 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// Don't edit this file!  It is auto-generated by frameworks/rs/api/generate.sh.

#pragma version(1)
#pragma rs java_package_name(android.renderscript.cts)

rs_allocation gAllocInDenominator;

float __attribute__((kernel)) testAtan2piFloatFloatFloat(float inNumerator, unsigned int x) {
    float inDenominator = rsGetElementAt_float(gAllocInDenominator, x);
    return atan2pi(inNumerator, inDenominator);
}

float2 __attribute__((kernel)) testAtan2piFloat2Float2Float2(float2 inNumerator, unsigned int x) {
    float2 inDenominator = rsGetElementAt_float2(gAllocInDenominator, x);
    return atan2pi(inNumerator, inDenominator);
}

float3 __attribute__((kernel)) testAtan2piFloat3Float3Float3(float3 inNumerator, unsigned int x) {
    float3 inDenominator = rsGetElementAt_float3(gAllocInDenominator, x);
    return atan2pi(inNumerator, inDenominator);
}

float4 __attribute__((kernel)) testAtan2piFloat4Float4Float4(float4 inNumerator, unsigned int x) {
    float4 inDenominator = rsGetElementAt_float4(gAllocInDenominator, x);
    return atan2pi(inNumerator, inDenominator);
}
