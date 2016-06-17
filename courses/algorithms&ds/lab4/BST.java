package lab4;

import java.util.ArrayList;

public class BST {

	private TreeNode root;

	private static enum Position {
		ROOT, LEFT, RIGHT
	};

	public BST() {

	}

	public boolean containsKey(int id) {
		return get(id) != null;
	}

	public void traverse() {
		postorderTreeWalk(root);
	}

	private void postorderTreeWalk(TreeNode node) {
		if (node != null) {
			postorderTreeWalk(node.getLeft());
			postorderTreeWalk(node.getRight());
			System.out.println(node.getData().getInfo());
		}
	}

	public Student insert(int id, Student value) {

		TreeNode par = null;
		TreeNode cur = root;
		TreeNode newChild = new TreeNode(id, value);
		while (cur != null) {
			par = cur;                          //saving parent
			if (newChild.compareTo(cur) < 0) {		//choosing child place
				cur = cur.getLeft();			
			} else
				cur = cur.getRight();
		}
		if (par != null && par.getId() == id) { //saving elem on this id and returning back										
			Student prev = par.getData();
			par.setData(value);
			return prev;
		}
		newChild.setParent(par);						//adding parent for new child
		if (par == null) {
			root = newChild;
		} else if (newChild.compareTo(par) < 0) {	//choosing place for child
			par.setLeft(newChild);
		} else
			par.setRight(newChild);
		return null;
	}

	public int size() {
		if (root == null)
			return 0;
		else
			return childrenCount(root);
	}

	private int childrenCount(TreeNode x) {
		if (!x.hasLeft() && !x.hasRight()) //if leaf reached
			return 1;
		int left, right;
		if (x.hasLeft())
			left = childrenCount(x.getLeft()); //children of left node
		else
			left = 0;
		if (x.hasRight())
			right = childrenCount(x.getRight()); //of right
		else
			right = 0;
		return left + right + 1;   //left node ch + right node ch + current node
	}

	public Student get(int id) {
		return get(root, id);
	}

	private Student get(TreeNode x, int id) {
		if (x == null)			   //target does not exist
			return null;
		else if (id == x.getId())  //target reached
			return x.getData();
		if (id < x.getId()) {
			return get(x.getLeft(), id);
		} else
			return get(x.getRight(), id);
	}

	private TreeNode getTreeNode(TreeNode x, int id) { //same code as previous, returning node
		if (x == null)
			return null;
		else if (id == x.getId())
			return x;
		if (id < x.getId()) {
			return getTreeNode(x.getLeft(), id);
		} else
			return getTreeNode(x.getRight(), id);
	}

	public Student remove(int id) {
		TreeNode toDel = getTreeNode(root, id);
		if (toDel == null)  					//no elem on this key in bst
			return null;
		Student res = toDel.getData();
		remove(toDel);
		return res;
	}

	private void remove(TreeNode toDel) {

		TreeNode parent = toDel.getParent();
		if (!toDel.hasChildren()) { 						//no children
			if (toDel == root) {
				root = null;
				return;
			}
			if (parent.getLeft() == toDel) {
				parent.setLeft(null);
			} else if (parent.getRight() == toDel) {
				parent.setRight(null);
			}
		} else if (toDel.hasLeft() && !toDel.hasRight()) {	// only left child
			if (toDel == root) {
				root = root.getLeft();
				return;
			}
			if (parent.getLeft() == toDel) {
				parent.setLeft(toDel.getLeft());
			} else if (parent.getRight() == toDel) {
				parent.setRight(toDel.getLeft());
			}
		} else if (!toDel.hasLeft() && toDel.hasRight()) { //only right child
			if (toDel == root) {
				root = root.getRight();
				return;
			}
			if (parent.getLeft() == toDel) {
				parent.setLeft(toDel.getRight());
			} else if (parent.getRight() == toDel) {
				parent.setRight(toDel.getRight());
			}
		} else { 										//two children
			TreeNode x = null;
			TreeNode y;
			if (!toDel.hasLeft() || !toDel.hasRight()) { 
				y = toDel;									//we are at successor already
			} else
				y = getMinimum(toDel.getRight());			//getting successor					
				x = y.getRight();							//x - child of y
			if (x != null) {								//deleting by linking y.parent and x
				x.setParent(y.getParent());
			}
			if (!y.hasParent()) {							//deleted elem was root
				root = x;
			} else if (y == y.getParent().getLeft()) {		//if y was left child
				y.getParent().setLeft(x);
			} else											//or it was left child
				y.getParent().setRight(x);					
			if (y != toDel) { 								//interface does NOT return TreeNodes
				toDel.setData(y.getData());					//so data exchange is allowed
			}
		}
	}

	private TreeNode getMinimum(TreeNode x) {
		while (x.hasLeft()) {
			x = x.getLeft();
		}
		return x;
	}

	public int remove(int CourseNum, String ForeignLanguage) {
		ArrayList<TreeNode> removeList = new ArrayList<>();
		removeTraversal(root, removeList, CourseNum, ForeignLanguage);
		int prevSize = size();
		for (TreeNode node : removeList) {
			remove(node);
			int newSize = size();
			if (prevSize == newSize)
				throw new RuntimeException();
			prevSize = newSize;
		}
		return removeList.size();
	}

	private void removeTraversal(TreeNode node, ArrayList<TreeNode> removeList,
			int CourseNum, String ForeignLanguage) {
		if (node != null) {
			removeTraversal(node.getLeft(), removeList, CourseNum,
					ForeignLanguage);
			removeTraversal(node.getRight(), removeList, CourseNum,
					ForeignLanguage);
			if (node.getData().getCourseNum() == CourseNum
					&& node.getData().getForeignLanguage()
							.equals(ForeignLanguage)) {
				removeList.add(node);
			}
		}
	}

	public void print() {
		print(root, 0, BST.Position.ROOT);
	}

	private void print(TreeNode node, int offset, BST.Position pos) {
		for (int i = 0; i < offset; i++) {
			System.out.format("|    ");
		}
		if (pos != BST.Position.ROOT) {
			System.out.format("|---");
		}
		switch (pos) {
		case LEFT:
			System.out.format("(L)");
			break;
		case RIGHT:
			System.out.format("(R)");
			break;
		case ROOT:
			System.out.format("(RT)");
		}
		System.out.format(" %s\n", node.getShortInfo());
		for (int i = 0; i < offset + 1; i++) {
			System.out.format("|    ");
		}
		if (node.hasChildren()) {
			System.out.format("|\n");
		} else
			System.out.format("\n");
		if (node.hasLeft())
			print(node.getLeft(), offset + 1, BST.Position.LEFT);
		if (node.hasRight())
			print(node.getRight(), offset + 1, BST.Position.RIGHT);
	}

}
