package sort;

public class Task1 {
	
	public static void ShellKnutSort(Student[] ar){
		int h = 1;
		while (h <= ar.length / 3){
			h = 3 * h + 1;
		}
		while (h > 0){
			for (int i = h; i < ar.length; i++){
				Student temp = ar[i];
				int j = i;
				while (j > h-1 && ar[j-h].compareTo(temp) >= 0){
					ar[j] = ar[j-h];
					j-=h;
				}
				ar[j] = temp;
			}
			h = h/3;
		}
	}
	
	public static void printArray(Student[] ar){
		for (int i = 0 ; i<ar.length; i++){
			System.out.format("%3d. %s\n", i, ar[i].getData());
		}
	}
	
	public static Student[] createArray(int amount){
		Student[] ar = new Student[amount];
		for (int i = 0; i<ar.length; i++){
			ar[i] = new Student();
		}
		return ar;
	}
	
	public static void main(String[] args) {
		Student[] st = createArray(2);
		System.out.println("Before Shell sort:");
		printArray(st);
		System.out.println("");
		ShellKnutSort(st);
		System.out.println("After Shell sort:");
		printArray(st);
	}
}
