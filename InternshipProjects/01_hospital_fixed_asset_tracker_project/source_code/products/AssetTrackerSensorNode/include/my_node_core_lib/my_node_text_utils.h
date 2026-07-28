#pragma once

#include <stddef.h>

bool buildHospitalId(
    const char *hospital_name,
    char *output,
    size_t output_size,
    const char *fallback_id);
