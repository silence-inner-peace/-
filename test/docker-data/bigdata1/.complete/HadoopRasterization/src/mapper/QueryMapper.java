package mapper;

import java.io.IOException;
import java.util.Random;

import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapred.MapReduceBase;
import org.apache.hadoop.mapred.Mapper;
import org.apache.hadoop.mapred.OutputCollector;
import org.apache.hadoop.mapred.Reporter;
import org.apache.hadoop.mapred.JobConfigurable;
import org.apache.hadoop.mapred.JobConf;

public class QueryMapper extends MapReduceBase implements Mapper<LongWritable, Text, Text, Text>, JobConfigurable{

    // query variables with default values( for a quick view of input format) 
    double startLat = 0.0;
    double endLat = 80.0;
    double startLon = -160.0 ;
    double endLon = 0.0;
    double cellSize= 20.0;

    // not quite clear about its effect
    int MAX_NUMBER_OF_REDUCERS = 4;


    /* 
     * Get time window and bouding box
     */
    @Override
    public void configure(JobConf conf) {
        startLat = Double.parseDouble(conf.get("startLat"));
        endLat = Double.parseDouble(conf.get("endLat"));
        startLon = Double.parseDouble(conf.get("startLon"));
        endLon = Double.parseDouble(conf.get("endLon"));
        cellSize = Double.parseDouble(conf.get("cellSize"));
    }

    /* 
     * Filter and generate key-value pairs
     */
    @Override
    public void map(LongWritable key, Text value, OutputCollector<Text, Text> output, Reporter reporter) throws IOException {

        String[] line = value.toString().split(",");

        // filter incomplete lines
        if (line.length < 4)
            return;
        if (line[0].isEmpty() || line[1].isEmpty() || line[2].isEmpty() || line[3].isEmpty())
            return;

        // get line data
        String time = line[0];
        double lat = Double.parseDouble(line[1]);
        double lon = Double.parseDouble(line[2]);
        double radiation_value = Double.parseDouble(line[3]);

        // non-cpm values are filtered out in 'nice_radiation.csv'
        //String unit = line[4];

        // Spatial-temporal Query
        if (lat > endLat || lat < startLat || lon > endLon || lon < startLon)
            return;

        // Generate Index
        int rowIndex = (int) ((lat - startLat) / cellSize);
        int colIndex = (int) ((lon - startLon) / cellSize);

        // Key-Value pairs
        String outKey = rowIndex + "," + colIndex;
        String outValue = radiation_value + ",1"; // radiation_value , 1(count)
        
        // Output 
        output.collect(new Text(outKey), new Text(outValue));
    }
}
