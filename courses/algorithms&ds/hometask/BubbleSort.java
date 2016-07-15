package home;

public class BubbleSort {
	
	public static void BubbleSort(int[] ar){
		int n = ar.length;
		for (int i = 0; i < n - 1; i++){
			for (int j = 0; j < n - 1 -i; j++){
				if (ar[j+1] < ar[j]){
					swap(ar, j, j+1);
				}
			}
		}
	}
	
	public static void BidirectionalBubbleSort(int[] ar){
		int l = 0;
		int r = ar.length - 1;
		do {
			for (int i = l; i < r; i++){
				if (ar[i+1] < ar[i]){
					swap(ar, i, i+1);
				}
			}
			r--;
			for (int i = r; i > l; i--){
				if (ar[i] < ar[i-1]){
					swap(ar, i, i-1);
				}
			}
			l++;
		} while (l < r);
	}
	
	private static void swap(int[] ar, int i, int j){
		int t = ar[i];
		ar[i] = ar[j];
		ar[j] = t;
	}
	
}
