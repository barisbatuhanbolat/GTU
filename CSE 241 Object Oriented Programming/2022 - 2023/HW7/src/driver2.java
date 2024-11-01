import java.util.Scanner;
import java.util.Random;

public class driver2 {
    public static void main(String[] args){
        Scanner input = new Scanner(System.in);
        int key = 0;
        char tChoice = 'I';
        int height,width;
        do {
            System.out.print("Enter height: ");
            while (!input.hasNextInt()) {
                System.out.println("Wrong input!");
                input.next(); 
            }
            height = input.nextInt();            
            System.out.print("Enter width: ");
            while (!input.hasNextInt()) {
                System.out.println("Wrong input!");
                input.next(); 
            }
            width = input.nextInt();
        } while (height <= 0 || width <= 0);
        
        Tetris game  = new Tetris(height, width);
        
        while(key != 9){
            System.out.println("Choose Tetromino Type");
            System.out.println("\t1 - I");
            System.out.println("\t2 - O");
            System.out.println("\t3 - L");
            System.out.println("\t4 - S");
            System.out.println("\t5 - Z");
            System.out.println("\t6 - T");
            System.out.println("\t7 - J");
            System.out.println("\t8 - Random");
            System.out.println("\t9 - Quit");
            do {
                System.out.print("Choice: ");
                while (!input.hasNextInt()) {
                    System.out.print("Wrong Choice!!: ");
                    input.next(); 
                }
                key = input.nextInt();
            } while (key <= 0 || key >9 || key<0);

            if(key == 8){
                Random rand = new Random();
                key = 1 + rand.nextInt(6);
            }
            if(key == 9){
                break;
            }
            switch(key){
                case 1:
                    tChoice = 'I';
                    break;
                case 2:
                    tChoice = 'O';
                    break;
                case 3:
                    tChoice = 'L';
                    break;
                case 4:
                    tChoice = 'S';
                    break;                                        
                case 5:
                    tChoice = 'Z';
                    break;
                case 6:
                    tChoice = 'T';
                    break;
                case 7:
                    tChoice = 'J';
                    break;
                
                
            }
            Tetromino tetro = new Tetromino(tChoice);
            game.add(tetro);
            game.animate();
        }
        input.close();
    }
}