from math import sqrt, log


class MCTSNode(object):
    """
        T.B.D.
    """

    def __init__(self, action=None, parent=None, state=None):
        self.previous_action = action  # the move that got us to this node - "None" for the root node
        self.parent_node = parent  # "None" for the root node

        self.child_nodes = []

        self.wins = 0
        self.visits = 0

        self.actions_not_taken = state.get_available_actions()  # future child nodes
        self.last_active_player = state.last_active_player  # the only part of the state that the Node needs later

    def select_next_child_node(self):
        """
            T.B.D.
        """
        return sorted(self.child_nodes, key=lambda c: c.wins / c.visits + sqrt(2 * log(self.visits) / c.visits))[-1]

    def add_child_node(self, action, state):
        """
            T.B.D.
        """
        self.actions_not_taken.remove(action)

        new_child = MCTSNode(action=action, parent=self, state=state)
        self.child_nodes.append(new_child)
        return new_child

    def update(self, value):
        """
            T.B.D.
        """
        self.visits += 1
        self.wins += value

    def __repr__(self):
        return "[ Previous action: {0}; Wins: {1}; Visits: {2}; Actions not taken: {3}; ]"\
            .format(self.previous_action, self.wins, self.visits, self.actions_not_taken)
