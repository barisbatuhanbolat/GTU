import java.awt.Color;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.Dimension;
import java.awt.GridLayout;  
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import java.awt.Font;
import java.util.Random;

enum Tetromino {
    I,
    O,
    L,
    S,
    Z,
    T,
    J
}
/**
 * This is a GUI Tetris class represent Tetris board with animations
 * @author Barış Batuhan Bolat
 */
public class Tetris extends JFrame {

	private Color[] tetrominoColors = {
		Color.cyan, Color.blue, Color.orange, Color.yellow, Color.green, Color.pink, Color.red
	};
	private Tetromino[] Tetrominos = {
		Tetromino.I,Tetromino.O,Tetromino.L,Tetromino.S,Tetromino.Z,Tetromino.T,Tetromino.J
	};
	
    private int[][] board;
    private int[][] board_cpy;
    private int[][] tetro;
    private JButton[][] buttons;
	private JPanel panel;
    private int x,y; //Coordinates    
    private boolean isGameOver = false;
	private  boolean isStart = true;
	private Color color;
	private Random rand = new Random(System.currentTimeMillis());;
    /**
     * Default constructor for Tetromino class.
     * <p>
     * This constructor creates board and tetro and creates JFrame for window with full buttons.
     */
    public Tetris(){
        JFrame f = new JFrame("Tetris");
		f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		f.setSize(new Dimension(500, 800));

		buttons = new JButton[23][12];
		panel = new JPanel();
		panel.setLayout(new GridLayout(23, 12));
		board = new int[23][12];
        board_cpy = new int[23][12];
        tetro = new int[4][4];

		for (int i = 0; i <23; i++) {
			for (int j = 0; j <12; j++) {
				if(i == 0 || i == 21 || i == 22 || j == 0 || j == 11){
					if((i == 22 && j == 5) || (i == 22 && j == 6)|| (i == 22 && j == 7)|| (i == 22 && j == 4)){
						board[i][j] = 3;
					}
					else{
						board[i][j] = 2;
					}
				}
				else{
					board[i][j] = 0;

				}
			}
		}
		backup();
		for(int i = 0;i<23;i++){
			for(int j = 0;j<12;j++){
				buttons[i][j] = new JButton();
				if(i == 0 || i == 21 || i == 22 || j == 0 || j == 11){
					if((i == 22 && j == 5) || (i == 22 && j == 6)|| (i == 22 && j == 7)|| (i == 22 && j == 4)){
						buttons[i][j].setBackground(Color.RED);
						buttons[i][j].setEnabled(true);
						buttons[i][j].setFont(new Font("Arial", Font.PLAIN, 10)); 
						buttons[i][j].setFocusable(false);
					}
					else{
						buttons[i][j].setBackground(Color.WHITE);
						buttons[i][j].setEnabled(false);
					}
				}
				else{
					buttons[i][j].setBackground(Color.BLACK);
					buttons[i][j].setEnabled(false);

				}
				panel.add(buttons[i][j]);
			}
		}
		buttons[22][4].setText("R");
		buttons[22][5].setText("S");
		buttons[22][6].setText("E");
		buttons[22][7].setText("R");
		f.add(panel);
		f.setVisible(true);;
		buttons[22][5].addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				Tetris.this.isStart = true;

			}
		});
		buttons[22][6].addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				System.exit(0);

			}
		});	
		buttons[22][4].addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				reset();
			}
		});
		buttons[22][7].addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				reset();
			}
		});				
		f.addKeyListener(new KeyListener() {
			public void keyTyped(KeyEvent e) {
			}
			
			public void keyPressed(KeyEvent e) {
				switch (e.getKeyCode()) {

				case KeyEvent.VK_LEFT:
					if(!isFilled(x-1, y))
						moveVH(x-1, y);
					break;
				case KeyEvent.VK_RIGHT:
					if(!isFilled(x+1, y))
						moveVH(x+1, y);
					break;
				case KeyEvent.VK_UP:
					rotate(0);
					break;
				case KeyEvent.VK_DOWN:
					rotate(1);
					break;
				}
			}
			public void keyReleased(KeyEvent e) {
			}
		});
	}
	/**
	 * This method resets the whole board
	 */
	public void reset(){
		for(int i = 1;i<21;i++){
			for(int j = 1;j<11;j++){
				board[i][j] = 0;
			}
		}
		for(int i = 0;i<4;i++){
			for(int j = 0;j<4;j++){
				tetro[i][j] = 0;
			}
		}
		backup();
		add();
	}
	/**
	 * This method rotates the tetromino according to the fullness
	 * @param rotation Integer variable for rotatiton
	 */
	public void rotate(int rotation){
		int[][] temp1 = new int[4][4];
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				temp1[i][j] = tetro[i][j]; 
			}
		}
		if(rotation == 0){
            for (int x = 0; x < 2; x++) {
                for (int y = x; y < 4 - x - 1; y++) {

                    int temp = tetro[x][y];

                    tetro[x][y] = tetro[y][3 - x];

                    tetro[y][3 - x] = tetro[3 - x][3 - y];

                    tetro[3 - x][3 - y] = tetro[3 - y][x];

                    tetro[3 - y][x] = temp;
                }
            }
        }
        else if(rotation == 1){
            int i = 0;
            while(i < 3){
                for (int x = 0; x < 2; x++) {
                    for (int y = x; y < 4 - x - 1; y++) {

                        int temp = tetro[x][y];

                        tetro[x][y] = tetro[y][3 - x];

                        tetro[y][3 - x] = tetro[3 - x][3 - y];

                        tetro[3 - x][3 - y] = tetro[3 - y][x];

                        tetro[3 - y][x] = temp;
                    }
                }
                i++;
            }
        }
		if (isFilled(x, y)) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					tetro[i][j] = temp1[i][j];
				}
			}
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				board[y + i][x + j] -= temp1[i][j];
				board[y + i][x + j] += tetro[i][j];
			}
		}		
	}
	/**
	 * This method starts the program after boards creation
	 */
	public void init(){
		while(isGameOver == false){
			clearRows();
			add();
			animate();
		}
	}
	/**
	 * This method deletes specified row(FUlled row)
	 * @param row Integer variable for represent row
	 */
	public void deleteRow(int row) {
		for (int j = row-1; j > 0; j--) {
			for (int i = 1; i < 21; i++) {
				board[i][j+1] = board[i][j];
			}
		}
	}	
	/**
	 * This method clears the full rows with help of deleteRow method
	 */
	public void clearRows() {
		boolean gap;
		
		for (int j = 10; j > 0; j--) {
			gap = false;
			for (int i = 1; i < 21; i++) {
				if (board[i][j] == 0) {
					gap = true;
					break;
				}
			}

			if (!gap) {
				deleteRow(j);
				j += 1;
			}
		}	
	}
	/**
	 * This methods animates the tetromino on board according to fullness
	 */
	public void animate(){
		
		while(isGameOver == false){
			try {
				Thread.sleep(200);
			} 
			catch (InterruptedException e) {
				Thread.currentThread().interrupt();
			}
            if (!isFilled(x, y + 1)) {
				moveVH(x, y + 1);

			}
			else {
                backup();
				return;
			}
			repaint();
        }
	}
	/**
	 * This method checks the next piece on the board for fullness
	 * @param newX X axis variable to be moved
	 * @param newY Y axis variable to be moved
	 * @return boolean variable for fullness
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
	 * This method adds the random tetromino on board
	 */
	public void add(){
        x = 4;
		y = 0;
		color = tetrominoColors[rand.nextInt(7)];
		Tetromino shape = Tetrominos[rand.nextInt(7)];
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				tetro[i][j] = 0;
			}
		}
        if(shape  == Tetromino.I){
            tetro[3][0] = 1;
            tetro[3][1] = 1;
            tetro[3][2] = 1;
            tetro[3][3] = 1;
        }
        else if(shape  == Tetromino.O){
            tetro[1][1] = 1;
            tetro[1][2] = 1;
            tetro[2][1] = 1;
            tetro[2][2] = 1;
        }
        else if(shape  == Tetromino.L){
            tetro[0][1] = 1;
            tetro[1][1] = 1;
            tetro[2][1] = 1;
            tetro[2][2] = 1;
        }
        else if(shape  == Tetromino.S){
            tetro[1][1] = 1;
            tetro[1][2] = 1;
            tetro[2][0] = 1;
            tetro[2][1] = 1;
        }
        else if(shape  == Tetromino.Z){
            tetro[1][0] = 1;
            tetro[1][1] = 1;
            tetro[2][1] = 1;
            tetro[2][2] = 1;
        }

        else if(shape  == Tetromino.T){
            tetro[1][0] = 1;
            tetro[1][1] = 1;
            tetro[1][2] = 1;
            tetro[2][1] = 1;
        }                                 
        else if(shape  ==Tetromino.J){
            tetro[0][1] = 1;
            tetro[1][1] = 1;
            tetro[2][1] = 1;
            tetro[2][0] = 1;
        } 
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
	 * This method copies the board for backup
	 */
	public void backup() {
		for (int i = 0; i < 23; i++) {
			for (int j = 0; j < 12; j++) {
				board_cpy[i][j] = board[i][j];
			}
		}
	}
	/**
	 * This method paints the buttons on window accordng to the boards
	 */
	public void repaint(){
		for(int i = 0;i<23;i++){
			for(int j = 0;j<12;j++){
				if(board[i][j] == 0){
					buttons[i][j].setBackground(Color.BLACK);
				}
				else if(board[i][j] == 1){
					buttons[i][j].setBackground(color);
				}
				else if(board[i][j] == 2){
					buttons[i][j].setBackground(Color.WHITE);
				}
				else if(board[i][j] == 3){
					buttons[i][j].setBackground(Color.RED);
				}				
			}
		}
		panel.revalidate();
		panel.repaint();
	}
	/**
	 * This method moves the tetromino on board according the given parameters
	 * @param newX X axis variable to be moved
	 * @param newY Y axis variable to be moved
	 */
	public void moveVH(int newX, int newY) {
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
	

	public static void main(String[] args) {
		Tetris game  = new Tetris();
		game.init();
	}
}