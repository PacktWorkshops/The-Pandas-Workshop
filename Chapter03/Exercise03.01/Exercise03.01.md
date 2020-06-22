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

<!-- #region -->
# Exercise 03-01 | Gross domestic product

The task: Find and load data on GDP.


1. Load Pandas
<!-- #endregion -->

```python
import pandas as pd
```

2. Query a search engine

Now we know about the "datapackage" format, let's see whether there exists a prepared dataset in this format (which would help us loading it).

* [Duck Duck Go](https://duckduckgo.com/?q=gdp+datapackage)
* [Google Search](https://www.google.com/search?q=gdp+datapackage)

And indeed, we find the site: https://github.com/datasets/gdp as first or among the top results.

3. Install "pandas-datapackage-reader" to access the datapackage format.

```python
!pip install pandas-datapackage-reader
```

4. Import the pandas datapackage adapter and load the JSON file from the GDP dataset repository.

```python
import pandas_datapackage_reader as pdr
```

```python
df = pdr.read_datapackage("https://raw.githubusercontent.com/datasets/gdp/master/datapackage.json")
```

5. Confirm the successful load of the data, by using head, tail and info.

```python
df.head()
```

```python
df.tail()
```

```python
df.info()
```

```python

```
