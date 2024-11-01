package homework3_third;
/**
 * Interaction class for keeping Interaction details
 * @author Barış Batuhan Bolat
 */
public class Interaction {
    protected final int interactionID;
    protected Account account;
    protected int postID;
    /**
     * Default constructor for Interaction class
     * <p>
     * This constructor calls other constructor with invalid parameters
     */
    public Interaction(){
        this(0,null,0);
    }
    /**
     * Constructor for Interaction class
     * @param ID Integer variable to identify interactionID
     * @param account Account variable to identify accountID
     * @param postID Integer variable to identify postID
     */
    public Interaction(int ID,Account account,int postID){
        this.interactionID = ID;
        this.account = account;
        this.postID = postID;
    }
    /**
     * Get method for interactionID
     * @return Integer variable to identify interactionID
     */
    public int getID(){
        return interactionID;
    }
    /**
     * Get method for account
     * @return Account variable to identify account who make comment or like
     */
    public Account getAccount(){
        return account;
    }
    /**
     * Get method for postID
     * @return Integer variable to identify postID
     */
    public int getPostID(){
        return postID;
    }
}
