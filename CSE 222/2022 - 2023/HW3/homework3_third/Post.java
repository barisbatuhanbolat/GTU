package homework3_third;

/**
 * Post class for keeping post details
 * @author Barış Batuhan Bolat
 */
public class Post{
    private final int postID;
    private Account author;
    private LDLinkedList<Like> likes;
    private LDLinkedList<Comment> comments;
    private String content;
    /**
     * Default constructor for Post class.
     * <p>
     * This constructor calls other constructor with invalid parameters.
     */
    public Post(){
        this(0,null,"");
    }    
    /**
     * Constructor for Post class
     * @param ID Integer variable to identify postID
     * @param author Account variable to identify author
     * @param content String variable to identify post content
     */
    public Post(int ID ,Account author, String content) {
        this.postID = ID;
        this.author = author;
        this.content = content;
        this.likes = new LDLinkedList<Like>();
        this.comments = new LDLinkedList<Comment>();
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
     */
    public Account getAccount(){
        return author;
    }
    /**
     * Get method for post content
     * @return String variable to identify content of post
     */
    public String getContent(){
        return content;
    }
    /**
     * Get method for likes ldlinkedlist of post
     * @return Like list variable to identify likes of post
     */
    public LDLinkedList<Like> getLikes(){
        return likes;
    }
    /**
     * Get method for comment ldlinkedlist of post
     * @return Comment list variable to identify comments of post
     */
    public LDLinkedList<Comment> getComments(){
        return comments;
    }
    /**
     * Set method for likes of post. For helping dynamic allocation methods.
     * @param newLikes new Like array to be setted
     */
    public void setLikes(LDLinkedList<Like> newLikes){
        likes = newLikes;
    }
    /**
     * Set method for comments of post. For helping dynamic allocation methods.
     * @param newComments new Comment array to be setted
     */ 
    public void setComments(LDLinkedList<Comment> newComments){
        comments = newComments;
    }
}