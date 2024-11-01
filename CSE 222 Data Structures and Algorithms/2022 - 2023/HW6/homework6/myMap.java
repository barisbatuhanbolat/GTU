package homework6;
/**
 * Custom map class to perform desired operations
 * @author Barış Batuhan Bolat
 */
import java.util.LinkedHashMap;


public class myMap{
    private LinkedHashMap <String, info> map = new LinkedHashMap<String,info>();;
    private int mapSize = 0;
    private String str = null;
    
    /**
     * Default constructor with null parameter
     */
    public myMap(){
        this((String)null);
    }
    /**
     * Constructor with regular string input
     * @param input String to be mapped
     */
    public myMap(String input){
        if(input != null){
            StringBuilder output = new StringBuilder();
            for (int i = 0;i<input.length();i++) {
                if (Character.isLetter(input.charAt(i))) {
                    output.append(Character.toLowerCase(input.charAt(i)));
                } 
                else if (input.charAt(i) == ' ') {
                    output.append(input.charAt(i));
                }
            }
            input = output.toString();
        }
        str = input;
        boolean control = this.buildMap();
        if(!control){
            System.out.println("\u001B[31m" + "\nPreprocessed String is empty" + "\u001B[0m");
        }
    }
    /**
     * Copy constructor
     * @param other Map to be copied
     */
    public myMap(myMap other){
        this.setMap(other.getMap());
        this.setSize(other.getSize());
        this.setStr(other.getstr());
    }
    /**
     * A method to create map according to string 
     * @return true if string is non-empty and not null false otherwisse
     */
    public boolean buildMap(){
        if(!str.equals("") && str != null){
            String[] words = str.split(" ");
            for (String word : words) {
                for (int i = 0;i<word.length();i++) {
                    String c = word.substring(i, i+1);
                    if (!this.containsKey(c)) {
                        ++mapSize;
                        this.put(c, new info());
                    }
                    this.get(c).push(word);
                }
            }
            return true;
        }
        else{
            return false;
        }
    }
    /**
     * A method that prints map 
     */
    public void printMap(){
        if(!str.equals("") && str != null){
            for(String key : this.getKeys()){
                System.out.println(key + " --> " + get(key).toString());
            }
        }
        else{
            System.out.println("\u001B[31m" + "\nPreprocessed String is empty" + "\u001B[0m");
        }
    }
    /**
     * Clears map
     */
    public void clearMap(){
        map.clear();
    }
    /**
     * This method checks whether the map instance variable contains a key-value pair where the key is equal to the key parameter.
     * @param key String key to be searched
     * @return true if key-value pair exists false otherwise
     */
    public boolean containsKey(String key){
        return map.containsKey(key);
    }
    /**
     * This method adds a key-value mapping to the map instance variable. The key is the key parameter and the value is the value parameter. 
     * @param key String key 
     * @param value info value
     * @return Added value
     */
    public info put(String key,info value){
        map.put(key, value);
        return value;
    }
    /**
     * Get method to reach maps value according to given key
     * @param key String 
     * @return Value of given key 
     */
    public info get(String key){
        return map.get(key);
    }    
    /**
     * Set method for map
     * @param newMap New map to be copied to original one
     */
    public void setMap(LinkedHashMap <String, info> newMap){
        map = newMap;
    }
    /**
     * Set method for string 
     * @param newstr New string to be copied to original one
     */
    public void setStr(String newstr){
        str = newstr;
    }
    /**
     * Set method for mapsize
     * @param newSize New map size to be copied to original one
     */
    public void setSize(int newSize){
        mapSize = newSize;
    }
    /**
     * Get method for string
     * @return String of map
     */
    public String getstr(){
        return str;
    }
    /**
     * Get method for map size
     * @return Size of map
     */
    public int getSize(){
        return mapSize;
    }
    /**
     * Get for map
     * @return Map as LinkedHashMap strucure
     */
    public LinkedHashMap <String, info> getMap(){
        return map;
    }
    /**
     * Get method for keyset of map
     * @return String array representation of keyset of map
     */
    public String[] getKeys(){
        return map.keySet().toArray(new String[0]);
    }
    /**
     * Get method for values of map
     * @return info array representation of values of map
     */    
    public info[] getValues(){
        return map.values().toArray(new info[0]);
    }

}
