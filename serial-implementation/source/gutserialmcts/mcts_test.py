from gutserialmcts.games.nim import NimState
from gutserialmcts.algorithm.utc import UTCSearch


class MonteCarloGameHandler(object):
    """
        This class is responsible for playing out a simple game between two players.
        Both of them are using UTC to determine their best moves, however they have different number of iterations.
        Player with higher number of iterations should win more often.

        Class should be provided with starting game state object, a class inheriting GameState properties -
        this class can (in theory) describe any 2-player complete information deterministic zero-sum game.

        !IMPORTANT!: 1 UTC iterations == 1 simulation == 1 MCTS node
    """

    def __init__(self, starting_state, player_one_max_iterations=1000, player_two_max_iterations=100):
        self.starting_state = starting_state
        self.player_one_max_iterations = player_one_max_iterations
        self.player_two_max_iterations = player_two_max_iterations

    def play(self):
        """
            This method plays out game accordingly to provided starting state and iterations
        """
        while self.starting_state.get_available_actions():
            print("Starting game state: {0}".format(repr(self.starting_state)))

            if self.starting_state.last_active_player == 1:
                action = UTCSearch.search(root_state=self.starting_state, max_iterations=self.player_one_max_iterations)
            else:
                action = UTCSearch.search(root_state=self.starting_state, max_iterations=self.player_two_max_iterations)

            print("Best move determined: {0}\n".format(str(action)))
            self.starting_state.perform_action(action)

        if self.starting_state.get_value(self.starting_state.last_active_player) == 1.0:
            print("Player #{0} wins!".format(self.starting_state.last_active_player))
        elif self.starting_state.get_value(self.starting_state.last_active_player) == 0.0:
            print("Player #{0} wins!".format(str(3 - self.starting_state.last_active_player)))
        else:
            print("It is a draw!")


if __name__ == "__main__":
    gameHandler = MonteCarloGameHandler(NimState(last_active_player=2, _chips=15), 1000, 100)
    gameHandler.play()
