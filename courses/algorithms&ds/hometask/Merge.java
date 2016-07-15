package home;

public class Merge {

	public static void TwoWayMerge(int[] leftArray, int[] rightArray, int[] result) {
		int iLeft = 0, iRight = 0, iResult = 0;
		while (iLeft < leftArray.length && iRight < rightArray.length) {
			if (leftArray[iLeft] <= rightArray[iRight]) {
				result[iResult++] = leftArray[iLeft++];
			} else {
				result[iResult++] = rightArray[iRight++];
			}
		}
		System.arraycopy(leftArray, iLeft, result, iResult, leftArray.length - iLeft);
		System.arraycopy(rightArray, iRight, result, iResult, rightArray.length - iRight);
	}

}
