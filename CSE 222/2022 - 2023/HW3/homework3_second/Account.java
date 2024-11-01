package homework3_second;
import java.util.LinkedList;
/**
 * Account class for keeping users datas
 * @author Barış Batuhan Bolat
 */
public class Account{
    private final int accountID;
    private String username;
    private String birthdate;
    private String location;
    private LinkedList<Post> posts;
    private LinkedList<Message> messages;
    private LinkedList<Account> following;
    private LinkedList<Account> followers;
    private LinkedList<Account> blockedAccounts;
    private LinkedList<String> history;
    private boolean isLogin = false;
    private boolean isViewed = false;
    
    /**
     * Default constructor for Account class.
     * <p>
     * This constructor calls other constructor with invalid parameters.
     */
    public Account(){
        this(0,null,null,null);
    }
    /**
     * Only username constructor for Account class
     * <p>
     * This constructor calls other constructor with username and invalid birthdate and location parameters.
     * @param ID Uniqe integer variable for identify Account object
     * @param username String variable for declaring Account's username
     */
    public Account(int ID,String username){
        this(ID,username,null,null);
    }
    /**
     * Constructor for Account class
     * @param ID Uniqe integer variable for identify Account object
     * @param username String variable for declaring Account's username
     * @param birthdate String variable for declaring Account's birthday
     * @param location String variable for declaring Account's location
     */
    public Account(int ID,String username,String birthdate,String location){
        accountID = ID;
        this.username = username;
        this.birthdate = birthdate;
        this.location = location;
        this.messages = new LinkedList<Message>();
        this.posts = new LinkedList<Post>();
        this.following = new LinkedList<Account>();
        this.followers = new LinkedList<Account>();
        this.blockedAccounts = new LinkedList<Account>();
        this.history = new LinkedList<String>();
        System.out.println("An account with username " + this.getUsername() + " has been created.");


    }
    /**
     * Login system. 
     * <p> 
     * This method changes isLogin variable to true when it called.
     */
    public void Login(){
        if(isLogin == false){
            System.out.println("\nLogging into an account (username: " + this.getUsername() +")");
            isLogin = true;   
        }
        else{
            System.out.println("\u001B[31m" + "\nYou already login this account" + "\u001B[0m");
        }
    }
    /**
     * LogOut system
     * <p>
     * This method changes isLogin variable to false when it called
     */
    public void LogOut(){
        if(isLogin != false){
            System.out.println("\nLogging out from account '"+this.getUsername()+"'...");
            isLogin = false;
        }
        else{
            System.out.println("\u001B[31m" + "\nYou already logout" + "\u001B[0m");
        }
    }
    /**
     * This method prints the parameter account's detailes
     * @param account Account variable to be printed
     */
    public void viewProfile(Account account){
        if(isLogin != false && !account.isBlocked(this)){
            System.out.println("\nViewing "+account.getUsername() +"'s profile...");
            System.out.println("----------------------");
            System.out.println("User ID: "+account.getID());
            System.out.println("Username: "+account.getUsername());
            System.out.println("Birthdate: "+account.getBirthdate());
            System.out.println("Location: "+account.getLocation());
            System.out.println(account.getUsername() + " is following " + account.getFollowing().size() + " account(s) and has " + account.getFollowers().size() + " follower(s).");
            System.out.print("The followers of " + account.getUsername() + " is: ");
            for(Account follower : account.getFollowers()){
                System.out.print(follower.getUsername() + ",");
            }
            System.out.print("\n" + account.getUsername() + " is following: ");
            for(Account following : account.getFollowing()){
                System.out.print(following.getUsername() + ",");
            }
            System.out.print("\n");
            System.out.println(account.getUsername() + " has " + account.getPosts().size() + " post(s).");
            if(!account.equals(this)){
                account.isViewed = true;                
            }
        }
        else if(isLogin == false){
            System.out.println("\u001B[31m" + "\nYou are not logged in" + "\u001B[0m");
        }
        else if(account.isBlocked(this)){
            System.out.println("\u001B[31m" + "You can't view "+ account.getUsername() + "'s profile. You are blocked by this user." + "\u001B[0m");
        }
    }
    public void viewHistory(){
        if(isLogin != false){
            System.out.println("\nViewing action history of " + this.getUsername());
            System.out.println("----------------------");
            for(String act : history){
                System.out.println(act);
            }
        }
        else{
            System.out.println("\u001B[31m" + "\nYou are not logged in" + "\u001B[0m");
        }
    }
    /**
     * This method checks the messages array for sended messages
     */
    public void checkOutbox(){
        if(isLogin != false){
            int count = 0 ;
            for(Message message : this.getMessages()){
                if(message.getSender().equals(this)){
                    ++count;
                }
            }
            System.out.println("\nChecking outbox...\nThere is/are " + count + " message(s) in the outbox.");
        }
        else{
            System.out.println("\u001B[31m" + "\nYou are not logged in" + "\u001B[0m");
        }
    }
    /**
     * This method checks the messages array for received messages
     */    
    public void checkInbox(){
        if(isLogin != false){
            int count = 0 ;
            for(Message message : this.getMessages()){
                if(!message.getSender().equals(this)){
                    ++count;
                }
            }
            System.out.println("\nChecking inbox...\nThere is/are " + count + " message(s) in the inbox.");
    
        }
        else{
            System.out.println("\u001B[31m" + "\nYou are not logged in" + "\u001B[0m");
        }        
    }
    /**
     * This method prints the sended messages with their details
     */
    public void viewOutbox(){
        if(isLogin != false){
            System.out.println("\nViewing " + this.getUsername() + " 's outbox...");
            if(this.getMessages().size() != 0){
                for(Message message : this.getMessages()){
                    if(message.getSender().equals(this)){
                        System.out.println("Message ID: " + message.getID());
                        System.out.println("From: " + this.getUsername());
                        System.out.println("To: " + message.getReceiver().getUsername());
                        System.out.println("Message: " + message.getContent());
                        System.out.println("------------------------------");
                    }
                } 
            }   
            else{
                System.out.println("\nEmpty...");
            
            }
        }
        else{
            System.out.println("\u001B[31m" + "\nYou are not logged in" + "\u001B[0m");
        }
    }
    /**
     * This method prints the received messages with their details
     */
    public void viewInbox(){
        if(isLogin != false){
            System.out.println("\nViewing " + this.getUsername() + " 's inbox...");
            if(this.getMessages().size() != 0){
                for(Message message : this.getMessages()){
                    if(!message.getSender().equals(this)){
                        System.out.println("Message ID: " + message.getID());
                        System.out.println("From: " + message.getSender().getUsername());
                        System.out.println("To: " + this.getUsername());
                        System.out.println("Message: " + message.getContent());
                        System.out.println("------------------------------");
                    }
                }
            }
            else{
                System.out.println("\nEmpty...");
            }
        }
        else{
            System.out.println("\u001B[31m" + "\nYou are not logged in" + "\u001B[0m");
        }
    }
    /**
     * This method prints the posts of given Account with details
     * @param account Account variable to be printed its posts with details
     */    
    public void viewPosts(Account account){
        if(isLogin != false){
            if((!account.equals(this) && account.isViewed != false) || (account.equals(this))){
                System.out.println("\nViewing " + account.getUsername() + " 's posts...");
                if(account.getPosts().size() != 0){
                    for(Post post : account.getPosts()){
                        System.out.println("(Post ID: " + post.getID() + "): " + post.getContent());
                    }
                }
            }
        }
        else{
            System.out.println("\u001B[31m" + "\nYou are not logged in" + "\u001B[0m");
        }
    }
    /**
     * This method prints the interactions of users posts 
     * @param account Account to view interactions
     */
    public void viewInteractions(Account account){
        if(isLogin != false){
            if((!account.equals(this) && account.isViewed != false) || (account.equals(this))){
                System.out.println("\nViewing " + account.getUsername() + " 's post's interactions...");
                System.out.println("------------------------------");
                if(account.getPosts().size() != 0){
                    for(int i = 0;i<account.getPosts().size();i++){
                        System.out.println("(Post ID: " + account.getPosts().get(i).getID() + "): " + account.getPosts().get(i).getContent());
                        System.out.print("The post was liked by the following account(s): ");
                        for(int j = 0;j<account.getPosts().get(i).getLikes().size();j++){
                            System.out.print(account.getPosts().get(i).getLikes().get(j).getAccount().getUsername() + ", ");
                        }
                        System.out.println("\nThe post has " + account.getPosts().get(i).getComments().size()  + " comment(s)...");
                        for(int j = 0;j<account.getPosts().get(i).getComments().size();j++){
                            System.out.print("Comment " + (j+1) + ": " + "'" +account.getPosts().get(i).getComments().get(j).getAccount().getUsername() + "' said '" + account.getPosts().get(i).getComments().get(j).getContent() + "'");
                            System.out.print("\n");

                        }
                        System.out.print("------------------------------\n");
                    }
                }
            }
        }
        else{
            System.out.println("\u001B[31m" + "\nYou are not logged in" + "\u001B[0m");
        } 
    }
    /**
     * This method adds the given account to users following array and also adds our user to given accounts followers array
     * @param account Account variable to be followed
     */
    public void followAccount(Account account){
        if(isLogin != false && !this.inFollowing(account)){
            System.out.println("\nFollowing " + account.getUsername());
            following.add(account);
            account.followers.add(this);
            history.add("You followed " + account.getUsername());
        }
        else if(isLogin == false){
            System.out.println("\u001B[31m" + "\nYou are not logged in" + "\u001B[0m");
        }
        else if(this.inFollowing(account)){
            System.out.println("\u001B[31m" + "\nYou already follow this account." + "\u001B[0m");
        }
    }
    /**
     * This method deletes the given account to users following array and also deletes our user to given accounts followers array
     * @param account Account variable to be unfollowed
     */    
    public void unFollowAccount(Account account){
        if(isLogin != false && inFollowing(account)){
            System.out.println("\nUnfollowing " + account.getUsername());
            following.remove(account);
            account.followers.remove(this);
            history.add("You unfollowed " + account.getUsername());
        }
        else if(isLogin == false){
            System.out.println("\u001B[31m" + "\nYou are not logged in" + "\u001B[0m");
        }
        else if(!inFollowing(account) == false){
            System.out.println("\u001B[31m" + "\nYou need to follow first " + "\u001B[0m");
        }
    }
    /**
     * This method sends the given message to given account
     * @param account Account variable to whom the message will be sent.
     * @param content String variable to represent message for sending
     */
    public void sendMessage(Account account,String content){
        if(isLogin != false && this.inFollowing(account) && !account.isBlocked(this) && !this.isBlocked(account)){
            System.out.println("\nSending a message to '" + account.getUsername() + "... '");
            int count = (this.getMessages().size() > account.getMessages().size()) ? this.getMessages().size()  : account.getMessages().size() ;
            Message newMsg = new Message(count + 1,this,account,content);
            messages.add(newMsg);
            account.messages.add(newMsg);
            history.add("You sent message to " + account.getUsername());
        }
        else if(isLogin == false){
            System.out.println("\u001B[31m" + "\nYou are not logged in" + "\u001B[0m");
        }
        else if(!this.inFollowing(account)){
            System.out.println("\u001B[31m" + "\nYou need to follow this account for send a message." + "\u001B[0m");
        }  
        else if(account.isBlocked(this)){
            System.out.println("\u001B[31m" + "\nYou can't send a message to this user because you are blocked by this account." + "\u001B[0m");
        }      
        else if(this.isBlocked(account)){
            System.out.println("\u001B[31m" + "\nYou can't send a message to this user because you blocked this account." + "\u001B[0m");
        }     
    }
    /**This method shares the post 
     * <p>
     * This method creates Post variable and add it to users Post array
     * @param content String variable to be shared
     */
    public void sharePost(String content){
        if(isLogin != false){
            System.out.println("\nSending post");
            posts.add(new Post(this.getPosts().size() + 1,this,content));
            history.add("You shared post with content \"" + content + "\"");
        }
        else{
            System.out.println("\u001B[31m" + "\nYou are not logged in" + "\u001B[0m");
        }          
    }
    /**This method likes the given post
     * <p>
     * This method creates Like variable and add it to given Post variables Like array
     * @param post Post variable to be liked
     */
    public void likePost(Post post){
        if(isLogin != false && !isLiking(post)){
            System.out.println("\nLiking " + post.getAccount().getUsername() + "'s post id: " + post.getID());
            post.getLikes().add(new Like(post.getLikes().size() +1 ,this,post.getID()));
            history.add("You liked " + post.getAccount().getUsername() + "'s post id: " + post.getID());
        }
        else if(isLogin == false){
            System.out.println("\u001B[31m" + "\nYou are not logged in" + "\u001B[0m");
        }
        else if(isLiking(post)){
            System.out.println("\u001B[31m" + "\nYou already liked this post " + "\u001B[0m");
        }       
    }
    /**This method comments the given post with given content
     * <p>
     * This method creates Comment variable with given content and add itt to given Post variables Comment array
     * @param post Post variable to be commented
     * @param content String variable represent content of the comment
     */
    public void commentPost(Post post,String content){
        if(isLogin != false){
            System.out.println("\nCommenting " + post.getAccount().getUsername() + "'s post id: " + post.getID());
            post.getComments().add(new Comment(post.getComments().size() + 1 ,this,post.getID(),content));
            history.add("You commented " + post.getAccount().getUsername() + "'s post id: " + post.getID());
        }
        else{
            System.out.println("\u001B[31m" + "\nYou are not logged in" + "\u001B[0m");
        }          
    }
    /**This method unlikes the already liked post
     * @param post Post variable to be unliked
     */
    public void unLikePost(Post post){
        if(isLogin != false && isLiking(post)){
            System.out.println("\nUnliking " + post.getAccount().getUsername() + "'s post id: " + post.getID());
            Like like = new Like();
            for(int i = 0;i<post.getLikes().size();i++){
                like = post.getLikes().get(i);
                if(this.equals(like.getAccount())){
                    break;
                }
            }
            history.add("You unliked " + post.getAccount().getUsername() + "'s post id: " + post.getID());
            post.getLikes().remove(like);
        }
        else if(isLogin == false){
            System.out.println("\u001B[31m" + "\nYou are not logged in" + "\u001B[0m");
        }
        else if(!isLiking(post)){
            System.out.println("\u001B[31m" + "\nYou need to like first " + "\u001B[0m");
        }
    }
    /**This method deletes the comment from post
     * @param post Post variable
     * @param content String variable
     */
    public void unCommentPost(Post post,String content){
        if(isLogin != false && isCommenting(post)){
            System.out.println("\nDeleting comment from " + post.getAccount().getUsername() + "'s post id: " + post.getID());
            Comment comment = new Comment();
            for(int i = 0;i<post.getComments().size();i++){
                comment = post.getComments().get(i);
                if(this.equals(comment.getAccount())){
                    if(comment.getContent().equals(content)){
                        break;
                    }
                }
            }
            history.add("You deleted comment from " + post.getAccount().getUsername() + "'s post id: " + post.getID());
            post.getComments().remove(comment);
        }
        else if(isLogin == false){
            System.out.println("\u001B[31m" + "\nYou need to login first " + "\u001B[0m");
        }
        else if(!isCommenting(post)){
            System.out.println("\u001B[31m" + "\nYou need to comment first " + "\u001B[0m");
        }        
    }   
    /**
     * This method blocks the given account to restrict some actions
     * <p>
     * This method adds to given account to users blockedAccounts array
     * @param account Account variable to be blocked
     */
    public void block(Account account){
        if(isLogin!= false && !this.isBlocked(account)){
            System.out.println("\nBlocking " + account.getUsername());
            blockedAccounts.add(account);
            if(inFollowing(account)){
                unFollowAccount(account);
            }
            if(account.inFollowing(this)){
                account.isLogin = true;
                account.unFollowAccount(this);
                account.isLogin = false;

            }
            history.add("You blocked " + account.getUsername());
        }
        else if(isLogin == false){
            System.out.println("\u001B[31m" + "\nYou are not logged in" + "\u001B[0m");
        }  
        else if(this.isBlocked(account)){
            System.out.println("\u001B[31m" + "\nYou already blocked this account." + "\u001B[0m");
        }  
    }
    /**
     * This method unblocks the already blocked account
     * <p>
     * This method deletes the account to users blockedAccounts array
     * @param account Account variable to be unblocked
     */       
    public void unblock(Account account){
        if(isLogin!= false && this.isBlocked(account)){
            System.out.println("\nUnblocking " + account.getUsername());
            blockedAccounts.remove(account);
        }
        else if(isLogin == false){
            System.out.println("\u001B[31m" + "\nYou are not logged in" + "\u001B[0m");
        }  
        else if(!this.isBlocked(account)){
            System.out.println("\u001B[31m" + "\nYou are not blocked this account." + "\u001B[0m");
        }  
    }    
    /**
     * This method checks the given post liked or not
     * @param post Post variable to be checked for like
     * @return boolean variable to represent liked or not.
     */
    public boolean isLiking(Post post){
        for(Like like : post.getLikes()){
            if(like.getAccount().equals(this)){
                return true;
            }
        }
        return false;
    }
    public boolean isCommenting(Post post){
        for(Comment comment : post.getComments()){
            if(comment.getAccount().equals(this)){
                return true;
            }
        }
        return false;
    }    
    /**
     * This method checks whether the given user has been followed.
     * @param account Account variable to be followed
     * @return LinkedList's contains method
     */
    public boolean inFollowing(Account account){
        return following.contains(account);
    }
    /**
     * This method checks whether the given user has been blocked.
     * @param account Account varible to be blocked
     * @return LinkedList's contains method
     */
    public boolean isBlocked(Account account){
        return blockedAccounts.contains(account);
    }
    
