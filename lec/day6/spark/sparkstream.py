
# coding: utf-8

# In[1]:


from pyspark import SparkContext
from pyspark.streaming import StreamingContext

# Create a local StreamingContext with two working thread and batch interval of 1 second
sc = SparkContext("local[2]", "NetworkWordCount")
ssc = StreamingContext(sc, 1)


# In[2]:


# Create a DStream that will connect to hostname:port, like localhost:9999
lines = ssc.socketTextStream("localhost", 9999)


# In[3]:


# Split each line into words
words = lines.flatMap(lambda line: line.split(" "))


# In[4]:


# Count each word in each batch
pairs = words.map(lambda word: (word, 1))
wordCounts = pairs.reduceByKey(lambda x, y: x + y)

# Print the first ten elements of each RDD generated in this DStream to the console
wordCounts.pprint()


# In[ ]:


ssc.start()             # Start the computation
ssc.awaitTermination()  # Wait for the computation to terminate

