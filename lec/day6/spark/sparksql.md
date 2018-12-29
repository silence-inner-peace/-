

```python
import numpy as np
import random
```


```python
import pyspark
from pyspark.sql import SparkSession

spark = SparkSession \
    .builder \
    .appName("Python Spark SQL basic example") \
    .config("spark.some.config.option", "some-value") \
    .getOrCreate()
sc = spark.sparkContext

```

# Spark SQL


```python
from pyspark.sql import Row
# $example on:schema_inferring$
sc = spark.sparkContext

# Load a text file and convert each line to a Row.
lines = sc.textFile("file:///trn/testdata/poihubei_all_100.csv")
parts = lines.map(lambda l: l.split(","))
places = parts.map(lambda p: Row(name = p[6], age = float(p[3])))

# Infer the schema, and register the DataFrame as a table.
schemaP = spark.createDataFrame(places)
schemaP.createOrReplaceTempView("poihubei")

# SQL can be run over DataFrames that have been registered as a table.
poluted = spark.sql("SELECT name, age FROM poihubei WHERE age <= 50 AND age <= 100")

# The results of SQL queries are Dataframe objects.
# rdd returns the content as an :class:`pyspark.RDD` of :class:`Row`.
polutedNames = poluted.rdd.map(lambda p: "Name: " + p.name + " Age: "+str(p.age))
polutedNames.take(10)
#for name in teenNames:
#    print(name)


```




    ['Name: 雷家寨 Age: 31.6138',
     'Name: 分水岭 Age: 32.3663',
     'Name: 毛田咀 Age: 11.4878',
     'Name: 樟木村 Age: 40.3982',
     'Name: 云丰村 Age: 46.1054',
     'Name: 五丘田 Age: 49.1783',
     'Name: 小沟 Age: 39.9625',
     'Name: 巨耳沟 Age: 49.972',
     'Name: 货郎冲 Age: 16.6083',
     'Name: 跑马坪(1) Age: 36.4044']


