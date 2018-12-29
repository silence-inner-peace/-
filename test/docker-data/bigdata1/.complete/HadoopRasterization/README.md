# Demo code for hadoop tutorial

## Content
Do query and rasterization for radiation dataset

## Progress
- [x] output "$rowIndex,$colIndex:$meanGridValue" ( result approved by spark)
- [ ] transform output to ascii grid

## Sample Run (prepare input and output files first)

    hadoop jar dist/queryradiation.jar classes/runhadoop/RunRadQuery.class /user/dyin4/radiation.csv temp1.csv result.asc 30 60 120 160 0.05

where the arguments represent for inputFile, intermediateFile, outputFile, startLat, endLat, startLong, endLong, cellSize
