package mapper;

import java.io.IOException;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapred.MapReduceBase;
import org.apache.hadoop.mapred.Mapper;
import org.apache.hadoop.mapred.OutputCollector;
import org.apache.hadoop.mapred.Reporter;

public class QueryTweetsMapper extends MapReduceBase implements Mapper<LongWritable, Text, IntWritable, LongWritable> {

    float UPPER =  50.08611f;
    float LOWER =  49.63817f;
    float LEFT  = -119.90303f;
    float RIGHT = -118.96095f;

    @Override
    public void map(LongWritable key, Text value, OutputCollector<IntWritable, LongWritable> output,
	    Reporter reporter) throws IOException {
		//Split the text input into array
		String[] line = value.toString().split(",");

		//Cast String input to double
		float lat = Float.parseFloat(line[0]);
		float lon = Float.parseFloat(line[1]);

		//Check if the point lies into our bounding box
		if (lat < LOWER || lat > UPPER || lon < LEFT || lon > RIGHT) return;
		
		//Send the (key,value) out
		output.collect(new IntWritable(1), new LongWritable(1));
   }
}
