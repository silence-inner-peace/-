package runhadoop;


import mapper.*;
import reducer.*;
import java.util.Date;

import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.mapred.FileInputFormat;
import org.apache.hadoop.mapred.FileOutputFormat;
import org.apache.hadoop.mapred.JobClient;
import org.apache.hadoop.mapred.JobConf;
import org.apache.hadoop.mapred.KeyValueTextInputFormat;
import org.apache.hadoop.mapred.TextInputFormat;
import org.apache.hadoop.mapred.TextOutputFormat;
import org.apache.hadoop.mapred.lib.MultipleOutputs;

public class RunMovePattern {
    
    public static void main(String[] args) throws Exception{
	long start;
   	long end;
	long time = 0;
	
	//Define input and output based on user arguments
	Path in = new Path(args[1]);
	Path out = new Path(args[2]);


	//Define Job Config
	JobConf conf = new JobConf(RunMovePattern.class);
	conf.set("mapred.textoutputformat.separator", ",");
	conf.setJobName("QueryTweets");	

	//Set Mapper and Reducer Class
	conf.setMapperClass(QueryTweetsMapper.class);
	conf.setCombinerClass(QueryTweetsReducer.class);
	conf.setReducerClass(QueryTweetsReducer.class);

	//Assign Input and output
	conf.setOutputKeyClass(IntWritable.class);
	conf.setOutputValueClass(LongWritable.class);
	conf.setInputFormat(TextInputFormat.class);	

	FileInputFormat.setInputPaths(conf, in);
	FileOutputFormat.setOutputPath(conf, out);			
	
	//Run the job
	start =  new Date().getTime();
	System.out.println("Start Job");
	JobClient.runJob(conf);
	System.out.println("End Job");
	end =  new Date().getTime();
	time += (end-start);
	System.out.println("It took " + time + " ms to make cells jobs");
    }

}


