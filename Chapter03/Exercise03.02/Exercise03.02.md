# Exercise 03.02 | Internet users around the world

Your company wants to invest in countries with potential internet user growth.
That is we want to find countries with the lowest ratio of internet users.

Your task is to find the following information on the internet:

* A table showing the number of internet users within a country.
* A table showing the population per country.

Once you found a webpage, load the appropriate table into a DataFrame.

----

# Discussion

Different websites will contain this information, but let's go with CIA
factbook, as their tables are quite parseable (besides, the information will be
available in other formats as well).

* Internet users: [https://www.cia.gov/library/publications/the-world-factbook/fields/204rank.html](https://www.cia.gov/library/publications/the-world-factbook/fields/204rank.html)
* Population: [https://www.cia.gov/library/publications/the-world-factbook/fields/335rank.html](https://www.cia.gov/library/publications/the-world-factbook/fields/335rank.html)



Import Pandas and load the data info dataframe lists.

```python
import pandas as pd
```

```python
f204s = pd.read_html("https://www.cia.gov/library/publications/the-world-factbook/fields/204rank.html")
f335s = pd.read_html("https://www.cia.gov/library/publications/the-world-factbook/fields/335rank.html")
```

Confirm, that there is only one table on the page (if there are more, you need to find out, which one contains the relevant information); then assign new variables for the dataframes.

```python
assert len(f204s) == 1
assert len(f335s) == 1
```

```python
users = f204s[0]
population = f335s[0]
```

```python
users.head()
```

```python
population.head()
```

Excellent, you found an important relevant information quickly!


Optional task: Determine the countries with the lowest ratio of internet users.


For that, we need to merge the three important columns: "Country", "Internet users" and "Population".

```python
mdf = population[["Country", "Population"]].merge(users[["Country", "Internet users"]])
```

```python
mdf.head()
```

Calculate the ratio and put it into a new column, the sort by the ratio.

```python
mdf["Ratio"] = mdf["Internet users"] / mdf["Population"]
```

```python
mdf.sort_values(by="Ratio").head(10)
```

According to these statistics, Eritrea has the lowest ratio of internet users.
