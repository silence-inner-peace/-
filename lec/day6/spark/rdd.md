

```python
import numpy as np
import random
```


```python
import pyspark
sc = pyspark.SparkContext('local[*]')

```


```python
# do something to prove it works
rdd = sc.parallelize(range(1000))
rdd.takeSample(False, 5)
```




    [605, 316, 650, 405, 173]



# RDD


```python
# word count
rtxt = sc.textFile('file:///trn/testdata/md/p2p_non_blocking_ex.md')
rcount =  rtxt.flatMap(lambda l: l.split()).map(lambda w: (w,1)).reduceByKey(lambda a,b: a+b)
rcount.take(5)
```




    [('#', 1), ('exercise', 3), ('Now', 2), ('is', 31), ('dig', 1)]




```python
rcount =  rtxt.flatMap(lambda l: l.split()).map(lambda w: (w,1)).countByKey()
list(rcount.items())[:5]
```




    [('#', 1),
     ('Non-blocking', 1),
     ('communications', 2),
     ('-', 1),
     ('exercise', 3)]




```python
rdd.cache()
```




    PythonRDD[11] at RDD at PythonRDD.scala:49




```python
b = sc.broadcast([26, 78, 90])
b.value
```




    [26, 78, 90]




```python
# Accumulator
accum = sc.accumulator(100)
sc.parallelize([1, 2, 3, 4]).foreach(lambda x: accum.add(x))
accum.value
# Accumulator not work in transformation func (trans doesn't do things)
```




    110




```python
def samplepi(p):
    x, y = random.random(), random.random()
    return 1 if x*x + y*y < 1.0 else 0
count = sc.parallelize(range(10000000)).map(samplepi).reduce(lambda a,b:a+b)
```


```python
count * 4.0 / 10000000
```




    3.1412288


