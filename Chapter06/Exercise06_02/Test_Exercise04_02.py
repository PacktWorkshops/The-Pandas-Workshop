import unittest
import pandas as pd
import import_ipynb
import pandas.testing as pd_testing


class Test(unittest.TestCase):
    def setUp(self):
        import Exercise04_02
        self.exercises = Exercise04_02

        self.file_url = 'https://raw.githubusercontent.com/PacktWorkshops/The-Pandas-Workshop/master/Chapter04/Data/retail_purchase_missing.csv'
        self.data_frame = pd.read_csv(self.file_url)

    def test_file_url(self):
        self.assertEqual(self.exercises.file_url, self.file_url)

    def test_df(self):
        self.data_frame.fillna(value={'Receipt Id': 0, 'Product Weight': 0, 'Total Price': 0}, inplace=True)
        self.data_frame['Date of Purchase'].fillna('01/01/99', inplace=True)
        self.data_frame.fillna(value={'Product Name': 'Missing Name', 'Retail shop name': 'Missing Name'}, inplace=True)
        self.data_frame['Date of Purchase'] = pd.to_datetime(self.data_frame['Date of Purchase'], format='%d/%m/%y')
        self.data_frame['Receipt Id'] = self.data_frame['Receipt Id'].astype('int')
        self.data_frame['Total Price'] = self.data_frame['Total Price'].astype('int')
        self.data_frame['Product Weight'] = self.data_frame['Product Weight'].astype('int')
        self.data_frame['Product Name'] = self.data_frame['Product Name'].astype('category')
        self.data_frame['Retail shop name'] = self.data_frame['Retail shop name'].astype('category')
        pd_testing.assert_frame_equal(self.exercises.data_frame, self.data_frame)

if __name__ == '__main__':
    unittest.main()