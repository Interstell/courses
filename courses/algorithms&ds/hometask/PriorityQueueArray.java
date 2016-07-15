package home;

public class PriorityQueueArray { // MaxPriorityQueue

	private int[] array;

	public PriorityQueueArray(int[] ar) {
		array = ar;
	}

	private int getIndexOfBiggestElement() {
		int maxI = 0;
		for (int i = 1; i < array.length; i++) {
			if (array[i] > array[maxI]) {
				maxI = i;
			}
		}
		return maxI;
	}

	private static void swap(int[] ar, int i, int j) {
		int t = ar[i];
		ar[i] = ar[j];
		ar[j] = t;
	}

	public int removeMax() {
		if (array.length == 0)
			throw new RuntimeException();
		int indexOfMax = getIndexOfBiggestElement();
		swap(array, indexOfMax, array.length - 1);
		return array[array.length - 1];
	}
}
