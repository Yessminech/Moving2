import unittest
from collections import deque

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

    ## Testing that the Q table is initialized and modified correctly
    def test_initialize_Q_table(self):
        Q_table = self.agent.initialize_Q_table()
        self.assertEqual(Q_table.shape, (7, 6, 5, 7, 6))

    def test_update_Q_table(self):
        batch = [
            (("white", "dis_0"), "forward", ("yellow", "dis_2"), 17.0, False),
            (("yellow", "dis_2"), "forward", ("yellow", "dis_2"), 17.0, False),
        ]
        self.agent.update_Q_table(batch)
        Q_table = self.agent.get_Q_table()
        self.assertEqual(Q_table.shape, (7, 6, 5, 7, 6))
        self.assertNotEqual(Q_table.sum(), 0)

    ## Testing that the Q_table is exported correctly
    def test_export_Q_table(self):
        import os

        # TODO double check .csv or .txt
        self.assertTrue(os.path.isfile("rl/main/Q_table.csv"))

    def test_populate_replay_buffer(self):
        self.agent.populate_replay_buffer("E:/Fichier/TUB/STUDIUM/SoSe 24/EES Projekt (RL)/RL/GIT repo 2/Moving2/rl/main/generated_dataset/fake_dataset_test_populatereplaybefore.txt")
        print(self.agent.replay_buffer)
        test_buffer = deque([(('white', 'dis_0'), 'forward', ('white', 'dis_0'), -1.0, False),
       (('white', 'dis_0'), 'forward', ('white', 'dis_1'), -2.0, False),
       (('white', 'dis_0'), 'forward', ('white', 'dis_2'), -3.0, False)],
      maxlen=10000)
        self.assertEqual(self.agent.replay_buffer , test_buffer )

    def test_sample_batch_1(self):
        self.agent.populate_replay_buffer("E:/Fichier/TUB/STUDIUM/SoSe 24/EES Projekt (RL)/RL/GIT repo 2/Moving2/rl/main/generated_dataset/fake_dataset_test_populatereplaybefore.txt")
        batch = self.agent.sample_batch()
        print(batch)

    def test_sample_batch_2(self):
        self.agent.populate_replay_buffer("E:/Fichier/TUB/STUDIUM/SoSe 24/EES Projekt (RL)/RL/GIT repo 2/Moving2/rl/main/generated_dataset/fake_dataset.txt")
        batch = self.agent.sample_batch()
        self.assertEqual(len(batch), self.agent.batch_size)





if __name__ == "__main__":
    unittest.main()
