"""
File: test_location_matcher.py
Author: Farros Ramzy (you@domain.com)
Description: Unit tests for matching detected rooms and nodes against expected asset locations.
Version: 0.1
Date: 2026-05-29

Copyright (c) 2026
"""

try:
    from app.services.assets.location.asset_location_matcher import location_matches
except ModuleNotFoundError:
    from app.services.assets.asset_location_service import location_matches


def test_location_matches_when_room_and_node_match():
    assert location_matches(
        expected_room_name="ICU",
        expected_node_id="NODE_ICU",
        detected_room_name="ICU",
        detected_node_id="NODE_ICU",
    )


def test_location_does_not_match_when_room_differs():
    assert not location_matches(
        expected_room_name="ICU",
        expected_node_id="NODE_ICU",
        detected_room_name="ER",
        detected_node_id="NODE_ICU",
    )


def test_location_does_not_match_when_node_differs():
    assert not location_matches(
        expected_room_name="ICU",
        expected_node_id="NODE_ICU",
        detected_room_name="ICU",
        detected_node_id="NODE_ER",
    )


def test_location_matches_by_room_only():
    assert location_matches(
        expected_room_name="ICU",
        expected_node_id="",
        detected_room_name="ICU",
        detected_node_id="ANY_NODE",
    )


def test_location_matches_by_node_only():
    assert location_matches(
        expected_room_name="",
        expected_node_id="NODE_ICU",
        detected_room_name="ANY_ROOM",
        detected_node_id="NODE_ICU",
    )


def test_location_returns_false_when_no_expected_location_configured():
    assert not location_matches(
        expected_room_name="",
        expected_node_id="",
        detected_room_name="ICU",
        detected_node_id="NODE_ICU",
    )


def test_location_trims_extra_whitespace():
    assert location_matches(
        expected_room_name=" ICU ",
        expected_node_id=" NODE_ICU ",
        detected_room_name="ICU",
        detected_node_id="NODE_ICU",
    )
