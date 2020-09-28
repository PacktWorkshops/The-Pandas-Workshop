import unittest
import pandas as pd
import import_ipynb
import pandas.testing as pd_testing


class Test(unittest.TestCase):
    def setUp(self):
        import Activity04_01
        self.exercises = Activity04_01

        self.file_url = 'https://raw.githubusercontent.com/PacktWorkshops/The-Pandas-Workshop/master/Chapter04/Data/wine_review.csv'
        self.data_frame = pd.read_csv(self.file_url)

    def test_file_url(self):
        self.assertEqual(self.exercises.file_url, self.file_url)

    def test_df(self):
        self.data_frame.fillna(value={'country': 'Unknown',
                                      'designation': 'Unknown',
                                      'province': 'Unknown',
                                      'region': 'Unknown',
                                      'taster_name': 'Unknown',
                                      'taster_twitter_handle': 'Unknown',
                                      'variety': 'Unknown',
                                      'winery': 'Unknown',
                                      'price': 0
                                      }, inplace=True)
        self.data_frame['country'] = self.data_frame['country'].astype('category')
        self.data_frame['province'] = self.data_frame['province'].astype('category')
        self.data_frame['region'] = self.data_frame['region'].astype('category')
        self.data_frame['taster_name'] = self.data_frame['taster_name'].astype('category')
        self.data_frame['taster_twitter_handle'] = self.data_frame['taster_twitter_handle'].astype('category')
        self.data_frame['variety'] = self.data_frame['variety'].astype('category')
        self.data_frame['price'] = self.data_frame['price'].astype('int')

        pd_testing.assert_frame_equal(self.exercises.data_frame, self.data_frame)

if __name__ == '__main__':
    unittest.main()