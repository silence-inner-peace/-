-- Load the data from HDFS and define the schema
data = LOAD '/user/soltani2/2014augtweets.txt' USING PigStorage(',') AS (lat:float , lon:float);

-- Filter out for geographical bound
data_filtered = FILTER data BY (lat >= 49.63817 AND lat <= 50.08611 AND lon >= -119.90303 AND lon <= -118.96095);

-- Group all the records
data_group = GROUP data_filtered ALL;

-- Find out count
final_count = FOREACH data_group GENERATE COUNT(data_filtered);

-- Output the result
DUMP final_count

