package homework8;
/**
 * Class for Dijkstra's algorithm
 * @author Barış Batuhan Bolat 
 */
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

public class CSE222Dijkstra {
    private CSE222Graph graph = null;
    private int length = 0;
    /**
     * Constructor for CSE222Dijkstra
     * @param graph CSE222Graph object to be work on
     */
    public CSE222Dijkstra(CSE222Graph graph) {
        this.graph = graph;
    }
    /**
     * This given method is a Dijkstra's algorithm implementation to find a feasible path in a graph based on the calculated edge weights. 
     * @return List of strings that holds coordinates of paths
    */
    public List<String> findPath() {
        // Get adjacency list and size of map from the graph.
        List<List<Node>> adjacencyList = graph.getAdjList();
        int size = graph.getMap().getSize();

        // Initialize distances to maximum value for all vertices
        int[] distances = new int[size * size];    
        for (int i = 0; i < size * size; i++) {
            distances[i] = Integer.MAX_VALUE;
        }
        //Calculate the start and end point of map
        int start = graph.getMap().getStartY() * size + graph.getMap().getStartX();
        int end = graph.getMap().getEndY() * size + graph.getMap().getEndX();
        //In some maps, since the starting vertex is larger than the ending vertex, it creates errors in the wayfinding algorithm. 
        //To avoid this situation, I swapped the start and end vertex.
        if(start > end){
            int temp = start;
            start = end;
            end = temp;
        }

        distances[start] = 0;
        
        // Queue to perform Dijskstra Algorithm
        Queue<Node> queue = new LinkedList<>();
        Node startNode = new Node(start);
        // Add start node to the queue
        queue.offer(startNode);
        
        while (!queue.isEmpty()) {
            Node current = queue.poll();
            if (current.isVisited) {
                continue;
            }
            
            current.isVisited = true;
    
            if (current.vertex == end) {
                break;
            }
    
            // Iterate through neighbors of the current node
            for (Node neighbor : adjacencyList.get(current.vertex)) {
                // Calculate the total distance by using the edge weight between the current node and its neighbor
                int distance = distances[current.vertex] + Math.abs((current.vertex % size) - (neighbor.vertex % size)) + 
                                                           Math.abs((current.vertex / size) - (neighbor.vertex / size));
                if (distance < distances[neighbor.vertex]) {
                    distances[neighbor.vertex] = distance; 
                    queue.offer(neighbor);
                }
            }
        }
        
        List<String> path = new ArrayList<>();
        int current = end;
        
        // Fill the path list from end to start using the distances of vertexs
        while (current != start) {
            // Calculate coordinates from vertex index
            int x = current % size;
            int y = current / size;
            path.add(y + "," + x);
            
            int minDistance = Integer.MAX_VALUE;
            int next = current;
            
            // Find the next node with the minimum distance
            for (Node neighbor : adjacencyList.get(current)) {
                int distance = distances[neighbor.vertex] + Math.abs((current % size) - (neighbor.vertex % size)) + 
                                                            Math.abs((current / size) - (neighbor.vertex / size));
                if (distance < minDistance) {
                    minDistance = distance;
                    next = neighbor.vertex;
                }
            }            
            current = next;
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