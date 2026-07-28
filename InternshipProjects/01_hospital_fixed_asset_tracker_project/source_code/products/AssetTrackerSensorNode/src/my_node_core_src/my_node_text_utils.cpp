/**
 * @file my_node_text_utils.cpp
 * @author Farros Ramzy (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-06-25
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "my_node_core_lib/my_node_text_utils.h"

#include <ctype.h>
#include <string.h>

static bool appendChar(char *output, size_t output_size, size_t *index, char value)
{
    if (*index + 1 >= output_size)
    {
        return false;
    }

    output[*index] = value;
    (*index)++;
    output[*index] = '\0';
    return true;
}

static bool copyFallback(char *output, size_t output_size, const char *fallback_id)
{
    if (output == nullptr || output_size == 0 || fallback_id == nullptr)
    {
        return false;
    }

    size_t len = strlen(fallback_id);
    if (len == 0 || len >= output_size)
    {
        output[0] = '\0';
        return false;
    }

    strcpy(output, fallback_id);
    return true;
}

bool buildHospitalId(
    const char *hospital_name,
    char *output,
    size_t output_size,
    const char *fallback_id)
{
    if (output == nullptr || output_size == 0)
    {
        return false;
    }

    output[0] = '\0';

    if (hospital_name == nullptr || hospital_name[0] == '\0')
    {
        return copyFallback(output, output_size, fallback_id);
    }

    size_t out_index = 0;
    bool previous_dash = false;

    for (size_t i = 0; hospital_name[i] != '\0'; i++)
    {
        unsigned char raw = (unsigned char)hospital_name[i];
        char c = (char)tolower(raw);

        if (isalnum(raw))
        {
            if (!appendChar(output, output_size, &out_index, c))
            {
                return false;
            }
            previous_dash = false;
        }
        else if (!previous_dash && out_index > 0)
        {
            if (!appendChar(output, output_size, &out_index, '-'))
            {
                return false;
            }
            previous_dash = true;
        }
    }

    while (out_index > 0 && output[out_index - 1] == '-')
    {
        out_index--;
        output[out_index] = '\0';
    }

    if (out_index == 0)
    {
        return copyFallback(output, output_size, fallback_id);
    }

    return true;
}
