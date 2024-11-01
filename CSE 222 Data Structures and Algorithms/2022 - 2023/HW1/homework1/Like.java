package homework1;
/**
 * Extended Like class form Interaction class  
 * @author Barış Batuhan Bolat
 */
public class Like extends Interaction {
    /**
     * Default constructor for Like class
     * <p>
     * This constructor calls other constructor with invalid parameters
     */
    public Like(){
        this(0,null,0);
    }
    /**
     * Constructor for Like class
     * <p>
     * This constructor calls superclass constructor
     * @param ID Integer variable to identify interactionID
     * @param account Account variable to identify account who liked
     * @param postID Integer variable to identify postID
     */
    public Like(int ID,Account account,int postID){
        super(ID,account,postID);
    }
}
