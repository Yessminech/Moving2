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
