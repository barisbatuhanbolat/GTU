import java.util.Scanner;
import java.util.Random;
/**
 * Driver for testing classes
 */
public class driver1 {
    public static void Wait(){
        try {
            Thread.sleep(500);
        } 
        catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
    public static void main(String args[]){
        int key;
        Scanner input = new Scanner(System.in);
        System.out.println("--------------------Testing Tetromino Class--------------------");
        System.out.println("-----------------Testing Tetromino Constructor-----------------");

        System.out.println("Choose Tetromino Type");
        System.out.println("\t1 - I");
        System.out.println("\t2 - O");
        System.out.println("\t3 - L");
        System.out.println("\t4 - S");
        System.out.println("\t5 - Z");
        System.out.println("\t6 - T");
        System.out.println("\t7 - J");
        do {
            System.out.print("Choice: ");
            while (!input.hasNextInt()) {
                System.out.print("Wrong Choice!!: ");
                input.next(); // this is important!
            }
            key = input.nextInt();
        } while (key <= 0 || key >7 || key<0);
        char tChoice = 'I';
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
        Wait();
        System.out.println("--------------------Testing Tetromino Print--------------------");
        tetro.print();
        Wait();
        System.out.println("-------------------Testing Tetromino Rotate--------------------");
        System.out.println("Rotate Left");
        tetro.rotate(0);
        tetro.print();
        Wait();
        System.out.println("Rotate Right");
        tetro.rotate(1);  
        tetro.print();
        Wait();
        System.out.println("----------------------Testing Tetris Class---------------------");
        System.out.println("------------------Testing Tetris Constructor-------------------");
        System.out.println("Creating 50x50 Tetris Board");
        Tetris game  = new Tetris(50, 50);
        Wait();
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
                input.next(); // this is important!
            }
            key = input.nextInt();
        } while (key <= 0 || key >9 || key<0);

        if(key == 8){
            Random rand = new Random();
            key = 1 + rand.nextInt(6);
        }
        if(key == 9){
           System.exit(0);
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
        tetro = new Tetromino(tChoice);
        Wait();
        System.out.println("----------------------Testing Tetris Add-----------------------");
        game.add(tetro);
        Wait();
        game.draw();
        System.out.println("----------------------Testing Tetris Draw----------------------");
        Wait();
        game.move(30, 5);
        game.draw();
        System.out.println("----------------------Testing Tetris Move----------------------");
        System.out.println("5 block downward and 5 block right");        
        System.out.println("Press any key to continue testing....");
        try{System.in.read();}
        catch(Exception e){}

        game.animate();
        System.out.println("--------------------Testing Tetris Animate---------------------");

        System.out.println("Press Enter to insert driver2");
        try{System.in.read();}
        catch(Exception e){}

        input.close();
    }
}
