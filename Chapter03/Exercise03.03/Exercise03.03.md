<!-- #region -->
# Exercise 03.03 | Internet users around the world (Excel)

You colleague (or yourself) has prepared a JSON file with information, that other people are interested in, but they prefer an Excel file.

Your task is:

* Load the "mdf.json" file into a DataFrame.
* Export the DataFrame as Excel, do not save the index, format the ratio with two decimal places and name the Sheet "Internet users".

Bonus task.

Microsoft Excel will display large integers in scientific notation, which may or may not be the right thing to do. A workaround is to convert int columns with large number into text first. Apply this workaround.

* [https://superuser.com/q/452832/38447](https://superuser.com/q/452832)

----

# Discussion


Import Pandas and load the JSON file.
<!-- #endregion -->

```python
import pandas as pd
```

```python
df = pd.read_json("mdf.json")
```

```python
df.head()
```

Use the appropriate parameters for the Excel export.

```python
df.to_excel("mdf.xlsx", sheet_name="Internet users", float_format="%.2f", index=False)
```

Bonus solution, create a new DataFrame with adjusted dtypes, the export it.

```python
bonus = pd.DataFrame({"Country": df["Country"],
                      "Population": df["Population"].astype(str),
                      "Internet users":  df["Internet users"].astype(str),
                      "Ratio": df["Ratio"]})
```

```python
bonus.to_excel("bonus.xlsx", sheet_name="Internet users", float_format="%.2f", index=False)
```
