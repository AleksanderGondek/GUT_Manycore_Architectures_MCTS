from gutserialmcts.games.base import GameState


class NimState(GameState):
    """
        Class representing state of game called "Nim" ( https://en.wikipedia.org/wiki/Nim )
        More precisely: "subtractions 1,2,3" variant

        In this game two players alternately take turns to remove chips from stack - they can only remove
        (1,2, or 3) chip at once. The player to take last chip wins.
    """

    def __init__(self, last_active_player=2, chips=15):
        super().__init__(last_active_player, chips)

    def clone(self):
        """
            Return a deep clone of self
        """
        return NimState(self.last_active_player, self.chips)

    def perform_action(self, action):
        """
            Perform given action and change last_active_player
            :param action: action to be performed - in this case, number of chips to be removed
        """
        if not 1 <= action <= 3 and action == int(action):
            raise Exception("Invalid action to be performed: {0}".format(action))

        self.chips -= action
        self.last_active_player = 3 - self.last_active_player

    def get_available_actions(self):
        """
            Returns list of remaining possible moves
            In this case: you can take up to 3 chips
        """
        return list(range(1, min([4, self.chips + 1])))

    def get_value(self, player_id):
        """
            Return game state value, from the point of view of player 'player_id'
            :param player_id: player_id to check for win condition
        """
        if not self.chips == 0:
            raise Exception("Attempt to read node value before play-out finished!")

        if self.last_active_player == player_id:
            # player_id was the last active player, took the last chip, so he won
            return 1.0
        else:
            return 0.0

    def __repr__(self):
        """
            Prints game state in human readable form
            :return: text value describing game state
        """
        return "Last active player: {0}; Chips: {1}".format(self.last_active_player, self.chips)
