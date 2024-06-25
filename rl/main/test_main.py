import unittest
from main import QLearningAgent


class QLearningAgentTests(unittest.TestCase):
    def setUp(self):
        self.color_mapping = {
            "white": 1,
            "yellow": 2,
            "blue": 3,
            "red": 4,
            "black": 5,
            "brown": -10,
            "lilas": -10,
        }
        self.distance_mapping = distance_map = {
            "dis_0": 1,
            "dis_1": 2,
            "dis_2": 3,
            "dis_3": 4,
            "dis_4": 5,
            "dis_out": -10,  ##dis4 is better than dis0
        }
        self.action_mapping = {
            "forward": 0,
            "backward": 1,
            "right": 2,
            "left": 3,
            "stop": 4,
        }
        self.agent = QLearningAgent(
            self.color_mapping,
            self.distance_mapping,
            self.action_mapping,
            learning_rate=0.1,
            discount_factor=0.99,
            num_episodes=100,
            batch_size=32,
        )

    def test_initialize_Q_table(self):
        Q_table = self.agent.initialize_Q_table()
        self.assertEqual(Q_table.shape, (7, 6, 5, 7, 6))

    def test_update_Q_table(self):
        batch = [
            (('white', 'dis_0'), 'forward', ('yellow', 'dis_2'), 17.0, False),
            (('yellow', 'dis_2'), 'forward', ('yellow', 'dis_2'), 17.0, False),
        ]
        self.agent.update_Q_table(batch)
        Q_table = self.agent.get_Q_table()
        self.assertEqual(Q_table.shape, (7, 6, 5, 7, 6))
        self.assertNotEqual(Q_table.sum(), 0)

if __name__ == "__main__":
    unittest.main()
