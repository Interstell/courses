package sort;

public class DoubleLinkedList {

	private int length;
	private ListNode head;
	private ListNode tail;
	
	public DoubleLinkedList(){
		length = 0;
		head = new ListNode();
		tail = new ListNode();
		head.student = null;
		tail.student = null;
		head.next = tail;
		tail.prev = head;
	}
	
	public DoubleLinkedList(int studentsToBeRandomFilled){
		length = 0;
		head = new ListNode();
		tail = new ListNode();
		head.student = null;
		tail.student = null;
		head.next = tail;
		tail.prev = head;
		for (int i = 0; i < studentsToBeRandomFilled; i++)
			add();
	}
	
	public void add(Student st){
		ListNode tmpNode = tail.prev;
		tmpNode.next = new ListNode(st);
		tmpNode.next.prev = tmpNode;
		tmpNode.next.next = tail;
		tail.prev = tmpNode.next;
		length++;
	}
	
	public void add(){
		ListNode tmpNode = tail.prev;
		tmpNode.next = new ListNode();
		tmpNode.next.prev = tmpNode;
		tmpNode.next.next = tail;
		tail.prev = tmpNode.next;
		length++;
	}
	
	public void set(Student st, int index){
		if (index >= length) return;
		ListNode tmpNode = head.next;
		int i = 0;
		while (i++ < index)
			tmpNode = tmpNode.next;
		tmpNode.student = st;
	}
	
	public Student get(int index){
		if (index >= length) return null;
		ListNode tmpNode = head.next;
		int i = 0;
		while (i++ < index)
			tmpNode = tmpNode.next;
		return tmpNode.student;
	}
	
	public void print(){
		ListNode tmpNode = head.next;
		int i = 0;
		while (tmpNode != tail){
			System.out.format("%3d. %s\n", i++, tmpNode.student.getData());
			tmpNode = tmpNode.next;
		}
	}
	
	public void referenceSort(){
		Student[] arr = new Student[length];
		ListNode tmpNode = head.next;
		int k = 0;
		while(tmpNode != tail){
			arr[k++] = tmpNode.student;
			tmpNode = tmpNode.next;
		}
		for (int i = 1; i < arr.length; i++){
			Student tmp = arr[i];
			int j = i - 1;
			while (j >= 0 && arr[j].compareTo(tmp) > 0){
				arr[j + 1] = arr[j];
				j--;
			}
			arr[j + 1] = tmp;
		}
		k = 0;
		tmpNode = head.next;
		while (tmpNode != tail){
			tmpNode.student = arr[k++];
			tmpNode = tmpNode.next;
		}
	}
	
}
