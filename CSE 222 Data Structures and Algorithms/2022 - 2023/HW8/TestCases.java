import java.util.List;

import homework8.*;

public class TestCases implements Runnable {

    private  String FileName;
    private int X_SIZE;
    private int Y_SIZE;

    public TestCases(String FileName, int X_SIZE, int Y_SIZE) {
        this.FileName = FileName;
        this.X_SIZE = X_SIZE;
    	this.Y_SIZE = Y_SIZE;
    }
    
    public void test(){
    	System.out.println("\n\n*******************\nMap is " + this.FileName + " with X_SIZE " + this.X_SIZE + " and Y_SIZE " + this.Y_SIZE + "\n********************\n");
        CSE222Map Map = new CSE222Map (this.FileName, this.X_SIZE, this.Y_SIZE);
        this.FileName = this.FileName.replaceAll(".txt", "");
        CSE222Graph Graph = new CSE222Graph (Map);
        CSE222Dijkstra Dijkstra = new CSE222Dijkstra (Graph);
        CSE222BFS BFS= new CSE222BFS (Graph);

        List<String> BFSPath = BFS.findPath();
        Map.convertPNG(this.FileName);
        Map.drawLine(BFSPath,this.FileName+"BFS");
        Map.writePath(BFSPath,this.FileName+"BFS");

        List<String> DijkstraPath = Dijkstra.findPath();
        Map.drawLine(DijkstraPath,this.FileName+"Dijkstra");
        Map.writePath(DijkstraPath,this.FileName+"Dijkstra");
        System.out.println("BFS Path Length(" + this.FileName + "): "+ BFS.getLength());
        System.out.println("Dijkstra Path Length(" + this.FileName + "): "+ Dijkstra.getLength());
    }

    @Override
    public void run() {
        test();
    }
}

