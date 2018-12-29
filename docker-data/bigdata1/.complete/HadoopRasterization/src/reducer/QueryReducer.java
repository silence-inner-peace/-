package reducer;

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
import org.apache.hadoop.io.DoubleWritable;
import org.apache.hadoop.mapred.MapReduceBase;
import org.apache.hadoop.mapred.OutputCollector;
import org.apache.hadoop.mapred.Reducer;
import org.apache.hadoop.mapred.Reporter;

public class QueryReducer extends MapReduceBase implements Reducer<Text, Text, Text, DoubleWritable>{

    @Override
    public void reduce(Text key, Iterator<Text> values, OutputCollector<Text, DoubleWritable> output, Reporter reporter) throws IOException {

        Double sum = 0.00;
        int count = 0;

	//Iterate through values to calculate sum and count
        while(values.hasNext()){
            String[] rad_count = values.next().toString().split(",");
            sum += Double.parseDouble(rad_count[0]);
            count += Integer.parseInt(rad_count[1]);
        }

        // get average
        output.collect(key, new DoubleWritable(sum / count));
    }
}

