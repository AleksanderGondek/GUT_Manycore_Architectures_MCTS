import unittest
import pytest

from guterialmcts.mcts_test import MonteCarloGameHandler


@pytest.mark.usefixtures("MonteCarloGameHandler")
class MonteCarloGameHandlerTest(unittest.TestCase):
    def setUp(self):
        self.gameHandler = MonteCarloGameHandler(starting_state=None,
                                                 player_one_max_iterations=1,
                                                 player_two_max_iterations=1)

    def tearDown(self):
        self.gameHandler = None

    def test_play_method(self):
        self.assertTrue(hasattr(self.gameHandler, 'play'))
