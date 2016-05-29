package lists;

public class StackFromListTest {
	
	
	private static void fillStackFromList(ArrayStack stack, SinglyLinkedList list){
		for (int i = 0; i<list.length(); i++){
			stack.push(Math.pow(10, Integer.parseInt(list.get(i))));
		}
	} 
	
	public static void main(String[] args) {
		ArrayStack stack = new ArrayStack(3);
		SinglyLinkedList list = new SinglyLinkedList();
		list.add("4");
		list.add("3");
		list.add("8");
		list.add("1");
		list.add("10");
		fillStackFromList(stack, list);
		list.print();
		stack.print();
	}
}
