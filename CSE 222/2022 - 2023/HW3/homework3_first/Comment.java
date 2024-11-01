package homework3_first;
/**
 * Extended Comment class form Interaction class  
 * @author Barış Batuhan Bolat
 */
public class Comment extends Interaction {
    private String content;

    /**
     * Default constructor for Comment class
     * <p>
     * This constructor calls other constructor with invalid parameters
     */
    public Comment(){
        this(0,null,0,"");
    }
    /**
     * Constructor for Comment class
     * <p>
     * This constructor calls superclass constructor
     * @param ID Integer variable to identify interactionID
     * @param account Account variable to identify account who make comment
     * @param postID Integer variable to identify postID
     * @param content String variable to identify comments content
     */
    public Comment(int ID,Account account,int postID,String content){
        super(ID,account,postID);
        this.content = content;
    }
    /**
     * Get method for comments content
     * @return String variable to identify comments content
     */
    public String getContent(){
        return content;
    }
}
