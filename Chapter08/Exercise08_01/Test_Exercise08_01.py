import unittest
import pandas as pd
import import_ipynb
import pandas.testing as pd_testing

class Test(unittest.TestCase):
    def setUp(self):
        import Exercise07_01
        self.exercises = Exercise07_01

        self.file_url = 'https://raw.githubusercontent.com/PacktWorkshops/The-Pandas-Workshop/master/Chapter07/Data/titanic.csv'
        self.data_frame = pd.read_csv(self.file_url)


    def test_file_url(self):
        self.assertEqual(self.exercises.file_url, self.file_url)
        
    def test_df(self):
        self.data_frame = self.data_frame.dropna()
        pd_testing.assert_frame_equal(self.exercises.data_frame, self.data_frame)

if __name__ == '__main__':
    unittest.main(argv=['first-arg-is-ignored'], exit=False)
