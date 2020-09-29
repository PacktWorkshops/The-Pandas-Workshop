import unittest
import pandas as pd
import import_ipynb
import pandas.testing as pd_testing

class Test(unittest.TestCase):
    def setUp(self):
        import Exercise04_03
        self.exercises = Exercise04_03

        self.s = pd.Series(['         Data Analysis using python with pandas is great',
               'pandas DataFrame and pandas series are useful  ',
               'PYTHON3 PANDAS'])

    def test_series(self):
        pd_testing.assert_series_equal(self.exercises.s, self.s)

if __name__ == '__main__':
    unittest.main()