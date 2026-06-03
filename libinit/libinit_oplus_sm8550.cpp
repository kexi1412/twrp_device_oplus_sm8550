/*
 * Copyright (C) 2022-2026 The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

#include <android-base/logging.h>
#include <android-base/parseint.h>
#include <android-base/properties.h>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

#include <fs_mgr.h>
#include <unordered_map>

using android::base::GetProperty;
using android::fs_mgr::GetKernelCmdline;

const std::unordered_map<int, std::string> kRegionSuffixMap = {
    {27,    "IN"},
    {55,    "RU"},
    {68,    "EEA"},
    {151,   ""},    // CN
    {161,   "NA"},
    {167,   ""},    // GLO
    {0,     ""},    // Default
};

struct ModelInfo {
    const char* brand;              // ro.product.brand
    const char* device;             // ro.product.device
    const char* manufacturer;       // ro.product.manufacturer
    const char* model;              // ro.product.model
    const char* base_name;          // ro.product.name  w/o region suffix
    const char* twversion;          // ro.twrp.device_version
};

const std::unordered_map<int, ModelInfo> kModelInfoMap = {
    // OnePlus 11 (CN)
    {22811, {"OnePlus", "OP591BL1",  "OnePlus", "PHB110",  "PHB110",  "OnePlus_11_CN"}},
    // OnePlus 11 (IN/GLO) - CPH2447 India, CPH2449 Global
    {22861, {"OnePlus", "OP594DL1",  "OnePlus", "CPH2449", "CPH2449", "OnePlus_11"}},
    // OnePlus Ace 2 Pro (CN)
    {22851, {"OnePlus", "OP5943L1",  "OnePlus", "PJA110",  "PJA110",  "OnePlus_Ace2_Pro"}},
    // OnePlus Ace 3 (CN)
    {23801, {"OnePlus", "OP5CF9L1",  "OnePlus", "PJE110",  "PJE110",  "OnePlus_Ace3"}},
    // OnePlus 12R (IN/GLO) - CPH2585 India, CPH2609 Global
    {23861, {"OnePlus", "OP5D35L1",  "OnePlus", "CPH2609", "CPH2609", "OnePlus_12R"}},
    // OnePlus Open (GLO)
    {22899, {"OnePlus", "OP5973L1",  "OnePlus", "CPH2551", "CPH2551", "OnePlus_Open"}},
    // OPPO Find X6 Pro (CN)
    {21131, {"OPPO",    "OP528BL1",  "OPPO",    "PGEM10",  "PGEM10",  "OPPO_Find_X6_Pro"}},
    // OPPO Find N3 (CN)
    {22003, {"OPPO",    "OP55F3L1",  "OPPO",    "PHN110",  "PHN110",  "OPPO_Find_N3"}},
    // realme GT5 150W (CN)
    {22635, {"realme",  "RE5C33",    "realme",  "RMX3820", "RMX3820", "Realme_GT5_150W"}},
    // realme GT5 240W (CN)
    {23603, {"realme",  "RE5C33",    "realme",  "RMX3823", "RMX3823", "Realme_GT5_240W"}},
    // Default
    {0,     {"OPLUS",   "SM8550",    "OPLUS",   "SM8550",  "SM8550",  "OPLUS_SM8550"}},
};

/*
 * SetProperty does not allow updating read only properties and as a result
 * does not work for our use case. Write "OverrideProperty" to do practically
 * the same thing as "SetProperty" without this restriction.
 */
void OverrideProperty(const char* name, const char* value) {
    size_t valuelen = strlen(value);

    prop_info* pi = (prop_info*)__system_property_find(name);
    if (pi != nullptr) {
        __system_property_update(pi, value, valuelen);
    } else {
        __system_property_add(name, strlen(name), value, valuelen);
    }
}

void SetupModelProperties(const ModelInfo& info, const std::string& region) {
    std::string name = info.base_name + region;
    struct PropPair {
        const char* key;
        const char* value;
    } props[] = {
        {"ro.product.brand",            info.brand},
        {"ro.product.device",           info.device},
        {"ro.product.manufacturer",     info.manufacturer},
        {"ro.product.model",            info.model},
        {"ro.product.name",             name.c_str()},
        {"ro.twrp.device_version",      info.twversion},
        {"ro.build.date.utc",           "0"},
    };
    for (const auto& p : props) {
        OverrideProperty(p.key, p.value);
    }
}

void vendor_load_properties() {
    std::string buf = "0";
    GetKernelCmdline("oplus_region", &buf);

    auto region = std::stoi(buf);
    auto region_suffix_iter = kRegionSuffixMap.find(region);

    // Handle unknown regions gracefully
    if (region_suffix_iter == kRegionSuffixMap.end()) {
        LOG(WARNING) << "Unknown oplus_region: " << region << ", using default";
        region_suffix_iter = kRegionSuffixMap.find(0);
    }

    auto prjname = std::stoi(GetProperty("ro.boot.prjname", "0"));
    auto model_info = kModelInfoMap.find(prjname);

    // Handle unknown device models
    if (model_info == kModelInfoMap.end()) {
        LOG(ERROR) << "Unknown prjname: " << prjname << ", using default";
        model_info = kModelInfoMap.find(0);
    }

    SetupModelProperties(model_info->second, region_suffix_iter->second);
}
