package homework6;
/**
 * 
 * @author Barış Batuhan Bolat
 */
import java.util.ArrayList;

public class info {
    private int count;
    private ArrayList<String> words;
    /**
     * Default constructor 
     */
    public info() {
        this.count = 0;
        this.words = new ArrayList<>();
    }
    /**
     * Copy constructor
     * @param other Other info object to be copied
     */
    public info(info other){
        this.set(other);
    }
    /**
     * A method to add new word to list
     * @param word String 
     */
    public void push(String word) {
        ++count;
        this.words.add(word);
    }
    /**
     * Set method for info class. Works like a copy constructor
     * @param other Other info object to be copied
     */
    public void set(info other){
        this.count = other.getCount();
        this.words = other.getWords();
    }
    /**
     * Get method for count 
     * @return Count of character
     */ 
    public int getCount() {
        return this.count;
    }
    /**
     * Get method for words
     * @return Words list
     */
    public ArrayList<String> getWords(){
        return words;
    }

    @Override
    public String toString(){
        StringBuilder str  = new StringBuilder();
        str.append("Count : " + count + " - Words : [" + words.get(0));
        for(int i = 1;i<words.size();i++){
            str.append("," + words.get(i));
        }
        str.append("]");
        return str.toString();
    }
}
