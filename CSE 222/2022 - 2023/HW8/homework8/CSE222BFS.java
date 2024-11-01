package homework8;
/**
 * Class for BFS algorithm
 * @author Barış Batuhan Bolat
 */
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

public class CSE222BFS {
    private CSE222Graph graph;
    private int length = 0;
    /**
     * Constructor for CSE222BFS class
     * @param graph CSE222Graph object to be work on
     */
    public CSE222BFS(CSE222Graph graph) {
        this.graph = graph;
    }
    /**
     * This method performs a BFS on a map graph, starting from the start and exploring its neighbors until it finds the end.
     * <p>
     *  It then reconstructs the path from the end to the start and returns it if valid.
     * @return List of strings that holds coordinates of paths
     */
    public List<String> findPath() {
        // Get the size of the map from map
        int size = graph.getMap().getSize();
        
        //Calculate the start and end point of map
        int start = graph.getMap().getStartY() * size + graph.getMap().getStartX();
        int end = graph.getMap().getEndY() * size + graph.getMap().getEndX();
    
        int[] previous = new int[size * size]; // Array to store the previous node for each vertex
    
        // Initialize the previous array with -1 to indicate that no previous node is set
        for (int i = 0; i < previous.length; i++) {
            previous[i] = -1;
        }

        // Queue to perform breadth-first search
        Queue<Node> queue = new LinkedList<>(); 
        // Add the start node to the queue
        queue.offer(new Node(start)); 

        previous[start] = start;
    
        while (!queue.isEmpty()) {
            Node current = queue.poll();
    
            if (current.vertex == end) { 
                break;
            }
            
            //Calculate the coordinates of current node
            int currentX = current.vertex % size;
            int currentY = current.vertex / size;
            
            int[] newX = {currentX - 1, currentX + 1, currentX, currentX};
            int[] newY = {currentY, currentY, currentY - 1, currentY + 1};
    
            for (int i = 0; i < 4; i++) {
                // Check the validity of new coordinates
                if (newX[i] >= 0 && newX[i] < graph.getMap().getSize() && newY[i] >= 0 && newY[i] < graph.getMap().getSize() && graph.getMap().getMap()[newY[i]][newX[i]] != 1) {
                    // Calculate the vertex of the neighbor node
                    int neighborVertex = newY[i] * size + newX[i];
                    
                    //Check if the node visited (-1 is not visited)
                    if (previous[neighborVertex] == -1) {
                        queue.offer(new Node(neighborVertex));
                        previous[neighborVertex] = current.vertex;
                    }
                }
            }
        }
    
        List<String> path = new ArrayList<>();
        int current = end;
    
        // Fill the path list from end to start using the previous array
        while (current != start) {
            // Calculate coordinates from vertex index
            int x = current % size;
            int y = current / size;
            path.add(y + "," + x);
            current = previous[current];
        }
        
        // Add the start coordinate to the path
        path.add(graph.getMap().getStartY() + "," + graph.getMap().getStartX());
    
        List<String> temp = new ArrayList<>();
    
        // Reverse the path to get it from start to end
        for (int i = path.size() - 1; i >= 0; i--) {
            temp.add(path.get(i));
        }
        path = temp;
        
        // Calculate the length of the path
        length = path.size() - 1;
    
        if (path.get(0).equals(graph.getMap().getStartY() + "," + graph.getMap().getStartX())) {
            return path;
        } else {
            System.out.println("No feasible path is found");
            return null;
        }
    }
    
    /**
     * Get method for length of path
     * @return Integer
     */
    public int getLength() {
        if(length != 0){
            return length;
        }
        List<String> path = findPath();
        return path.size() - 1;
    }
}