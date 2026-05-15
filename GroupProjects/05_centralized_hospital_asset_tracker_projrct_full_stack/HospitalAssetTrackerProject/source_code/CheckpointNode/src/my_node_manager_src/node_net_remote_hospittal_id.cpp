/**
 * @file node_hospittal_id.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-05-13
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "my_node_manager_lib/node_manager.h"

String NodeManager::hospitalNameToID(String hospital_name)
{
    String hospital_id = hospital_name;

    hospital_id.trim();
    hospital_id.toLowerCase();

    if (hospital_id.length() == 0)
    {
        return MY_DEFAULT_HOSPITAL_ID;
    }

    String safe_id = "";
    bool previous_dash = false;

    for (size_t i = 0; i < hospital_id.length(); i++)
    {
        char c = hospital_id.charAt(i);

        bool is_lowercase_letter = (c >= 'a' && c <= 'z');
        bool is_digit = (c >= '0' && c <= '9');

        if (is_lowercase_letter || is_digit)
        {
            safe_id += c;
            previous_dash = false;
        }
        else
        {
            if (!previous_dash && safe_id.length() > 0)
            {
                safe_id += '-';
                previous_dash = true;
            }
        }
    }

    while (safe_id.endsWith("-"))
    {
        safe_id.remove(safe_id.length() - 1);
    }

    if (safe_id.length() == 0)
    {
        safe_id = MY_DEFAULT_HOSPITAL_ID;
    }

    return safe_id;
}