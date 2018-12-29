package sequential;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;

public class SequentialRasterization {

	/**
	 * @param args inputFileName outputFileName xMin yMin xMax yMax cellSize
	 * @throws IOException 
	 */
	public static void main(String[] args) throws IOException 
	{
		Date date1 = new java.util.Date();
		SimpleDateFormat format = new SimpleDateFormat("hh:mm:ss");
		System.out.println("Start at " + format.format(date1));
		
		double xMin, yMin, xMax, yMax, cellSize;
		int nCol, nRow;
		int pointCount[];
		double pointAve[];
		
		xMin = Double.parseDouble(args[2]);
		yMin = Double.parseDouble(args[3]);
		xMax = Double.parseDouble(args[4]);
		yMax = Double.parseDouble(args[5]);
		cellSize = Double.parseDouble(args[6]);
		
		nCol = (int)Math.ceil((xMax - xMin) / cellSize);
		nRow = (int)Math.ceil((yMax - yMin) / cellSize);
		
		xMax = xMin + nCol * cellSize;
		yMax = yMin + nRow * cellSize;
		
		pointCount = new int[nCol * nRow];
		pointAve = new double[nCol * nRow];
		
		for(int i = 0; i < nCol * nRow; i++)
		{
			pointCount[i] = 0;
			pointAve[i] = 0.0;
		}
		
		
		FileReader fReader = new FileReader(args[0]);
		BufferedReader bReader = new BufferedReader(fReader);
		
		String line;
		String lines[];
		
		double x;
		double y;
		double value;
		int colID;
		int rowID;
		
		while(true)
		{
			line = bReader.readLine();
			if(line == null || line.equals(""))
			{
				break;
			}
			
			lines = line.split(",");

			if(lines.length < 5 || lines[0].isEmpty() || lines[1].isEmpty() || lines[2].isEmpty() || lines[3].isEmpty())
			{
				continue;
			}

			x = Double.parseDouble(lines[2]);
			y = Double.parseDouble(lines[1]);
			value = Double.parseDouble(lines[3]);
			
			if(x < xMin || x > xMax || y < yMin || y > yMax)
				continue;
			
			colID = (int)((x - xMin) / cellSize);
			rowID = (int)((y - yMin) / cellSize);
			
			pointCount[rowID * nCol + colID] ++;
			pointAve[rowID * nCol + colID] += value;			
		}
		
		bReader.close();
		fReader.close();
		
		for(int i = 0; i < nCol * nRow; i++)
		{
			if(pointCount[i] > 0)
			{
				pointAve[i] = pointAve[i] / pointCount[i];
			}
		}
		
		
		FileWriter fWriter = new FileWriter(args[1]);
		BufferedWriter bWriter = new BufferedWriter(fWriter);
		
		bWriter.write("ncols\t" + nCol);
		bWriter.newLine();		
		bWriter.write("nrows\t" + nRow);
		bWriter.newLine();
		bWriter.write("xllcorner\t" + xMin);
		bWriter.newLine();
		bWriter.write("yllcorner\t" + yMin);
		bWriter.newLine();
		bWriter.write("cellsize\t" + cellSize);
		bWriter.newLine();
		bWriter.write("NODATA_value\t-1");
		bWriter.newLine();
		
		for(int i = nRow - 1; i >= 0; i--)
		{
			for(int j = 0; j < nCol; j++)
			{
				if(pointCount[i * nCol + j] > 0)
				{
					bWriter.write("\t" + pointCount[i * nCol + j]);
				}
				else
				{
					bWriter.write("\t-1");
				}
			}
			bWriter.newLine();
		}
		
		
		
		bWriter.close();
		fWriter.close();
		
		Date date2 = new java.util.Date();
		
		System.out.println("Finished at " + format.format(date2));
		System.out.println("Total time spent: " + (double)(date2.getTime() - date1.getTime())/1000 + " seconds");

	}

}
