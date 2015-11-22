import random
from gutserialmcts.algorithm.mcts import MCTSNode


class UTCSearch(object):
    """
        Container class for method performing UCT search.
        In future it should also contain randomising function for creating new state of game if it's empty.
    """

    @staticmethod
    def search(root_state=None, max_iterations=0):
        """
            Perform UCT ( Upper Confidence bound applied to Trees ) Monte Carlo Tree Search for root_state of game
            This implementation assumes that there are 2 alternating players and the game can hae results in range of
            [0.0, 1.0]

            :param max_iterations: maximum number of iterations to perform
            :param root_state: starting state of the game
        """

        root = MCTSNode(state=root_state)
        # This is the iteration loop
        for i in range(0, max_iterations):
            node = root
            state = root_state.clone()

            # Step no. 1: Selection
            # Starting at root node R, recursively select optimal child nodes until a leaf node L is reached.
            while node.actions_not_taken == [] and node.child_nodes != []:  # node is fully expanded and non-terminal
                node = node.select_next_child_node()
                state.perform_action(node.previous_action)

            # Step no. 2: Expansion
            # If L is a not a terminal node (i.e. it does not end the game) then
            # create one or more child nodes and select one C.
            if node.actions_not_taken:  # if we can expand (i.e. node is non-terminal)
                action = random.choice(node.actions_not_taken)
                state.perform_action(action)
                node = node.add_child_node(action, state)  # add child and descend tree

            # Step no. 3: Simulation
            # Run a simulated playout from C until a result is achieved.
            # This can often be made orders of magnitude quicker using a state.GetRandomMove() function
            while state.get_available_actions():  # while state is non-terminal
                state.perform_action(random.choice(state.get_available_actions()))

            # Step no. 4: Backpropagation
            # Update the current move sequence with the simulation result.
            while node is not None:  # work back to the root node from expanded one
                node.update(state.get_value(node.last_active_player))  # Update node with result
                node = node.parent_node

        print(repr(root))

        # Return most visited action
        return sorted(root.child_nodes, key=lambda c: c.visits)[-1].previous_action
