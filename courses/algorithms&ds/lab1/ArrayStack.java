package lists;

import java.util.Arrays;


public class ArrayStack {
	
	private double[] stack;
	private int top;
	
	public ArrayStack(){
		stack = new double[20];
		top = 0;
	}
	
	public ArrayStack(int capacity){
		stack = new double[capacity];
		top = 0;
	}
	
	public void push (double el){
		if (top==stack.length) {
			stretch();
		}
		stack[top++]=el;
	}
	
	public double pop(){
		return (isEmpty())?Double.NaN:stack[--top];
	}
	
	private boolean isEmpty(){
		return top == 0;
	}
	
	private void stretch(){
		stack = Arrays.copyOf(stack, stack.length+1);
	}
	
	public void print(){
		System.out.print((top > 0)?"[":"[]");
		for (int i = 0; i < top; i++){
			if (i == top - 1){
				System.out.print(stack[i]+"]");
			}
			else System.out.print(stack[i]+", ");
		}
		System.out.println();
	}
}
