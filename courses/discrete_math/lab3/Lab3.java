package lab3;

public class Lab3 {
	
	public static final int INF = (int)(Integer.MAX_VALUE / 2);
	
	public static void printMatrix(int[][] matrix){ 
		//выводит матрицу на экран
		for (int i = 0; i<matrix.length; i++){
			for (int j = 0; j<matrix[i].length; j++)
				if (matrix[i][j] == INF) System.out.print(" - ");
				else System.out.format("%2d ", matrix[i][j]);
			System.out.println("");	
		}
		System.out.println("");
	}
	
	public static void printMatrix(int[][] matrix, boolean[] bannedI, boolean[] bannedJ){
		System.out.print("    ");
		for (int j = 0; j<matrix.length; j++){
			if (!bannedJ[j]){
				System.out.format("%d  ", j+1);
			}
		}
		System.out.format("\n    ");
		for (int j = 0; j<matrix.length; j++){
			if (!bannedJ[j]){
				System.out.format("---");
			}
		}
		System.out.format("\n");
		for (int i = 0; i<matrix.length; i++){
			if (!bannedI[i]){
				System.out.format("%d |", i+1);
				for (int j = 0; j<matrix.length; j++){
					if (!bannedJ[j]){
						if (matrix[i][j] == INF) System.out.print(" - ");
						else System.out.format("%2d ", matrix[i][j]);
					}
				}
				System.out.println("");
			}
		}
		System.out.println("");
	}
	
	public static int NearestCityAlg(int[][] matrix){
		//жадный алгоритм поиска методой ближайшего города
		boolean passed[] = new boolean[matrix.length];
		int resLen = 0;
		String path = new String();
		for (boolean i:passed){
			i = false;
		}
		int iterCount = 0;
		int start = 0;
		int i = start;
		path += Integer.toString(start + 1) + " - ";
		passed[i] = true;
		while (iterCount < matrix.length - 1){
			int min = INF;
			int minJ = 0;
			for (int j = 0; j<matrix.length; j++){
				if (matrix[i][j] != INF && matrix[i][j] < min && !passed[j]){
					min = matrix[i][j];
					minJ = j;
				}
			}
			resLen+=matrix[i][minJ];
			path += Integer.toString(minJ + 1) + " - ";
			i = minJ;
			passed[minJ] = true;
			iterCount++;
		}
		resLen += matrix[i][start];	
		path += Integer.toString(start + 1);
		System.out.println("Min loop path by Nearest City Algorhytm: ");
		System.out.println(path);
		return resLen;
	}
	
	public static int findMinInRow(int[][] matrix, int row, boolean[] bannedI, boolean[] bannedJ, int bannedIndex){
		//найти минимумальный элемент в строке
		int min = INF;
		for (int j = 0; j < matrix.length; j++) {
			if (matrix[row][j] != INF && matrix[row][j] < min && !bannedI[row] && !bannedJ[j] && j != bannedIndex) {
				min = matrix[row][j];
			}
		}
		return min;
	}
	
	public static int findMinInColumn(int[][] matrix, int column, boolean[] bannedI, boolean[] bannedJ, int bannedIndex){
		//найти минимальный элемент в столбце
		int min = INF;
		for (int i = 0; i < matrix.length; i++) {
			if (matrix[i][column] != INF && matrix[i][column] < min && !bannedI[i] && !bannedJ[column] && i != bannedIndex) {
				min = matrix[i][column];
			}
		}
		return min;
	}
	
	public static int leadMatrixByRowsAndCols(int[][] matrix, boolean[] bannedI, boolean[] bannedJ){
		//приведение матрицы сначала по строкам, затем по столбцам
		int tempResL = 0;
		for (int i = 0; i < matrix.length; i++) {
			int min = findMinInRow(matrix, i, bannedI, bannedJ, INF);
			for (int j = 0; j < matrix.length; j++) {
				if (matrix[i][j] != INF && !bannedI[i] && !bannedJ[j] ) {
					matrix[i][j] -= min;
				}
			}
			tempResL += min;
		}
		for (int j = 0; j < matrix.length; j++) {
			int min = findMinInColumn(matrix, j, bannedI, bannedJ, INF);
			for (int i = 0; i < matrix.length; i++) {
				if (matrix[i][j] != INF && !bannedI[i] && !bannedJ[j]) {
					matrix[i][j] -= min;
				}
			}
			tempResL += min;
		}
		return tempResL;
	}
	
	public static int LittleAlg(int[][] matrix){
		//алгоритм Литтла
		int resL = 0;
		int[][] matrixClone = matrix.clone();
		for(int i = 0; i<matrix.length; i++){
			matrixClone[i] = matrix[i].clone();
		}
		boolean bannedI[] = new boolean[matrix.length];
		boolean bannedJ[] = new boolean[matrix.length];
		
		for (int i = 0; i < matrix.length; i++) {
			bannedI[i] = false;
			bannedJ[i] = false;
		}		
		Path path = new Path(matrix.length);
		
		for (int iter = 0; iter < matrix.length; iter++) {
			resL += leadMatrixByRowsAndCols(matrix, bannedI, bannedJ);
			printMatrix(matrix, bannedI, bannedJ);
			int maxWeightI = -1;
			int maxWeightJ = -1;
			int maxWeight = -INF;
			for (int i = 0; i<matrix.length; i++){
				for (int j = 0; j<matrix.length; j++){
					if (matrix[i][j] == 0 && !bannedI[i] && !bannedJ[j]){
						int weight =  findMinInRow(matrix, i, bannedI, bannedJ, j) +  findMinInColumn(matrix, j, bannedI, bannedJ, i);
						if (weight > maxWeight && !path.checkForEquality(i, j)){
							maxWeight = weight;
							maxWeightI = i;
							maxWeightJ = j;
						}
					}
				}
			}
			path.add(new Element(maxWeightI, maxWeightJ));
			bannedI[maxWeightI] = true;
			bannedJ[maxWeightJ] = true;
			matrix[maxWeightJ][maxWeightI] = INF;
		}
		System.out.println("Min loop path by Little Algorhytm: ");
		System.out.println(path.getPath(matrixClone));
		//path.printElems();
		return path.getLength(matrixClone);
	}

	public static void main(String[] args) {
		
		int aMatrix[][] = { 
				{ INF, 15, 11, 2, 8, 6, 9 },
				{ 15, INF, 4, 11, 6, 15, 7 }, 
				{ 11, 4, INF, 14, 3, 9, 5 },
				{ 2, 11, 14, INF, 16, 11, 9 }, 
				{ 8, 6, 3, 16, INF, 5, 10 },
				{ 6, 15, 9, 11, 5, INF, 4 },
				{ 9, 7, 5, 9, 10, 4, INF } 
			};
		
		printMatrix(aMatrix);
		
		int cityLen = NearestCityAlg(aMatrix);
		System.out.format("Min loop length by Nearest City Algorhytm: %d\n", cityLen);
		System.out.println("");
		int littleLen = LittleAlg(aMatrix);
		System.out.format("Min loop length by Little Algorhytm: %d\n", littleLen);
	}

}
