package combiner;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;
import java.util.List;
import java.util.Vector;
import java.lang.Comparable;

import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.mapred.MapReduceBase;
import org.apache.hadoop.mapred.OutputCollector;
import org.apache.hadoop.mapred.Reducer;
import org.apache.hadoop.mapred.Reporter;

public class QueryCombiner extends MapReduceBase implements Reducer<Text, Text, Text, Text>{

    @Override
    public void reduce(Text key, Iterator<Text> values, OutputCollector<Text, Text> output, Reporter reporter) throws IOException {

        Double sum = 0.00;
        int count = 0;

	// aggregate through values to calculate sum and count
	/* ADD CODE HERE */

        // aggreagate sum and count
    	/* ADD CODE HERE */
	}
}

