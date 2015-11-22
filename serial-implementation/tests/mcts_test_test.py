from gutserialmcts.mcts_test import MonteCarloGameHandler


class TestMonteCarloGameHandler:
    gameHandler = None

    def setup_method(self, method):
        self.gameHandler = MonteCarloGameHandler(starting_state=None,
                                                 player_one_max_iterations=1,
                                                 player_two_max_iterations=1)

    def teardown_method(self, method):
        self.gameHandler = None

    def test_play_method(self):
        assert hasattr(self.gameHandler, 'play') == True
