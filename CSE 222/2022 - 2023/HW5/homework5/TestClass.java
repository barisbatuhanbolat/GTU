package homework5;
import java.util.Scanner;

public class TestClass {
    public static void main(String args[]){
        HW5_Tree tree = new HW5_Tree();
        int choice = 0;
        Scanner input  = new Scanner(System.in);
        String target = new String();
        String [] source = new String[0];
        do{
            try{
                System.out.println("----------MENU----------");
                System.out.println("0 - Reset Tree");
                System.out.println("1 - Show/Hide Tree");
                System.out.println("2 - BFS Algorithm");
                System.out.println("3 - DFS Algorithm");
                System.out.println("4 - Post-Order-Traversal DFS Algorithm");
                System.out.println("5 - Move Node");
                System.out.println("6 - Exit");
                System.out.print("Choice : ");
                choice = input.nextInt();
                
                switch(choice){
                    case 0:
                        tree = new HW5_Tree();
                        break;
                    case 1:
                        tree.displayTree();
                        break;
                    case 2:
                        System.out.print("Enter target to be found: ");
                        target = input.next();
                        tree.bfs(target);
                        break;
                    case 3:
                        System.out.print("Enter target to be found: ");
                        target = input.next();
                        tree.dfs(target);
                        break;
                    case 4:
                        System.out.print("Enter target to be found: ");
                        target = input.next();
                        tree.dfspost(target);
                        break;
                    case 5:
                        source = new String[0];
                        while(true){
                            System.out.print("Enter source(-1 for stop): ");
                            String temp = input.next();
                            if(temp.equals("-1")){
                                break;
                            }
                            String[] newArray = new String[source.length + 1];
                            for (int j = 0; j <source.length; j++) {
                                newArray[j] = source[j];
                            }
                            newArray[source.length] = temp;
                            source = newArray;
                        }
                        System.out.print("Enter destination year: ");
                        target = input.next();
                        tree.moveNode(source,target);
                        break;
                    case 6:
                        System.out.println("Exiting...");
                        System.exit(0);
                        break;                    
                    default:
                        System.out.println("Wrong Choice. Try Again.");
                        break;
                }
            }catch(Exception e){
                System.out.println("Wrong Choice. Try Again.");
                input.nextLine();
            }
        }while(choice != 6);
        input.close();
    }
}
