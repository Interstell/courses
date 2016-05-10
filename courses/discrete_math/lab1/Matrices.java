package lab1;

import java.util.Scanner;

public abstract class Matrices {

	public static int[][] fillMatrix(int n){ //заполнение матрицы с клавиатуры
		int[][] matrix = new int[n][n];
		Scanner scan = new Scanner(System.in);
		for (int i = 0; i<n; i++)
			for (int j = 0; j<n; j++)
				matrix[i][j]=scan.nextInt(); //ввод значений с клавиатуры
		return matrix;
	}
	public static int[][] getCopy(int[][] matrix){ //возвращает копию двумерного массива matrix
		int n = matrix.length;
		int[][] res = new int[n][n];
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				res[i][j] = matrix[i][j];
		return res;
	}
	public static void printMatrix(int[][] matrix){ //выводит матрицу на экран
		for (int i = 0; i<matrix.length; i++){
			for (int j = 0; j<matrix[i].length; j++)
				System.out.print((matrix[i][j]==-1)?"- ":matrix[i][j]+" ");
			System.out.println("");
		}
		System.out.println("");
	}
	public static int[][] multiplyMatrices(int[][] matrixA, int[][] matrixB){ //умножает матрицы
		int n = matrixA.length;
		int[][] matrixC = new int[n][n];
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++){
				matrixC[i][j] = 0;
				for (int k = 0; k < n; k++)
					matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
			}
		return matrixC;
	}
	public static int[][] fillDMatrixFromAMatrixFirst(int[][] AMatrix){ //первое заполнение матрицы расстояний из матрицы смежности
		int n = AMatrix.length;
		int[][] DMatrix = new int[n][n];
		for (int i = 0; i<n; i++)
			for (int j = 0; j<n; j++){
				if (i == j) DMatrix[i][j]=0; //главная диагональ
				else if (AMatrix[i][j] == 1) DMatrix[i][j] = 1;
				else DMatrix[i][j] = -1;
			}
		return DMatrix;
	}
	public static void fillDMatrixFromAMatrix(int[][] AMatrix, int[][] DMatrix, int currIteration){ //дополняет матрицу расстояний из матрицы смежности в степени k(currIteration) 
		int n = AMatrix.length;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (AMatrix[i][j] > 0 && (DMatrix[i][j] == -1))
					DMatrix[i][j] = currIteration;
	}
	public static int[][] getDistanceMatrix(int[][] AMatrix){ //возвращает матрицу расстояний
		int[][] sourceAMatrix = getCopy(AMatrix);
		int n = AMatrix.length;
		int[][] DMatrix = fillDMatrixFromAMatrixFirst(AMatrix);
		for (int i = 2; i < n; i++){ //возводим в степень от 2 до n-1
			AMatrix = multiplyMatrices(AMatrix, sourceAMatrix);
			fillDMatrixFromAMatrix(AMatrix, DMatrix, i);
		}
		return DMatrix;
	}
	public static int[][] getReachMatrix(int[][] DMatrix){ //возвращает матрицу достижимости
		int n = DMatrix.length;
		int[][] RMatrix = new int[n][n];
		for (int i = 0; i<n; i++)
			for (int j = 0; j<n; j++)
				RMatrix[i][j] = (DMatrix[i][j] >= 0)?1:0;
		return RMatrix;
	}
	public static int[][] getBooleanAplusATransponed(int[][] AMatrix){ //возвращает B(A+AT)
		int n = AMatrix.length;
		int[][] ATMatrix = new int[n][n];
		for (int i = 0; i<n; i++)
			for (int j = 0; j<n; j++)
				ATMatrix[i][j] = AMatrix[j][i];
		for (int i = 0; i<n; i++)
			for (int j = 0; j<n; j++)
				ATMatrix[i][j]+=AMatrix[i][j];
		return ATMatrix;
	}
	public static int[][] getBooleanRmultRTransponed(int[][] RMatrix){ //возвращает B(R*RT) - квадратно-диагональная форма
		int n = RMatrix.length;
		int[][] RTMatrix = new int[n][n];
		for (int i = 0; i<n; i++)
			for (int j = 0; j<n; j++)
				RTMatrix[i][j] = RMatrix[j][i];
		for (int i = 0; i<n; i++)
			for (int j = 0; j<n; j++)
				RTMatrix[i][j]*=RMatrix[i][j];
		return RTMatrix;
	}
	
	public static int[][] getBooleanRplusRTransponed(int[][] RMatrix){ //возвращает B(R+RT)
		int n = RMatrix.length;
		int[][] RTMatrix = new int[n][n];
		for (int i = 0; i<n; i++)
			for (int j = 0; j<n; j++)
				RTMatrix[i][j] = RMatrix[j][i];
		for (int i = 0; i<n; i++)
			for (int j = 0; j<n; j++)
				RTMatrix[i][j]+=RMatrix[i][j];
		return RTMatrix;
	}
	
	public static void calculateAmountWays(int D[][]) {
		int amount = 0;
		for (int i = 0; i < D.length; i++) {
			for (int j = 0; j < D.length; j++) {
				if (D[i][j] == -1)
					amount++;
			}
		}
		System.out.printf("Empty items: %d\n", amount);
		for (int wayCount = 1; wayCount < D.length; wayCount++) {
			amount = 0;
			for (int i = 0; i < D.length; i++) {
				for (int j = 0; j < D.length; j++) {
					if (D[i][j] == wayCount)
						amount++;
				}
			}
			System.out.printf("Ways with length %d: %d\n", wayCount, amount);
		}
	}
	
	public static void calculateAmountLoops(int[][] A) {
		int amount = 0;
		for (int i = 0; i < A.length; i++) {
			if (A[i][i] != 0)
				amount++;
		}
		if (amount == 0) {
			System.out.println("There are no loops in this graph");
			return;
		}
		for (int i = 0; i < A.length; i++) {
			if (A[i][i] != 0) {
				System.out.printf("%d vertex has %d loops\n", i + 1, A[i][i]);
			}
		}
	}

	public static void calculateLengthLoops(int[][] D) {
		int amount = 0;
		for (int i = 0; i < D.length; i++) {
			if (D[i][i] != 0)
				amount++;
		}
		if (amount == 0) {
			System.out.println("There are no loops in this graph");
			return;
		}
		for (int i = 0; i < D.length; i++) {
			if (D[i][i] != 0) {
				System.out.printf("Length of loop on %d vertex is %d\n", i + 1, D[i][i]);
			}
		}
	}
	
	
	public static void main(String[] args) {
	
	int[][] AMatrix = {
			{0,1,0,1,0,0,0,0,0},
			{0,0,1,0,0,0,0,0,0},
			{0,0,0,1,0,0,0,0,0},
			{0,0,0,0,1,0,0,0,0},
			{0,0,0,0,0,1,0,0,0},
			{0,0,0,0,0,0,1,0,0},
			{0,0,0,0,0,0,0,1,0},
			{0,0,0,0,1,0,0,0,0},
			{0,0,0,0,0,0,0,1,0}
	};
	/*int[][] AMatrix = {{0,1,0,0,0,0,0},
			{0,0,0,0,1,0,0},
			{0,0,0,0,0,0,0},
			{0,0,1,0,0,0,0},
			{0,0,1,1,0,0,1},
			{0,0,0,0,1,0,0},
			{0,0,0,0,0,1,0}
	};*/
	Scanner scan = new Scanner(System.in);
	//System.out.println("Matrix size:"); 
	//получаем с клавиатуры размер матрицы
	int n = 9;
	
	System.out.println("Adjacency matrix:"); 
	printMatrix(AMatrix);
	//получаем с клавиатуры матрицу смежности
	//int[][]AMatrix = fillMatrix(n);
	System.out.println("Distance matrix:"); 
	//вычисляем матрицу расстояний
	int[][] DMatrix = getDistanceMatrix(AMatrix); 
	printMatrix(DMatrix);
	System.out.println("Reach matrix:"); 
	//вычисляем матрицу достижимости
	int[][] RMatrix = getReachMatrix(DMatrix); 
	printMatrix(RMatrix);
	//вычисляем квадратно-диагональную форму матрицы достижимости
	System.out.println("B(R*R^T): square - diagonal"); 
	int[][] BAMatrix = getBooleanRmultRTransponed(RMatrix);
	printMatrix(BAMatrix);
	System.out.println("B(R+R^T)"); 
	//получаем B(R+RT) для определения типа связности
	int[][] BRMatrix = getBooleanRplusRTransponed(RMatrix); 
	printMatrix(BRMatrix);
	
	/*R = 1 - сильносвязный
	R+RT = 1 - односторонне связный
	R+RT != 1 - слабо связный
	R+RT с нулевой строкой или элем - несвязный*/
	}

}
