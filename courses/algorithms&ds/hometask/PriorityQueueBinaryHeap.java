package home;

public class PriorityQueueBinaryHeap {

	private int[] array;
	private int heapSize;

	public PriorityQueueBinaryHeap(int[] ar) {
		array = ar;
		heapSize = ar.length;
		buildMaxHeap();
	}

	private int getLeft(int i) {
		return 2 * i + 1;
	}

	private int getRight(int i) {
		return 2 * i + 2;
	}

	private static void swap(int[] ar, int i, int j) {
		int t = ar[i];
		ar[i] = ar[j];
		ar[j] = t;
	}

	private void sink(int i) {
		int l = getLeft(i);
		int r = getRight(i);
		int largest;

		if (l <= heapSize - 1 && array[l] > array[i]) {
			largest = l;
		} else
			largest = i;
		if (r <= heapSize - 1 && array[r] > array[largest]) {
			largest = r;
		}
		if (largest != i) {
			swap(array, i, largest);
			sink(largest);
		}
	}

	private void buildMaxHeap() {
		for (int i = (array.length - 1) / 2; i >= 0; i--) {
			sink(i);
		}
	}

	public int removeMax() {
		int result = array[0];
		if (heapSize > 1) {
			swap(array, 0, heapSize - 1);
			sink(0);
		}
		heapSize--;
		return result;
	}
}
