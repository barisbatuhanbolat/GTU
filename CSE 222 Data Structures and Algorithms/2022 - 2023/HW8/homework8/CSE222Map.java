package homework8;
/**
 * Map class
 * @author Barış Batuhan Bolat
 */
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

import javax.imageio.ImageIO;
import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;

public class CSE222Map {
    private int[][] map;
    private int startX;
    private int startY;
    private int endX;
    private int endY;
    private int size;
    /**
     * Constructor for CSE222Map.
     * <p>
     * Reads the txt file row by row and convert it to 2D matrix
     * @param filename String for the name of the txt file to be read and convert into map 
     * @param sizeX Integer for column size of map
     * @param sizeY Integer for row size of map
     */
    public CSE222Map(String filename,int sizeX,int sizeY) {
        try {
            Scanner reader = new Scanner(new File(filename));
            //Reading first two rows that holds starting and ending points of map
            String[] startCoords = reader.nextLine().split(",");
            startY = Integer.parseInt(startCoords[0]);
            startX = Integer.parseInt(startCoords[1]);

            String[] endCoords = reader.nextLine().split(",");
            endY = Integer.parseInt(endCoords[0]);
            endX = Integer.parseInt(endCoords[1]);
            

            List<String> lines = new ArrayList<>();
            String line;
            while (reader.hasNextLine() && (line = reader.nextLine()) != null) {
                lines.add(line);
            }
            
            //And rest of the txt file holds map 
            size = (sizeX <= lines.size()) ? lines.size() : sizeX;
            map = new int[size][size];

            for (int i = 0; i < size; i++) {
                String[] values = lines.get(i).split(",");
                for (int j = 0; j < size; j++) {
                    map[i][j] = Integer.parseInt(values[j].replaceAll("-1", "1"));
                }
            }

            reader.close();
        }catch (FileNotFoundException e) {
            System.out.println("File not found");
            System.exit(0);
        }
    }
    /**
     * This method converts the map as 2D Array to png file
     * @param filename String for the name of png file to be create
     */
    public void convertPNG(String filename) {
        try {
            // Create the folder if it doesn't exist
            File folder = new File("Maps");
            if (!folder.exists()) {
                boolean created = folder.mkdirs();
                if (!created) {
                    return;
                }
            }

            BufferedImage image = new BufferedImage(size, size, BufferedImage.TYPE_INT_RGB);
            // Roads colored by white and walls colored by gray
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    if (map[i][j] == 1) {
                        image.setRGB(j, i, Color.GRAY.getRGB());
                    } 
                    else {
                        image.setRGB(j, i, Color.WHITE.getRGB());
                    }
                }
            }

            // Save the image to the folder
            ImageIO.write(image, "PNG", new File("Maps" + "/" + filename + ".png"));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * Drawing a line for coordinates
     * @param path List of coordinates of the feasible path
     * @param filename String for the name of the png file to draw a line
     */
    public void drawLine(List<String> path,String filename) {
        if (path != null) {
            try {
                BufferedImage image = null;
                // Detecting maps kind for naming
                if (filename.contains("BFS")) {
                    image = ImageIO.read(new File("Maps/" + filename.replaceAll("BFS", "") + ".png"));
                }
                if (filename.contains("Dijkstra")) {
                    image = ImageIO.read(new File("Maps/" + filename.replaceAll("Dijkstra", "") + ".png"));
                }

                // Create the folder if it doesn't exist
                File folder = new File("Maps_with_paths");
                if (!folder.exists()) {
                    boolean created = folder.mkdirs();
                    if (!created) {
                        return;
                    }
                }

                // Marking the coordinates given in the path on the PNG file
                Graphics2D g2d = image.createGraphics();
                g2d.setColor(Color.RED);
                for (String coordinate : path) {
                    String[] coordinates = coordinate.split(",");
                    int y = Integer.parseInt(coordinates[0]);
                    int x = Integer.parseInt(coordinates[1]);
                    g2d.drawLine(x, y, x, y);
                }
                g2d.dispose();

                // Save the image to the folder
                ImageIO.write(image, "PNG", new File("Maps_with_paths" + "/" + filename + "_with_path.png"));
            } catch (IOException e) {
                System.out.println("File not found.");
            }
        } else {
            System.out.println("Path is null");
        }
    }
    /**
     * This method writes the list of coordinates of feasible path to a txt file
     * @param path List that contains coordinates of feasible path 
     * @param filename String for the name of the txt file that holds coordinates
     */
    public void writePath(List<String> path,String filename) {
        if(path != null){    
            File folder = new File("Paths");
            if (!folder.exists()) {
                boolean created = folder.mkdirs();
                if (!created) {
                    return;
                }
            }
            File file = new File("Paths", filename + "_path.txt");
            try {
                boolean created = file.createNewFile();
                if (!created) {
                    System.out.println("Failed to create the file.");
                } 
                else {
                    FileWriter out = new FileWriter(file);
                    for (String coordinate : path) {
                        out.write(coordinate + "\n");
                    }
                    out.close();
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        else{
            System.out.println("Path is null");
        }
    }

    /**
     * Get method for map as 2d array
     * @return 2D int arrray that holds map
     */
    public int[][] getMap() {
        return map;
    }
    /**
     * Get method for start column index of map
     * @return Integer
     */
    public int getStartX() {
        return startX;
    }
    /**
     * Get method for start row index of map
     * @return Integer
     */
    public int getStartY() {
        return startY;
    }
    /**
     * Get method for end column index of map
     * @return Integer
     */
    public int getEndX() {
        return endX;
    }
    /**
     * Get method for end row index of map
     * @return Integer
     */
    public int getEndY() {
        return endY;
    }
    /**
     * Get method for size of map
     * @return Integer
     */
    public int getSize() {
        return size;
    }

}