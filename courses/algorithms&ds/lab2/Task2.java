package sort;

public class Task2 {

	public static void main(String[] args) {
		DoubleLinkedList list = new DoubleLinkedList(10);
		list.print();
		System.out.println("");
		list.referenceSort();
		list.print();
	}
}
