#pragma once
#include "rapidjson/document.h"
#include "errlog.hpp"
using namespace rapidjson;

struct json_data {
    const char* syn_file_name;
    bool rounding_enabled;
    bool rounding_small;
    bool blur;
};

void validate_doc(const Document& doc, json_data* out) {
    // syn_file_name
    if (!doc.HasMember("SynX File")) {
        log_err_and_exit("Could not find \"SynX File\" property in round_options.json");
    }
    if (!doc["SynX File"].IsString()) {
        log_err_and_exit("\"SynX File\" property in round_options.json must be a string");
    }
    out->syn_file_name = doc["SynX File"].GetString();


    // rounding
    if (!doc.HasMember("Rounding")) {
        log_err_and_exit("Could not find \"Rounding\" property in round_options.json");
    }
    if (!doc["Rounding"].IsObject()) {
        log_err_and_exit("\"Rounding\" property in round_options.json must be an object");
    }


    // rounding_enabled
    if (!doc["Rounding"].HasMember("Enabled")) {
        log_err_and_exit("Could not find \"Rounding[\"Enabled\"]\" property in round_options.json");
    }
    if (!doc["Rounding"]["Enabled"].IsBool()) {
        log_err_and_exit("\"Rounding[\"Enabled\"]\" property in round_options.json must be a bool");
    }
    out->rounding_enabled = doc["Rounding"]["Enabled"].GetBool();


    // rounding_small
    if (!doc["Rounding"].HasMember("Small")) {
        log_err_and_exit("Could not find \"Rounding[\"Small\"]\" property in round_options.json");
    }
    if (!doc["Rounding"]["Small"].IsBool()) {
        log_err_and_exit("\"Rounding[\"Small\"]\" property in round_options.json must be a bool");
    }
    out->rounding_small = doc["Rounding"]["Small"].GetBool();


    // blur
    if (!doc.HasMember("Blur")) {
        log_err_and_exit("Could not find \"Blur\" property in round_options.json");
    }
    if (!doc["Blur"].IsBool()) {
        log_err_and_exit("\"Blur\" property in round_options.json must be a bool");
    }
    out->blur = doc["Blur"].GetBool();
}