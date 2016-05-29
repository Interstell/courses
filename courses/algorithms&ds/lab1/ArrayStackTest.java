package lists;

import java.util.Scanner;
import java.util.InputMismatchException;

public class ArrayStackTest {
	
	 public static void main(String[] args) {
		ArrayStack a = new ArrayStack(2);
		
		try{
			System.out.println("Autodemonstration:");
			Thread.sleep(500);
			a.push(5);
			System.out.println("Pushed: "+5);
			Thread.sleep(500);
			a.push(10);
			System.out.println("Pushed: "+10);
			Thread.sleep(500);
			a.push(15);
			System.out.println("Pushed: "+15);
			Thread.sleep(500);
			System.out.println("Stack: ");
			a.print();
			Thread.sleep(500);
			System.out.println("Popped: "+ a.pop());
			Thread.sleep(500);
			System.out.println("Popped: "+ a.pop());
			Thread.sleep(500);
			System.out.println("Stack: ");
			a.print();
			System.out.println();
			a.pop();
			Thread.sleep(3000);
		}
		catch(java.lang.InterruptedException e){}
		
		System.out.println("Manual test:");
		Scanner scan = new Scanner(System.in);
		System.out.println("\"push %double%\" for push, \"pop\" for pop");
		while (true){
			String cmd = new String();
			cmd = scan.next();
			if (cmd.equalsIgnoreCase("push")){
				double num;
				try{
					num = scan.nextDouble();
					a.push(num);
					System.out.println("\""+num+"\" was pushed.");
				}
				catch(InputMismatchException e){
					System.out.println("Wrong input type.");
				}
			}
			else if (cmd.equalsIgnoreCase("pop")){
				System.out.println("\""+a.pop()+"\" was popped.");
			}
			else if (cmd.equalsIgnoreCase("stop")){
				a.print();
				break;
			}
		}
	}

}
