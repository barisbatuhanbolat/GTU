package homework8;
/**
 * Node Class
 * @author Barış Batuhan Bolat
 */
public class Node {
    public int vertex;
    public boolean isVisited;
    
    public Node(int vertex) {
        this.vertex = vertex;
        this.isVisited = false;
    }
}