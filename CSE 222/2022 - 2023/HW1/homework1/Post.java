package homework1;
/**
 * Post class for keeping post details
 * @author Barış Batuhan Bolat
 */
public class Post{
    private final int postID;
    private int accountID;
    private Like[] likes;
    private Comment[] comments;
    private String content;
    /**
     * Default constructor for Post class.
     * <p>
     * This constructor calls other constructor with invalid parameters.
     */
    public Post(){
        this(0,0,"");
    }    
    /**
     * Constructor for Post class
     * @param ID Integer variable to identify postID
     * @param authorID Integer variable to identify accountID
     * @param content String variable to identify post content
     */
    public Post(int ID ,int authorID, String content) {
        this.postID = ID;
        this.accountID = authorID;
        this.content = content;
        this.comments = new Comment[0];
        this.likes = new Like[0];
    }
    /**
     * Get method for postID
     * @return Integer variable to identify postID
     */
    public int getID(){
        return postID;
    }
    /**
     * Get method for post author ID
     * @return Integer variable to identify accountID
     */
    public int getAccountID(){
        return accountID;
    }
    /**
     * Get method for post content
     * @return String variable to identify content of post
     */
    public String getContent(){
        return content;
    }
    /**
     * Get method for likes array of post
     * @return Like array variable to identify likes of post
     */
    public Like[] getLikes(){
        return likes;
    }
    /**
     * Get method for comment array of post
     * @return Comment array variable to identify comments of post
     */
    public Comment[] getComments(){
        return comments;
    }
    /**
     * Set method for likes of post. For helping dynamic allocation methods.
     * @param newLikes new Like array to be setted
     */
    public void setLikes(Like[] newLikes){
        likes = newLikes;
    }
    /**
     * Set method for comments of post. For helping dynamic allocation methods.
     * @param newComments new Comment array to be setted
     */ 
    public void setComments(Comment[] newComments){
        comments = newComments;
    }
}