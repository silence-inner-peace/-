
# coding: utf-8

# In[1]:


import numpy as np
import random


# In[9]:


import pyspark
from pyspark.sql import SparkSession

spark = SparkSession     .builder     .appName("Python Spark SQL basic example")     .config("spark.some.config.option", "some-value")     .getOrCreate()
sc = spark.sparkContext


# # Spark SQL

# In[27]:


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

