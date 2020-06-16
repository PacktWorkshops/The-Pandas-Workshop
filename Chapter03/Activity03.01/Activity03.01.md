---
jupyter:
  jupytext:
    formats: ipynb,md
    text_representation:
      extension: .md
      format_name: markdown
      format_version: '1.2'
      jupytext_version: 1.4.0
  kernelspec:
    display_name: pandasworkshop
    language: python
    name: pandasworkshop
---

# Activity 03.01 | COVID19 impact on airline traffic

Your task is to report on the consequences of the 2020 COVID19 pandemic, especially how it affected airlines. We will use real data (unchanged) from EUROSTAT, especially:

* https://ec.europa.eu/eurostat/databrowser/view/ttr00016/default/table?lang=en

There are multiple problems with this dataset.

* Column names contain extra whitespace.
* Not all supposedly numeric columns are numeric.
* There are missing values.
* There is a messed up column at the beginning, containing values like "M,PAS,TOT,TOTAL,PAS_CRD,DE" - We only need the "DE" part (which is the country code)

The filename is "TSV", so a tab separator should work.

Apply a fixes to the input data:

* Inspect the DataFrame columns and remove trailing whitespace.
* Inspect the DataFrame and find the columns and values that does not contain numeric data.
* Use a custom converter to remove non-digits from column values.
* Use a custom converter to fix the first column values to extract only the last two characters (country code).
* Unify the type of all numeric columns to float64

### Bonus task

There are missing values in the data, supposedly the countries have not reported the numbers yet. But some countries have.

* Find all countries, that have reported the full data already.
* Calculate basic percentage changes (e.g. relative to the previous month) for those countries and store these values (maybe in a separate DataFrame).
* Find the average monthly change across the countries.
* Use this change to extrapolate the number for all missing fields.

```python
import pandas as pd
import numpy as np
import re
```

```python
!head estat_ttr00016_filtered.tsv
```

```python
def digits_only(v):
    match = re.search("\d+", v)
    if match:
        return float(match.group())
    return np.nan
```

```python
converters = {
    "freq,unit,schedule,tra_cov,tra_meas,geo\TIME_PERIOD": lambda v: v[-2:],
    "2019-10 ": digits_only,
    "2019-11 ": digits_only,
    "2019-12 ": digits_only,
}
```

```python
df = pd.read_csv("estat_ttr00016_filtered.tsv", sep="\t",
                 converters=converters,
                 na_values=[': '])
```

```python
df.head()
```

```python
df.columns
```

```python
df.columns = df.columns.str.strip()
```

```python
df.columns
```

```python
df = df.rename(columns={'freq,unit,schedule,tra_cov,tra_meas,geo\TIME_PERIOD': 'country_code'})
```

```python
df.dtypes
```

```python
df = df.rename(columns={'freq,unit,schedule,tra_cov,tra_meas,geo\TIME_PERIOD': "cc"})
```

```python
df.head()
```

```python
type(df["2019-07"][32])
```

```python
df["2019-10"]
```

```python
type(df["2019-10"][32])
```

```python
df.dtypes
```

```python
# df.iloc[:, 1:] = df.iloc[:, 1:].astype(float)
```

```python
df.iloc[:, 1:] = df.iloc[:, 1:].astype(float)
```

```python
df.dtypes
```

```python
df.head()
```

## Bonus task


Take the diff along the rows and drop all rows with NA values.

```python
frdiff = df.iloc[:, 1:].diff(axis=1).iloc[:, 1:].dropna()
```

```python
frdiff
```

Nice, but we want the PCT change.

```python
frpct = df.dropna().iloc[:, 1:].pct_change(axis=1).iloc[:, 1:].dropna()
```

```python
frpct
```

These are the average changes per month (from the complete rows only).

```python
change_map = frpct.mean().to_dict()
```

```python
change_map
```

```python
df
```

```python
pd.set_option('display.float_format', lambda x: '%.3f' % x)
```

```python
def mean_change(row):
    """
    Apply row-wise extrapolation of NA values by taking the previous' columns
    value and multiplying it by the mean chnage taken from a dictionary.
    """
    prev = None
    for c, item in row.iteritems():
        if np.isnan(item) and prev:
            row[c] = row[prev] * (1 + change_map[c])
        prev = c
    return row
```

```python
df.iloc[:, 1:] = df.iloc[:, 1:].apply(mean_change, axis=1)
```

We arrive at a complete table, including estimated values.

```python
df[["country_code", "2020-01", "2020-02", "2020-03", "2020-04"]]
```

```python

```
