import unittest
import pandas as pd
import import_ipynb
import pandas.testing as pd_testing

class Test(unittest.TestCase):
    def setUp(self):
        import Exercise06_01
        self.exercises = Exercise06_01

        self.file_url = 'https://raw.githubusercontent.com/PacktWorkshops/The-Pandas-Workshop/master/Chapter06/Data/messy_addresses.csv'
        self.data_frame = pd.read_csv(self.file_url, header=None)

    def test_file_url(self):
        self.assertEqual(self.exercises.file_url, self.file_url)
        
    def test_df(self):
        self.data_frame.drop([2,3], axis=1, inplace=True)
        self.column_names = ["full_name", "address"]
        self.data_frame.columns = ["full_name", "address"]
        self.data_frame[['first_name','last_name']]=self.data_frame.full_name.str.split(expand=True)
        self.data_frame.drop('full_name', axis=1, inplace=True)
        self.data_frame[['street', 'city','state']] = self.data_frame.address.str.split(pat = ", ", expand=True)
        self.data_frame.drop('address', axis=1, inplace=True)
        pd_testing.assert_frame_equal(self.exercises.data_frame, self.data_frame)
    
    

if __name__ == '__main__':
    unittest.main(argv=['first-arg-is-ignored'], exit=False)
