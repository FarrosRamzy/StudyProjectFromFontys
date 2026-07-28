"""
File: conftest.py
Author: Farros Ramzy (you@domain.com)
Description: Global pytest fixture aggregator.
Version: 0.1
Date: 2026-06-22

Copyright (c) 2026
"""

from tests.fixtures.test_environment import *  # noqa: F401,F403
from tests.fixtures.database_fixtures import *  # noqa: F401,F403
from tests.fixtures.patching_fixtures import *  # noqa: F401,F403
from tests.fixtures.user_factories import *  # noqa: F401,F403
from tests.fixtures.node_factories import *  # noqa: F401,F403
from tests.fixtures.asset_factories import *  # noqa: F401,F403
from tests.fixtures.route_fixtures import *  # noqa: F401,F403

# from tests.fixtures.test_environment import *  # noqa: F401,F403
# from tests.fixtures.database_fixtures import *  # noqa: F401,F403
# from tests.fixtures.patching_fixtures import *  # noqa: F401,F403
# from tests.fixtures.user_factories import *  # noqa: F401,F403
# from tests.fixtures.node_factories import *  # noqa: F401,F403
# from tests.fixtures.asset_factories import *  # noqa: F401,F403
# from tests.fixtures.route_fixtures import *  # noqa: F401,F403
