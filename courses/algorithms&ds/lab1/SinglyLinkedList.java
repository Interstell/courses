package lists;

public class SinglyLinkedList {
	
	private int length = 0;
	private Node headNode;
	
	public SinglyLinkedList(){
		
	}
	
	private boolean isCorrectInput(String elem){
		try{
			Integer.parseInt(elem);
		}
		catch (NumberFormatException e){
			return false;
		}
		if (Math.abs(Integer.parseInt(elem)) > 10) return false;
		
		return true;
	}
	
	public void add(String elem){
		if (!isCorrectInput(elem)) return;
		
		if (length == 0){
			headNode = new Node(elem);
			length++;
			return;
		}
		
		Node tmpNode = headNode;
		while (tmpNode.nextNode != null){
			tmpNode = tmpNode.nextNode;
		}
		tmpNode.nextNode = new Node(elem);
		length++;
	}
	
	public void add(int index, String elem){
		if (!isCorrectInput(elem)) return;
		if (index > length) return;
	
		if (index == 0){
			Node tmpNode = headNode;
			headNode = new Node(elem);
			headNode.nextNode = tmpNode;
			length++;
			return;
		}
		
		Node tmpNode = headNode;
		for (int i = 0; i < index - 1; i++){
			tmpNode = tmpNode.nextNode;
		}
		Node nextNode = tmpNode.nextNode;
		tmpNode.nextNode = new Node(elem);
		tmpNode.nextNode.nextNode = nextNode;
	}
	
	public void print(){
		Node tmpNode = headNode;
		while(tmpNode != null){
			System.out.print(tmpNode.element + " ");
			tmpNode = tmpNode.nextNode;
		}
		System.out.println("");
	}
	
	public String get(int index){
		Node tmpNode = headNode;
		for (int i = 0; i < index; i++){
			if (tmpNode.nextNode == null){
				return "NULL";
			}
			tmpNode = tmpNode.nextNode;
		}
		return tmpNode.element;
	}
	
	public String delete(int index){
		if (index == 0){
			String res = headNode.element;
			headNode = headNode.nextNode;
			length--;
			return res;
		}
		Node tmpNode = headNode;
		for (int i = 0; i<index - 1; i++){
			if (tmpNode.nextNode == null){
				return "NULL";
			}
			tmpNode = tmpNode.nextNode;
		}
		
		String res = tmpNode.nextNode.element;
		tmpNode.nextNode = tmpNode.nextNode.nextNode;
		length--;
		return res;
	}
	
	public int length(){
		return length;
	}
		
}