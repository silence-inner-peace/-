package runhadoop;

import mapper.QueryMapper;
import reducer.QueryReducer;
import combiner.QueryCombiner;

import java.io.*;
import java.util.*;
import java.net.*;

import org.apache.hadoop.fs.*;
import org.apache.hadoop.conf.*;
import org.apache.hadoop.io.*;
import org.apache.hadoop.util.*;
import org.apache.hadoop.mapred.FileInputFormat;
import org.apache.hadoop.mapred.FileOutputFormat;
import org.apache.hadoop.mapred.JobClient;
import org.apache.hadoop.mapred.JobConf;
import org.apache.hadoop.mapred.KeyValueTextInputFormat;
import org.apache.hadoop.mapred.TextInputFormat;
import org.apache.hadoop.mapred.TextOutputFormat;

public class RunRadQuery {
    
    public static void main(String[] args) throws Exception{
	long start;
   	long end;
	long end2;
	long time = 0;

	Path in = new Path(args[1]);
	Path interMediate = new Path(args[2]);

	JobConf conf1 = new JobConf(RunRadQuery.class);
	conf1.set("startLat", args[4]);
	conf1.set("endLat", args[5]);
	conf1.set("startLon", args[6]);
	conf1.set("endLon", args[7]);
	conf1.set("cellSize", args[8]);

	conf1.set("mapred.textoutputformat.separator", ":");
	conf1.setJobName("QueryRadiation");	
	conf1.setMapperClass(QueryMapper.class);
	conf1.setReducerClass(QueryReducer.class);
	conf1.setCombinerClass(QueryCombiner.class);
	
	conf1.setOutputKeyClass(Text.class);
	conf1.setOutputValueClass(Text.class);
	conf1.setInputFormat(TextInputFormat.class);	
	conf1.setOutputFormat(TextOutputFormat.class);
	FileInputFormat.setInputPaths(conf1, in);
	FileOutputFormat.setOutputPath(conf1, interMediate);			
	
	start =  new Date().getTime();	
	System.out.println("Start Job");
	JobClient.runJob(conf1);
	System.out.println("End Job");
	end =  new Date().getTime();
	time = (end-start);
	System.out.println("It took " + time + " ms to run MapReduce jobs");

	FileSystem fs = FileSystem.get(new Configuration());
//	BufferedReader br = new BufferedReader(new InputStreamReader(fs.open(interMediate)));

	double xMin = Double.parseDouble(args[6]);
	double yMin = Double.parseDouble(args[4]);
	double xMax = Double.parseDouble(args[7]);
	double yMax = Double.parseDouble(args[5]);
	double cellSize = Double.parseDouble(args[8]);
	int nCol = (int)Math.ceil((xMax - xMin) / cellSize);
	int nRow = (int)Math.ceil((yMax - yMin) / cellSize);

	double cellValues[] = new double[nCol * nRow];
	double value;

	for(int i = 0; i < nCol * nRow; i++)
	{
		cellValues[i] = -1;
	}

	String line;
	String lines[];
	int x;
	int y;

	FileStatus[] fss = fs.listStatus(interMediate);
	for(FileStatus status : fss)
	{
		Path path = status.getPath();
		BufferedReader br = new BufferedReader(new InputStreamReader(fs.open(path)));

		while(true)
		{
			line = br.readLine();
			if(line == null || line.equals(""))
			{
				break;
			}
			lines = line.split(":");
			value = Double.parseDouble(lines[1]);
			lines = lines[0].split(",");
			x = Integer.parseInt(lines[1]);
			y = Integer.parseInt(lines[0]);

			cellValues[y * nCol + x] = value;
		}

		br.close();
	}

	FileWriter fw = new FileWriter(args[3]);
	BufferedWriter bw = new BufferedWriter(fw);


	bw.write("ncols\t" + nCol);
	bw.newLine();
	bw.write("nrows\t" + nRow);
	bw.newLine();
	bw.write("xllcorner\t" + xMin);
	bw.newLine();
	bw.write("yllcorner\t" + yMin);
	bw.newLine();
	bw.write("cellsize\t" + cellSize);
	bw.newLine();
	bw.write("NODATA_value\t-1");
	bw.newLine();
	
	for(int i = nRow - 1; i >= 0; i--)
	{
		for(int j = 0; j < nCol; j++)
		{
			if(cellValues[i * nCol + j] < 0)
			{
				bw.write("\t-1");
			}
			else
			{
				bw.write("\t" + cellValues[i * nCol + j]);
			}
		}
		bw.newLine();
	}

	bw.close();
	fw.close();

	end2 =  new Date().getTime();
	time = (end2-end);
	System.out.println("It took " + time + " ms to generate ascii grid");
	time = (end2-start);
	System.out.println("Total time: " + time + " ms");

    }

}


