package homework3_first;

import java.util.ArrayList;

/**
 * Post class for keeping post details
 * @author Barış Batuhan Bolat
 */
public class Post{
    private final int postID;
    private Account author;
    private ArrayList<Like> likes;
    private ArrayList<Comment> comments;
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
        this.likes = new ArrayList<Like>();
        this.comments = new ArrayList<Comment>();
    }
    /**
     * Get method for postID
     * @return Integer variable to identify postID
     */
    public int getID(){
        return postID;
    }
    /**
     * Get method for post author
     * @return Account variable to identify author
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
     * Get method for likes list of post
     * @return Like list variable to identify likes of post
     */
    public ArrayList<Like> getLikes(){
        return likes;
    }
    /**
     * Get method for comment list of post
     * @return Comment list variable to identify comments of post
     */
    public ArrayList<Comment> getComments(){
        return comments;
    }
    /**
     * Set method for likes of post. For helping dynamic allocation methods.
     * @param newLikes new Like list to be setted
     */
    public void setLikes(ArrayList<Like> newLikes){
        likes = newLikes;
    }
    /**
     * Set method for comments of post. For helping dynamic allocation methods.
     * @param newComments new Comment array to be setted
     */ 
    public void setComments(ArrayList<Comment> newComments){
        comments = newComments;
    }
}