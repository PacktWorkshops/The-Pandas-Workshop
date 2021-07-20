import unittest
import pandas as pd
import import_ipynb
import pandas.testing as pd_testing

class Test(unittest.TestCase):
    def setUp(self):
        import Exercise06_02
        self.exercises = Exercise06_02

        self.file_url_2018 = 'https://raw.githubusercontent.com/PacktWorkshops/The-Pandas-Workshop/master/Chapter06/Data/store_sales_demographics_2018.csv'
        self.file_url_2019 = 'https://raw.githubusercontent.com/PacktWorkshops/The-Pandas-Workshop/master/Chapter06/Data/store_sales_demographics_2019.csv'

        self.data_frame_2018 = pd.read_csv(self.file_url_2018)
        self.data_frame_2019 = pd.read_csv(self.file_url_2019)


    def test_file_url(self):
        self.assertEqual(self.exercises.file_url_2018, self.file_url_2018)
        self.assertEqual(self.exercises.file_url_2019, self.file_url_2019)
        
    def test_df(self):
        self.data_frame_2018["year"] = 2018
        self.data_frame_2019["year"] = 2019
        self.data_frame = pd.concat([self.data_frame_2018, self.data_frame_2019])
        self.data_frame = self.data_frame.melt(id_vars=["year", "store_id"],var_name=["demographic"],value_name="sales")
        self.data_frame['gender'] = self.data_frame.demographic.str[0].astype(str)
        self.data_frame['age_group'] = self.data_frame.demographic.str[1:].astype(str)
        self.data_frame.drop('demographic', axis=1, inplace=True)
        self.data_frame = self.data_frame.sort_values(by=['year', 'store_id', 'gender'])
        self.data_frame = self.data_frame[["store_id", "age_group", "gender", "year", "sales"]]
        self.data_frame = self.data_frame.reset_index(drop = True)
        pd_testing.assert_frame_equal(self.exercises.data_frame, self.data_frame)

if __name__ == '__main__':
    unittest.main(argv=['first-arg-is-ignored'], exit=False)