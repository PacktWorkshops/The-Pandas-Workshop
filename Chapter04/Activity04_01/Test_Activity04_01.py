import unittest
import pandas as pd
import import_ipynb
import pandas.testing as pd_testing

class Test(unittest.TestCase):
    def setUp(self):
        import Activity04_01
        self.exercises = Activity04_01

        self.file_url = 'https://raw.githubusercontent.com/PacktWorkshops/The-Pandas-Workshop/master/Chapter04/Data/car.csv'
        self.data_frame = pd.read_csv(self.file_url)

    def test_file_url(self):
        self.assertEqual(self.exercises.file_url, self.file_url)
        
    def test_df(self):
        self.data_frame.fillna(value={
            'buying': 'Unknown',
            'maint': 'Unknown',
            'doors': round(self.data_frame.doors.mean()),
            'persons': round(self.data_frame.persons.mean()),
            'lug_boot': 'Unknown',
            'safety': 'Unknown',
            'class': 'Unknown'
        }, inplace=True)
        
        self.data_frame = self.data_frame.astype({
            'buying': 'category',
            'maint': 'category',
            'persons': 'int',
            'lug_boot': 'category',
            'safety': 'category',
            'class': 'category'
        })

        pd_testing.assert_frame_equal(self.exercises.data_frame, self.data_frame)

if __name__ == '__main__':
    unittest.main(argv=['first-arg-is-ignored'], exit=False)
