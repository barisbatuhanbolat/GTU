import java.util.Random;
/**
 * This is a Tetris class represent Tetris board with animations
 * @author Barış Batuhan Bolat
 */
public class Tetris {
    private int[][] board;
    private int[][] board_cpy;
    private int[][] tetro;

    private int x,y; //Coordinates    
    private boolean isGameOver;
    private int width;
    private int height;
    private Tetromino m;
    
    /**
     * Default constructor for Tetromino class.
     * <p>
     * This constructor calls other constructor with no height and no width.
     */
    public Tetris(){
        this(0,0);
    }
    /**
     * Constructor for Tetris class
     * @param heightT integer variable for height of the board
     * @param widthT integer variable for width of the board
     */
    public Tetris(int heightT,int widthT){
        height = heightT;
        width = widthT;
        board = new int[height][width];
        board_cpy = new int[height][width];
        tetro = new int[4][4];

		for (int i = 0; i <= height - 2; i++) {
			for (int j = 0; j <= width - 2; j++) {
				if ((i == 0)||(j == 0) || (j == width - 2) || (i == width- 2)) {
					board[i][j] = 2;
					
				} else {
					board[i][j] = 0;
				}
			}
		}
        backup();
        isGameOver = false;
    }
    /**
     * Copy Constructor for Tetris class.
     * <p>
     * This constructor calls other constructor with Tetris shape to be copied.
     * @param other Tetris variable to copied
     */      
    public Tetris(Tetris other){
        this(other.getHeight(),other.getWidth());
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				board[i][j] = other.board[i][j];
			}
		}
        backup();
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				tetro[i][j] = other.tetro[i][j];
			}
		}
        isGameOver = other.isGameOver;
    }
    /**
     * This method copies the actual board for backup
     */
	public void backup() {
		for (int i = 0; i < height - 1; i++) {
			for (int j = 0; j < width - 1; j++) {
				board_cpy[i][j] = board[i][j];
			}
		}
	}
    /**
     * This get method returns height of the board
     * @return height of the board
     */
	public int getHeight(){
        return height;
    }
    /**
     * This get method returns width of the board
     * @return width of the board
     */    
    public int getWidth(){
        return width;
    }
    /**
     * This method adds a new tetromino to the board
     * @param newT Tetromino variable to be add
     */
    public void add(Tetromino newT){
        x = width/2-1;
		y = 0;
		m = newT;
		tetro = m.getTetro();
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				board[i+y][x + j] = board_cpy[y+i+1][x + j] + tetro[i][j];
				if (board[y+i][x + j] > 1) {
					isGameOver = true;
				}
			}
		}
    }
    /**
     * This method moves the Tetromino in the board according to the given parameters
     * @param newX integer variable to represent new x axis movement
     * @param newY integer variable to represent new y axis movement
     */
	public void move(int newX, int newY) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				board[y + i][x + j] -= tetro[i][j];
			}
		}
		x = newX;
		y = newY;

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				board[y + i][x + j] += tetro[i][j];
			}
		}

	}
    /**
     * This method controls the next piece for fullness
     * @param newX integer variable to represent new x axis movement
     * @param newY integer variable to represent new y axis movement
     * @return boolean variable to represent fullness
     */
	public boolean isFilled(int newX, int newY) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
                boolean bval;
                if (tetro[i][j] >= 1)
                    bval = true;
                else
                    bval = false ;
				if (bval && board_cpy[newY + i][newX + j] != 0) {
					return true;
				}
			}
		}
		return false;
	}

    /**
     * This method animates the Tetromino on board.
     * <p>
     * This method randomly moves the Tetromino in x axis at first and starts moving downward accordingly fullness
     */
    public void animate(){
        Random rand = new Random();
        int mCount = rand.nextInt(width);
        if(!isFilled(mCount,1)){
            move(mCount,1);
        }
        int[][] temp = new int[4][4];
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                temp[i][j] = tetro[i][j]; 
            }
        }
        
        int rCount = rand.nextInt(4);
        for(int i=0;i<rCount;i++){
            tetro = m.rotate(rand.nextInt(2));
        }
        if (isFilled(x, y)) {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    tetro[i][j] = temp[i][j];
                }
            }
        }
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                board[y + i][x + j] -= temp[i][j]; //remove block data before rotation.
                board[y + i][x + j] += tetro[i][j]; //add new block data after rotation.
            }
        }
        draw();
        while(isGameOver == false){
            //System.out.println(isFilled(x, y+1));
            if (!isFilled(x, y + 1)) {
				move(x, y + 1);
			}
			else {
                backup();
				draw();
				return;
			}
            draw();
        }
    }
    /**
     * This method prints the board to screen 
     */
    public void draw(){
        try {
            Thread.sleep(50);
        } 
        catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
		//Clear screen
		System.out.print("\033[H\033[2J");
        for(int[] x : board){
            for(int y : x){
                if(y == 0){
                System.out.print(" ");
               }
               else if(y == 1){
                System.out.print("X");
               }
               else if(y == 2){
                System.out.print("*");
               }
            }
            System.out.println();
        }        
    }   


}
