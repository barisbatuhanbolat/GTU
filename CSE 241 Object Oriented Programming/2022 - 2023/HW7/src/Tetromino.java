
/**
* This is a Tetromino class to represent Tetris pieces.
*   @author Barış Batuhan Bolat
*/
public class Tetromino{
    private char shape;
    private int[][] tetroMain = new int[4][4];
    
    /**
     * Default constructor for Tetromino class.
     * <p>
     * This constructor calls other constructor with null shape.
     */
    public Tetromino(){
        this('\0');
    }
    /**
     * Constructor for Tetromino class.
     * @param shapeT Char variable for Tetromino shape
     */    
    public Tetromino(char shapeT){
        shape = shapeT;
        if(shape == '\0'){
            ;
        }
        else if(shape  == 'I'){
            tetroMain[3][0] = 1;
            tetroMain[3][1] = 1;
            tetroMain[3][2] = 1;
            tetroMain[3][3] = 1;
        }
        else if(shape  == 'O'){
            tetroMain[1][1] = 1;
            tetroMain[1][2] = 1;
            tetroMain[2][1] = 1;
            tetroMain[2][2] = 1;
        }
        else if(shape  == 'L'){
            tetroMain[0][1] = 1;
            tetroMain[1][1] = 1;
            tetroMain[2][1] = 1;
            tetroMain[2][2] = 1;
        }
        else if(shape  == 'S'){
            tetroMain[1][1] = 1;
            tetroMain[1][2] = 1;
            tetroMain[2][0] = 1;
            tetroMain[2][1] = 1;
        }
        else if(shape  == 'Z'){
            tetroMain[1][0] = 1;
            tetroMain[1][1] = 1;
            tetroMain[2][1] = 1;
            tetroMain[2][2] = 1;
        }

        else if(shape  == 'T'){
            tetroMain[1][0] = 1;
            tetroMain[1][1] = 1;
            tetroMain[1][2] = 1;
            tetroMain[2][1] = 1;
        }                                 
        else if(shape  == 'J'){
            tetroMain[0][1] = 1;
            tetroMain[1][1] = 1;
            tetroMain[2][1] = 1;
            tetroMain[2][0] = 1;
        } 
    }
    /**
     * Copy Constructor for Tetromino class.
     * <p>
     * This constructor calls other constructor with Tetromino shape to be copied.
     * @param other Tetromino variable to copied
     */    
    public Tetromino(Tetromino other){
        this(other.getShape());
    }
    /**
     * <p>
     * This method prints the Tetromino to the screen.
     */
    public void print(){
        for(int[] x : tetroMain){
            for(int y : x){
               if(y == 0){
                System.out.print(" ");
               }
               else if(y == 1){
                System.out.print("X");
               }
            }
            System.out.println();
        }
    }
    /**
     * <p>
     * This method rotates the Tetromino according the parameter.
     * @param rotation  0 for left and 1 for right rotation
     * @return 2D integer array represent Tetromino
     */    
    public int[][] rotate(int rotation){

        if(rotation == 0){
            for (int x = 0; x < 2; x++) {
                for (int y = x; y < 4 - x - 1; y++) {

                    int temp = tetroMain[x][y];

                    tetroMain[x][y] = tetroMain[y][3 - x];

                    tetroMain[y][3 - x] = tetroMain[3 - x][3 - y];

                    tetroMain[3 - x][3 - y] = tetroMain[3 - y][x];

                    tetroMain[3 - y][x] = temp;
                }
            }
        }
        else if(rotation == 1){
            int i = 0;
            while(i < 3){
                for (int x = 0; x < 2; x++) {
                    for (int y = x; y < 4 - x - 1; y++) {

                        int temp = tetroMain[x][y];

                        tetroMain[x][y] = tetroMain[y][3 - x];

                        tetroMain[y][3 - x] = tetroMain[3 - x][3 - y];

                        tetroMain[3 - x][3 - y] = tetroMain[3 - y][x];

                        tetroMain[3 - y][x] = temp;
                    }
                }
                i++;
            }
        }
        return tetroMain;

    }
    /**
     * <p>
     * This get method returns Tetromino.
     * @return 2D integer array represent Tetromino
     */
    public int[][] getTetro(){
        return tetroMain;
    }
    /**
     * <p>
     * This get method returns Tetromino shape.
     * @return char variable represent Tetromino shape
     */    
    public char getShape(){
        return shape;
    }    
}
