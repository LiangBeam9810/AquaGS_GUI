# Outlier Elimination
If there were some data which didn’t fit the distribution.You could select the checkbox of outlier elimination in the Phenotype page.
## Formula
![formula](https://latex.codecogs.com/svg.image?\left(Q_{1}-1.5IQR\right)\leq&space;X\leq\left(Q_{3}&plus;1.5IQR\right))
- First Quartile	Q1 
- Second Quartile	Q2 	
- Third Quartile	Q3 	
- Interquartile Range	IQR 

## Source
[outlier_elimination.R](../rscript/outlier_elimination.R)