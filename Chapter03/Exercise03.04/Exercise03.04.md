<!-- #region -->
# Exercise 03.04 | Exporting to SQLite3

We continue to use our internet users dataset (from exercises 2 and 3).

Somehow, the data ended up as HDF5 (the key is "iu"), but we would like to prepare the data for a web application, which will require the data as an relational database. We convinced the web team to start with sqlite3.

You task:

* Read the HDF5 into a DataFrame (key: "iu").
* Export the DataFrame as sqlite database.

The web team requires the following database schema:

```
CREATE TABLE internet_users (
        "index" BIGINT,
        "Country" TEXT,
        "Population" BIGINT,
        "Internet users" BIGINT,
        "Ratio" FLOAT
);
```

----

# Discussion


Import Pandas and load the HDF5 file.
<!-- #endregion -->

```python
import pandas as pd
```

```python
df = pd.read_hdf("mdf.h5", key="iu")
```

```python
df.to_sql("internet_users", "sqlite:///mdf.db", if_exists="replace")
```

We can verify the schema.

```python
!sqlite3 mdf.db .schema
```

```python

```
