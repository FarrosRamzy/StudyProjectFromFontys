"""
File: dummy_node_payloads.py
Author: Farros Ramzy (you@domain.com)
Description: Dummy node definitions for monitor/backend testing.
Version: 0.1
Date: 2026-06-02

Copyright (c) 2026
"""

import random

DUMMY_NODE_PREFIX = "IH-DMY-NODE-"

DUMMY_CHECKPOINT_ROOMS = [
    "Emergency Room",
    "ICU B",
    "ICU C",
    "Operating Room 1",
    "Radiology Room",
    "Pharmacy Storage",
    "General Ward A",
    "General Ward B",
    "Basement Storage",
    "Sterilization Room",
]


def make_random_8_digit_number():
    return random.randint(10_000_000, 99_999_999)


def make_random_9_digit_number():
    return random.randint(100_000_000, 999_999_999)


def make_random_10_digit_number():
    return random.randint(1_000_000_000, 9_999_999_999)


def make_checkpoint_nodes():
    nodes = []

    for index, room_name in enumerate(DUMMY_CHECKPOINT_ROOMS, start=1):
        nodes.append(
            {
                "device_id": f"{DUMMY_NODE_PREFIX}CP{make_random_10_digit_number()}",
                "alias": f"Dummy Checkpoint {index:02d}",
                "role": "CHECKPOINT",
                "room_name": room_name,
            }
        )

    return nodes


def make_registration_nodes():
    return [
        {
            "device_id": f"{DUMMY_NODE_PREFIX}REG{make_random_9_digit_number()}",
            "alias": "Dummy Registration Desk",
            "role": "REGISTRATION",
            "room_name": "",
        }
    ]


def make_discovered_nodes(count: int):
    return [make_discovered_node() for _ in range(1, count + 1)]


def make_discovered_node():
    return {
        "device_id": f"{DUMMY_NODE_PREFIX}DISC{make_random_8_digit_number()}",
        "alias": "",
        "role": "",
        "room_name": "",
    }
