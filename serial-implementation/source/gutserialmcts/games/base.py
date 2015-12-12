class GameState(object):
    """
        This class represents a contract that must be fulfilled for MCTS to work.
        Such contract describes a singular state within a game (i.e. pawns positioning on chessboard).
        Methods provided below are bare minimum to make UTC in any 2-player complete information deterministic
        zero-sum game. By convention the players are numbered 1 and 2.
    """
    def __init__(self, last_active_player=2, _chips=15):
        self.last_active_player = last_active_player
        self._chips = _chips

    def clone(self):
        """
            This method should return a deep clone of this game state.
        """
        pass

    def perform_action(self, action):
        """
            This method should perform given move, update state and switch which player has just moved.
            :param action: action to be performed
        """
        pass

    def get_available_actions(self):
        """
            This method should return list of all possible, legal moves.
        """
        pass

    def get_value(self, player_id):
        """
            Get the game state value, from point of view of given player (1st or 2nd)
            :param player_id: player_id to get value for
        """
        pass

    def __repr__(self):
        """
            This method allows for easier printing out game states, but is not necessary.
        """
        pass
