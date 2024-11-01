package homework8;
/**
 * Graph class
 * @author Barış Batuhan Bolat
 */
import java.util.ArrayList;
import java.util.List;

public class CSE222Graph {
    private CSE222Map map;
    private List<List<Node>> adjList;
    /**
     * Constructor for CSE222Graph
     * <p>
     * Creating adjecency list from map
     * @param cse222Map CSE222Map object to be converted into graph
     */
    public CSE222Graph(CSE222Map cse222Map) {
        this.map = cse222Map;
        this.adjList = new ArrayList<>();

        int[][] mapArr = map.getMap();
        int size = map.getSize();
    
        for (int i = 0; i < size * size; i++) {
            adjList.add(new ArrayList<>());
        }
    
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (mapArr[i][j] == 1) {
                    continue;
                }
                
                int vertex = i * size + j;
    
                for (int dy = -1; dy <= 1; dy++) {
                    for (int dx = -1; dx <= 1; dx++) {
                        if (dy == 0 && dx == 0) {
                            continue;
                        }
    
                        int nx = j + dx;
                        int ny = i + dy;
    
                        if (nx >= 0 && nx < size && ny >= 0 && ny < size && mapArr[ny][nx] != 1) {
                            int neighbor = ny * size + nx;
                            adjList.get(vertex).add(new Node(neighbor));
                        }
                    }
                }
            }
        }
    }
    /**
     * Get method for map
     * @return CSE222Map object 
     */
    public CSE222Map getMap(){
        return map;
    }
    /**
     * Get method for adjecency list
     * @return List of lists 
     */
    public List<List<Node>> getAdjList(){
        return adjList;
    }
}