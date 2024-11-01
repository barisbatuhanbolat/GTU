package homework7;
/**
 * Driver Class for testing sorting algorithms
 * @author Barış Batuhan Bolat
 */
public class TestClass {
    public static void main (String args[]){
        mergeSort obj = new mergeSort();
        selectionSort obj2 = new selectionSort();
        insertionSort obj3 = new insertionSort();
        bubbleSort obj4 = new bubbleSort();
        quickSort obj5 = new quickSort();
        
        System.out.println("Best Case");
        myMap map = new myMap("a bb ccc dddd eeeee");
        System.out.println("Input : " + map.getstr());
        System.out.println("Original Map");
        map.printMap();
        System.out.println("mergeSort");
        obj.sort(map).printMap();
        System.out.println("selectionSort");
        obj2.sort(map).printMap();
        System.out.println("insertionSort");
        obj3.sort(map).printMap();
        System.out.println("bubbleSort");
        obj4.sort(map).printMap(); 
        System.out.println("quickSort");
        obj5.sort(map).printMap();
        System.out.println("--------------------------------------------------------------");

        System.out.println("Average Case");
        map = new myMap("bb eeeee a dddd ccc");
        System.out.println("Input : " + map.getstr());
        System.out.println("Original Map");
        map.printMap();        
        System.out.println("mergeSort");
        obj.sort(map).printMap();
        System.out.println("selectionSort");
        obj2.sort(map).printMap();
        System.out.println("insertionSort");
        obj3.sort(map).printMap();
        System.out.println("bubbleSort");
        obj4.sort(map).printMap(); 
        System.out.println("quickSort");
        obj5.sort(map).printMap();
        System.out.println("--------------------------------------------------------------");        

        System.out.println("Worst Case");
        map = new myMap("eeeee dddd ccc bb a");
        System.out.println("Input : " + map.getstr());
        System.out.println("Original Map");
        map.printMap();
        System.out.println("mergeSort");
        obj.sort(map).printMap();
        System.out.println("selectionSort");
        obj2.sort(map).printMap();
        System.out.println("insertionSort");
        obj3.sort(map).printMap();
        System.out.println("bubbleSort");
        obj4.sort(map).printMap(); 
        System.out.println("quickSort");
        obj5.sort(map).printMap();
        System.out.println("--------------------------------------------------------------");       
    }
}