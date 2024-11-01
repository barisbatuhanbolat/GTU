package homework5;

import javax.swing.JFrame;
import javax.swing.JTree;
import javax.swing.tree.DefaultMutableTreeNode;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.Stack;
import java.util.Queue;
import java.util.LinkedList;
/**
 * Class for doing HW 5 tree operations
 * @author Barış Batuhan Bolat
 */
public class HW5_Tree {
    private String[][] data = null;
    private JTree tree = null;
    private JFrame frame = null;
    private DefaultMutableTreeNode root = null;
    /**
     * Constructor that reads tree from txt file and convert it to JTree data structure.
     */
    public HW5_Tree() {
        data = readDataFromFile("homework5/tree.txt");

        root = new DefaultMutableTreeNode("Root");

        for (int i = 0; i < data.length; i++) {
            DefaultMutableTreeNode node = root;
            for (int j = 0; j < data[i].length; j++) {
                DefaultMutableTreeNode checkNode = findNode(node,data[i][j]);
                if(checkNode == null && data[i][j] != null){
                    DefaultMutableTreeNode newNode = new DefaultMutableTreeNode(data[i][j]);
                    node.add(newNode);
                    node = newNode;                    
                }
                else if(checkNode != null){
                    node = checkNode;
                }
            }
        }
        frame = new JFrame();
        tree = new JTree(root);
        for (int i = 0; i < tree.getRowCount(); i++) {
            tree.expandRow(i);
        }
        frame.add(tree);
        frame.setBounds(500, 250, 500, 480);
        frame.setVisible(false);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
    /**
     * This method changes visibility of frame
     */
    public void displayTree(){
        if(frame.isVisible()){
            frame.setVisible(false);
        }
        else{
            frame.setVisible(true);
        }
    }
    /**
     * A method that performs BFS algorithm to find an input in the tree
     * <p>
     * This method first puts all the nodes in a queue. Then it checks the queue by emptying it one by one.(Queue is used for search from begining)
     * @param target String value to be found
     */
    public void bfs(String target) {
        System.out.println("Using BFS  to find '"+target+"' int the tree...");
        Queue<DefaultMutableTreeNode> queue = treeToQueue();
        int j = 1;
        boolean found = false;
        while (!queue.isEmpty()) {
            DefaultMutableTreeNode node = queue.poll();
            System.out.print("Step "+ (j++) + " -> " + node.toString());
            if(node.toString().equals(target)){
                found = true;
                break;
            }
            System.out.print("\n");
        }
        if(found){
            System.out.println("(Found)");
        }
        else{
            System.out.println("Not found.");
        }
    }
    /**
     * A method that performs DFS algorithm to find an input in the tree
     * <p>
     * This method first puts all the nodes in a stack and reverse it because we start searhing from the last child of root. Then it checks the stack by emptying it one by one.(Stack is used for search from end)
     * @param target String value to be found
     */
    public void dfs(String target) {
        System.out.println("Using DFS  to find '"+target+"' int the tree...");
        Stack<DefaultMutableTreeNode> stack = reverseStack(treeToStack());
        int j = 1;
        boolean found = false;
        while (!stack.isEmpty()) {
            DefaultMutableTreeNode node = stack.pop();
            System.out.print("Step "+ (j++) + " -> " + node.toString());
            if(node.toString().equals(target)){
                found = true;
                break;
            }
            System.out.print("\n");
        }
        if(found){
            System.out.println("(Found)");
        }
        else{
            System.out.println("Not found.");
        }
    }
    /**
     * A method that performs DFS with Post-Order algorithm to find an input in the tree
     * <p>
     * This method first puts all the nodes in a stack. This time we dont need to reverse. Then it checks the stack by emptying it one by one.(Stack is used for search from end)
     * @param target String value to be found
     */
    public void dfspost(String target){
        System.out.println("Using Post-Order-Traverse DFS  to find '"+target+"' int the tree...");
        Stack<DefaultMutableTreeNode> stack = treeToStack();
        int j = 1;
        boolean found = false;
        while (!stack.isEmpty()) {
            DefaultMutableTreeNode node = stack.pop();
            System.out.print("Step "+ (j++) + " -> " + node.toString());
            if(node.toString().equals(target)){
                found = true;
                break;
            }
            System.out.print("\n");
        }
        if(found){
            System.out.println("(Found)");
        }
        else{
            System.out.println("Not found.");
        }
    }
    /**
     * This method moves node from one year to another with its parents.
     * @param source String array for location
     * @param destination String for destinatiton node
     */
    public void moveNode(String[] source, String destination) {
        frame.setVisible(false);
        boolean overrite = false;
        DefaultMutableTreeNode node = root;
        for (int i = 0; i < source.length; i++) {
            DefaultMutableTreeNode temp = findNode(node, source[i]);
            if (temp == null) {
                System.out.println("Cannot move because it doesn't exist in tree");
                frame.setVisible(true);
                return;
            }
            node = temp;
        }
        if(source[0].equals(destination)){
            System.out.print("Moved " + source[0]);
            for(int i = 1;i<source.length ;i++){
                System.out.print("->" + source[i]);
            }
            System.out.println("\nOverwriting existing node: " + source[source.length - 1]);
            frame.setVisible(true);
            return;
        }        
        DefaultMutableTreeNode destinationNode = findNode(root, destination);
        if (destinationNode == null) {
            destinationNode = new DefaultMutableTreeNode(destination);
            root.add(destinationNode);
        }
        DefaultMutableTreeNode destinationParent = destinationNode;
        for (int i = 1; i < source.length - 1; i++) {
            DefaultMutableTreeNode temp = findNode(destinationParent, source[i]);
            if (temp == null) {
                temp = new DefaultMutableTreeNode(source[i]);
                destinationParent.add(temp);
            }
            destinationParent = temp;
        }
        DefaultMutableTreeNode overriteNode = findNode(destinationParent, source[source.length - 1]);
        if (overriteNode != null) {
            overrite = true;
            destinationParent.remove(overriteNode);
        }
        DefaultMutableTreeNode oldParent = (DefaultMutableTreeNode) node.getParent();
        ((DefaultMutableTreeNode)node.getParent()).remove(node);
        destinationParent.add(node);

        if (oldParent.getChildCount() == 0) {
            DefaultMutableTreeNode parent = (DefaultMutableTreeNode) oldParent.getParent();
            parent.remove(oldParent);
        }
        
        System.out.print("Moved " + source[0]);
        for(int i = 1;i<source.length ;i++){
            System.out.print("->" + source[i]);
        }
        System.out.println(" to " + destination);
        if(overrite){
            System.out.println("Overwriting existing node: " + overriteNode.toString());
        }
        frame.remove(tree);
        tree = new JTree(root);
        for (int i = 0; i < tree.getRowCount(); i++) {
            tree.expandRow(i);
        }
        frame.add(tree);
        frame.setVisible(true);
    }
    /**
     * This method increases the 2D array capacity by desired rows and columns
     * @param arr String array to be increased
     * @param rowsToAdd number of rows to be increased
     * @param colsToAdd number of columns to be increased
     * @return Increased String array
     */
    public String[][] resize(String[][] arr, int rowsToAdd, int colsToAdd) {
        String[][] newArr = new String[arr.length + rowsToAdd][arr[0].length + colsToAdd];
    
        for (int i = 0; i < arr.length; i++) {
            for (int j = 0; j < arr[0].length; j++) {
                newArr[i][j] = arr[i][j];
            }
        }
    
        return newArr;
    }
    /**
     * Read some information from a .txt file and represent it as a tree structure with 2D String array
     * @param filename String variable for filepath
     * @return 2D String array to represent tree
     */
    public String[][] readDataFromFile(String filename) {
        String[][] data = null;
        try {
            Scanner scanner = new Scanner(new File(filename));

            data = new String[1][1];

            scanner = new Scanner(new File(filename));
            int i = 0;
            while (scanner.hasNextLine()) {
                data = resize(data, 1, 0);
                String line = scanner.nextLine();
                String[] parts = line.split(";");
                for (int j = 0; j < parts.length; j++) {
                    data = resize(data, 0, 1);
                    data[i][j] = parts[j];
                }
                i++;
            }
            scanner.close();
        } 
        catch (FileNotFoundException e) {
            System.out.println("File not found");
            System.exit(0);
        }
        return data;
    }      
    /**
     * This method converts tree to queue to help BFS Search algorithm
     * @return Queue with DefaultMutableTreeNode parameter
     */
    public Queue<DefaultMutableTreeNode> treeToQueue() {
        Queue<DefaultMutableTreeNode> queue = new LinkedList<DefaultMutableTreeNode>(); 
        Queue<DefaultMutableTreeNode> temp = new LinkedList<DefaultMutableTreeNode>();
        temp.offer(root); 

        while (!temp.isEmpty()) {
            DefaultMutableTreeNode node = temp.poll();
            queue.offer(node);
    
            for (int i = 0; i < node.getChildCount(); i++) {
                temp.offer((DefaultMutableTreeNode)node.getChildAt(i));
            }
        }
        return queue;
    }
    /**
     * This method converts tree to stack to help DFS Search algorithm
     * @return Stack with DefaultMutableTreeNode parameter
     */
    public Stack<DefaultMutableTreeNode> treeToStack() {
        Stack<DefaultMutableTreeNode> stack = new Stack<DefaultMutableTreeNode>(); 
        Stack<DefaultMutableTreeNode> temp = new Stack<DefaultMutableTreeNode>();
        temp.push(root);

        while (!temp.isEmpty()) {
            DefaultMutableTreeNode node = temp.pop();
            stack.push(node);
    
            for (int i = 0; i < node.getChildCount(); i++) {
                temp.push((DefaultMutableTreeNode)node.getChildAt(i));
            }
        }
        return stack;
    }
    /**
     * Method for reverse stack
     * @return Reversed Stack with DefaultMutableTreeNode parameter
     */   
    public Stack<DefaultMutableTreeNode> reverseStack(Stack<DefaultMutableTreeNode> stack){
        Stack<DefaultMutableTreeNode> reversed = new Stack<DefaultMutableTreeNode>();
        while(!stack.isEmpty()){
            reversed.push(stack.pop());
        }
        return reversed;

    }
    /**
     * Simple search algorithm to find target node under given parent node
     * @param parent DefaultMutableTreeNode variable to represent a node for parent
     * @param nodeName String variable to target node
     * @return null if node isn't found , node otherwise
     */
    public DefaultMutableTreeNode findNode(DefaultMutableTreeNode parent, String nodeName) {
        for (int i = 0; i < parent.getChildCount(); i++) {
            DefaultMutableTreeNode child = (DefaultMutableTreeNode) parent.getChildAt(i);
            if (child.toString().equals(nodeName)) {
                return child;
            }
        }
        return null;
    }
}