import java.awt.Color;
import java.awt.Graphics;
import java.awt.Point;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.util.ArrayList;
import java.util.Collections;

import java.awt.Dimension;
import java.awt.GridLayout;  
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import java.awt.Font;
import java.util.Random;

/**
 * This is a Tetris class represent Tetris board with animations
 * @author Barış Batuhan Bolat
 */
public class TetrisS extends JFrame{
    private int[][] board;
    private int[][] board_cpy;
    private int[][] tetro;
    private JButton[][] buttons;
	private JPanel panel;
    private int x,y; //Coordinates    
    private boolean isGameOver;
    private int width;
    private int height;
    private Tetromino m;
    
    public void init(){
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
        add();
		f.add(panel);
		f.setVisible(true);
    }
    /**
     * This method copies the actual board for backup
     */
	public void backup() {
		for (int i = 0; i < 23; i++) {
			for (int j = 0; j < 12; j++) {
				board_cpy[i][j] = board[i][j];
			}
		}
	}
    /**
     * This method adds a new tetromino to the board
     * @param newT Tetromino variable to be add
     */
    public void add(){
        x = 4;
		y = 0;
        tetro[3][0] = 1;
        tetro[3][1] = 1;
        tetro[3][2] = 1;
        tetro[3][3] = 1;
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
     * This method moveCs the Tetromino in the board according to the given parameters
     * @param newX integer variable to represent new x axis moveCment
     * @param newY integer variable to represent new y axis moveCment
     */
	public void moveC(int newX, int newY) {
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
     * @param newX integer variable to represent new x axis moveCment
     * @param newY integer variable to represent new y axis moveCment
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
     * This method randomly moveCs the Tetromino in x axis at first and starts moving downward accordingly fullness
     */
    public void animate(){
        draw();
        while(isGameOver == false){
            //System.out.println(isFilled(x, y+1));
            if (!isFilled(x, y + 1)) {
				moveC(x, y + 1);
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
		for(int i = 0;i<23;i++){
			for(int j = 0;j<12;j++){
				if(board[i][j] == 0){
					buttons[i][j].setBackground(Color.BLACK);
				}
				else if(board[i][j] == 1){
					buttons[i][j].setBackground(Color.blue);
				}
				else if(board[i][j] == 2){
					buttons[i][j].setBackground(Color.WHITE);
				}
				else if(board[i][j] == 3){
					buttons[i][j].setBackground(Color.RED);
				}				
			}
		}       
    }   

    public static void main(String args[]){
        TetrisS game = new TetrisS();
        game.init();
    }

}