    @Override
    /**
     * This overriten method compare Account objects
     */
    public boolean equals(Object o){
        Account account = (Account)(o);
        if(this.getID() == account.getID()){
            return true;
        }
        return false;
    }
    /**
     *  This get method returns the post according to given id
     * @param id integer variable to represent id of Post
     * @return Post variable according to given id
     */
    public Post getPost(int id){
        return posts.get(id - 1);
    }
    /**
     * This get method returns the accountID
     * @return integer variable to represent uniqe userID
     */
    public int getID(){
        return accountID;
    }
    /**
     * This get method returns the username
     * @return String variable to represent users username
     */
    public String getUsername() {
        return username;
    }
    /**
     * This get method returns the users birthdate
     * @return String variable to represent users birthday
     */
    public String getBirthdate() {
        return birthdate;
    }
    /**
     * This get method returns the users location
     * @return String variable to represent users location
     */
    public String getLocation() {
        return location;
    }    
    /**
     * This get method returns the users posts array
     * @return Post array variable to represent users posts
     */
    public LinkedList<Post> getPosts() {
        return posts;
    }
    /**
     * This get method returns the users followings
     * @return Account array variable to represent users followings 
     */
    public LinkedList<Account> getFollowing(){
        return following;
    }
    /**
     * This get method returns the users followers
     * @return Account array variable to represent users followers 
     */
    public LinkedList<Account> getFollowers(){
        return followers;
    }
    /**
     * This get method returns the users messages
     * @return Message array variable to represent users messages
     */
    public LinkedList<Message> getMessages(){
        return messages;
    }
}
