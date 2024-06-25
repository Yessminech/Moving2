    def test_train(self):
        self.agent.populate_replay_buffer("rl/code/generated_dataset/fake_dataset.txt")
        self.agent.train()
        Q_table = self.agent.get_Q_table()
        self.assertNotEqual(Q_table.sum(), 0)