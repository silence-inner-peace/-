import pyspark
# run local mode to use local file sys
sc = pyspark.SparkContext('local[*]')
# do something to prove it works
rdd = sc.parallelize(range(1000))
rdd.takeSample(False, 5)
# use file:///path/to/file to avoid no HDFS problem

# word count
rtxt = sc.textFile('file:///trn/testdata/md/p2p_non_blocking_ex.md')
rcount =  rtxt.flatMap(lambda l: l.split()).map(lambda w: (w,1)).reduceByKey(lambda a,b: a+b)
rcount.take(5)

#  Estimate π (compute-intensive task).
# Pick  random points in the unit square ((0, 0) to (1,1)),
# See how many fall in the unit circle. The fraction should be π / 4
# Note that “parallelize” method creates an RDD
def sample(p):
    x, y = random(), random()
    return 1 if x*x + y*y < 1 else 0

count = spark.parallelize(xrange(0, NUM_SAMPLES)).map(sample) \
             .reduce(lambda a, b: a + b)
print "Pi is roughly %f" % (4.0 * count / NUM_SAMPLES)

