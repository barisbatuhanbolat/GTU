package homework6;
/**
 * 
 * @author Barış Batuhan Bolat
 */

public class TestClass {    
    public static void main (String args[]){
        String target = new String();
        myMap map = null;
        myMap sortedMap = null;
        mergeSort obj = new mergeSort();

        System.out.println("Example 1");
        target = new String("Buzzing bees buzz.");
        System.out.println("Original String : " + target);
        map = new myMap(target);
        System.out.println("Preprocessed String : " + map.getstr());
        System.out.println("\n");
        System.out.println("The original (unsorted) map");
        map.printMap();
        System.out.println("\n");
        sortedMap = obj.sort(map);
        System.out.println("The sorted map");
        sortedMap.printMap();
        System.out.println("\n------------------------------------------------------\n");

        System.out.println("Example 2");
        target = new String("'Hush, hush!' whispered the rushing wind.");
        System.out.println("Original String : " + target);
        map = new myMap(target);
        System.out.println("Preprocessed String : " + map.getstr());
        System.out.println("\n");
        System.out.println("The original (unsorted) map");
        map.printMap();
        System.out.println("\n");
        sortedMap = obj.sort(map);
        System.out.println("The sorted map");
        sortedMap.printMap();  
        System.out.println("\n------------------------------------------------------\n");

        System.out.println("Example 3");
        target = new String("'java");
        System.out.println("Original String : " + target);
        map = new myMap(target);
        System.out.println("Preprocessed String : " + map.getstr());
        System.out.println("\n");
        System.out.println("The original (unsorted) map");
        map.printMap();
        System.out.println("\n");
        sortedMap = obj.sort(map);
        System.out.println("The sorted map");
        sortedMap.printMap();             
        System.out.println("\n------------------------------------------------------\n");

        System.out.println("Example 4");
        target = new String("'abc aba");
        System.out.println("Original String : " + target);
        map = new myMap(target);
        System.out.println("Preprocessed String : " + map.getstr());
        System.out.println("\n");
        System.out.println("The original (unsorted) map");
        map.printMap();
        System.out.println("\n");
        sortedMap = obj.sort(map);
        System.out.println("The sorted map");
        sortedMap.printMap();
        System.out.println("\n-------------------Custom Examples--------------------\n");

        System.out.println("Emtpy String");
        target = new String("");
        System.out.println("Original String : " + target);
        map = new myMap(target);
        System.out.println("Preprocessed String : " + map.getstr());
        System.out.println("\n");
        System.out.println("The original (unsorted) map");
        map.printMap();
        System.out.println("\n");
        sortedMap = obj.sort(map);
        System.out.println("The sorted map");
        sortedMap.printMap();
        System.out.println("\n------------------------------------------------------\n");
       
        System.out.println("String without letters.");
        target = new String("+^'-145154-()/");
        System.out.println("Original String : " + target);
        map = new myMap(target);
        System.out.println("Preprocessed String : " + map.getstr());
        System.out.println("\n");
        System.out.println("The original (unsorted) map");
        map.printMap();
        System.out.println("\n");
        sortedMap = obj.sort(map);
        System.out.println("The sorted map");
        sortedMap.printMap();        
    }
}