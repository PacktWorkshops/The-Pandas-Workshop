import unittest
import pandas as pd
import import_ipynb
import pandas.testing as pd_testing


class Test(unittest.TestCase):
    def setUp(self):
        import Exercise04_01
        self.exercises = Exercise04_01

        self.file_url = 'https://github.com/PacktWorkshops/The-Pandas-Workshop/blob/master/Chapter04/Data/retail_purchase.csv?raw=true'
        self.data_frame = pd.read_csv(self.file_url)

    def test_file_url(self):
        self.assertEqual(self.exercises.file_url, self.file_url)

    def test_df(self):
        self.data_frame['Date of Purchase'] = pd.to_datetime(self.data_frame['Date of Purchase'], format='%d/%m/%y')
        self.data_frame['Total Price'] = self.data_frame['Total Price'].str[1:]
        self.data_frame['Total Price'] = self.data_frame['Total Price'].astype('float')
        self.data_frame['Product Weight'] = self.data_frame['Product Weight'].str[:-2]
        self.data_frame['Product Weight'] = self.data_frame['Product Weight'].astype('float')
        self.data_frame['Product Name'] = self.data_frame['Product Name'].astype('category')
        self.data_frame['Retail shop name'] = self.data_frame['Retail shop name'].astype('category')
        pd_testing.assert_frame_equal(self.exercises.data_frame, self.data_frame)


if __name__ == '__main__':
    unittest.main()