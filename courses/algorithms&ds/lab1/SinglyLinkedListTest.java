package lists;

public class SinglyLinkedListTest {

	public static void main(String[] args) {
		SinglyLinkedList list = new SinglyLinkedList();
		list.add("1");
		list.add("2");
		list.add("3");
		list.add("4");
		list.add("akskdajksd");
		list.add("100");
		list.print();
		
		System.out.println(list.get(0));
		System.out.println(list.get(102));
		
		list.add(0, "8");
		list.print();
		
		list.add(3,"5");
		list.print();
		
		list.delete(0);
		list.print();
		
		list.delete(3);
		list.delete(10);
		list.print();
		
		
	}

}
