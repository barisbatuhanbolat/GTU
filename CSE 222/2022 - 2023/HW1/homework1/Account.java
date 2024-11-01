package homework1;
/**
 * Account class for keeping users datas
 * @author Barış Batuhan Bolat
 */
public class Account{
    private final int accountID;
    private String username;
    private String birthdate;
    private String location;
    private Post[] posts;
    private Message[] messages;
    private Account[] following;
    private Account[] followers;
    private Account[] blockedAccounts;
    private boolean isLogin = false;
    
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
        this.messages = new Message[0];
        this.posts = new Post[0];
        this.following = new Account[0];
        this.followers = new Account[0];
        this.blockedAccounts = new Account[0];
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
            System.out.println("\nYou already login this account");
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
            System.out.println("\nYou already logout");
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
            System.out.println(account.getUsername() + " is following " + account.getFollowing().length + " account(s) and has " + account.getFollowers().length + " follower(s).");
            System.out.print("The followers of " + account.getUsername() + " is: ");
            for(Account follower : account.getFollowers()){
                System.out.print(follower.getUsername() + ",");
            }
            System.out.print("\n" + account.getUsername() + " is following: ");
            for(Account following : account.getFollowing()){
                System.out.print(following.getUsername() + ",");
            }
            System.out.print("\n");
            System.out.println(account.getUsername() + " has " + account.getPosts().length + " post(s).");
        }
        else if(isLogin == false){
            System.out.println("\nYou are not logged in");
        }
        else if(account.isBlocked(this)){
            System.out.println("You can't view "+ account.getUsername() + "'s profile. You are blocked by this user.");
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
            System.out.println("\nYou are not logged in");
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
            System.out.println("\nYou are not logged in");
        }        
    }
    /**
     * This method prints the sended messages with their details
     */
    public void viewOutbox(){
        if(isLogin != false){
            System.out.println("\nViewing " + this.getUsername() + " 's outbox...");
            if(this.getMessages().length != 0){
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
            System.out.println("\nYou are not logged in");
        }
    }
    /**
     * This method prints the received messages with their details
     * @param accounts Account array to get account usernames by using their ids
     */
    public void viewInbox(){
        if(isLogin != false){
            System.out.println("\nViewing " + this.getUsername() + " 's inbox...");
            if(this.getMessages().length != 0){
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
            System.out.println("\nYou need to login first");
        }
    }
    /**
     * This method prints the posts of given Account with details
     * @param account Account variable to be printed its posts with details
     */    
    public void viewPosts(Account account){
        if(isLogin != false){
            System.out.println("\nViewing " + account.getUsername() + " 's posts...");
            if(account.getPosts().length != 0){
                for(Post post : account.getPosts()){
                    System.out.println("(Post ID: " + post.getID() + "): " + post.getContent());
                }
            }
        }
        else{
            System.out.println("\nYou need to login first");
        }
    }
    /**
     * This method prints the interactions of users posts 
     * @param accounts Account array to get account usernames by using their ids
     */
    public void viewInteractions(Account account){
        System.out.println("\nViewing " + account.getUsername() + " 's post's interactions...");
        System.out.println("------------------------------");
        if(account.getPosts().length != 0){
            for(int i = 0;i<account.getPosts().length;i++){
                System.out.println("(Post ID: " + account.getPosts()[i].getID() + "): " + account.getPosts()[i].getContent());
                System.out.print("The post was liked by the following account(s): ");
                for(int j = 0;j<account.getPosts()[i].getLikes().length;j++){
                    System.out.print(account.getPosts()[i].getLikes()[j].getAccount().getUsername() + ", ");
                }
                System.out.println("\nThe post has " + account.getPosts()[i].getComments().length  + " comment(s)...");
                for(int j = 0;j<account.getPosts()[i].getComments().length;j++){
                    System.out.print("Comment " + (j+1) + ": " + "'" +account.getPosts()[i].getComments()[j].getAccount().getUsername() + "' said '" + account.getPosts()[i].getComments()[j].getContent() + "'");
                    System.out.print("\n");

                }
                System.out.print("------------------------------\n");
            }
        }
    }
    /**
     * This method adds the given account to users following array and also adds our user to given accounts followers array
     * @param account Account variable to be followed
     */
    public void followAccount(Account account){
        if(isLogin != false && !this.inFollowing(account)){
            System.out.println("\nFollowing " + account.getUsername());
            Account[] newArray = new Account[following.length + 1];
            for (int i = 0; i <following.length; i++) {
                newArray[i] = following[i];
            }
            newArray[following.length] = account;
            following = newArray;
            
            Account[] newArray2 = new Account[account.getFollowers().length + 1];
            for (int i = 0; i <account.getFollowers().length; i++) {
                newArray2[i] = account.getFollowers()[i];
            }
            newArray2[account.getFollowers().length] = this;
            account.followers = newArray2;
        }
        else if(isLogin == false){
            System.out.println("\nYou need to login first ");
        }
        else if(this.inFollowing(account)){
            System.out.println("\nYou already follow this account.");
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
            int count = (this.getMessages().length > account.getMessages().length) ? this.getMessages().length  : account.getMessages().length ;
            Message newMsg = new Message(count + 1,this,account,content);

            Message[] newArray = new Message[this.getMessages().length + 1];
            for (int i = 0; i <this.getMessages().length; i++) {
                newArray[i] = this.getMessages()[i];
            }
            newArray[this.getMessages().length] = newMsg;
            messages = newArray;
            
            Message[] newArray2 = new Message[account.getMessages().length + 1];
            for (int i = 0; i <account.getMessages().length; i++) {
                newArray2[i] = account.getMessages()[i];
            }
            newArray2[account.getMessages().length] = newMsg;
            account.messages = newArray2;
        }
        else if(isLogin == false){
            System.out.println("\nYou need to login first ");
        }
        else if(!this.inFollowing(account)){
            System.out.println("\nYou need to follow this account for send a message.");
        }  
        else if(account.isBlocked(this)){
            System.out.println("\nYou can't send a message to this user because you are blocked by this account.");
        }      
        else if(this.isBlocked(account)){
            System.out.println("\nYou can't send a message to this user because you blocked this account.");
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
            Post[] newArray = new Post[posts.length + 1];
            for(int i = 0;i<posts.length;i++){
                newArray[i] = posts[i];
            }
            newArray[posts.length] = new Post(this.getPosts().length + 1,this.getID(),content);
            posts = newArray;
        }
        else{
            System.out.println("\nYou need to login first ");
        }        
    }
    /**This method likes the given post
     * <p>
     * This method creates Like variable and add it to given Post variables Like array
     * @param post Post variable to be liked
     */
    public void likePost(Post post){
        if(isLogin != false){
            System.out.println("\nLiking post with id " + post.getID());
            Like[] newArray = new Like[post.getLikes().length + 1];
            for(int i = 0;i<post.getLikes().length;i++){
                newArray[i] = post.getLikes()[i];
            }
            newArray[post.getLikes().length] = new Like(post.getLikes().length +1 ,this,post.getID());
            post.setLikes(newArray);
        }
        else{
            System.out.println("\nYou need to login first ");
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
            System.out.println("\nCommenting post with id " + post.getID());
            Comment[] newArray = new Comment[post.getComments().length + 1];
            for(int i = 0;i<post.getComments().length;i++){
                newArray[i] = post.getComments()[i];
            }
            newArray[post.getComments().length] = new Comment(post.getComments().length + 1 ,this,post.getID(),content);
            post.setComments(newArray);
        }
        else{
            System.out.println("\nYou need to login first ");
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
            System.out.println("Blocking " + account.getUsername());
            Account[] newArray = new Account[blockedAccounts.length + 1];
            for (int i = 0; i <blockedAccounts.length; i++) {
                newArray[i] = blockedAccounts[i];
            }
            newArray[blockedAccounts.length] = account;
            blockedAccounts = newArray;   
        }
        else if(isLogin == false){
            System.out.println("You are not logged in");
        }  
        else if(this.isBlocked(account)){
            System.out.println("You already blocked this account.");
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
    /**
     * This method checks whether the given user has been followed.
     * @param account Account variable to be followed
     * @return boolean variable to represent followed or not
     */
    public boolean inFollowing(Account account){
        for (Account following : following) {
            if(following.equals(account)){
                return true;
            }
        }
        return false;
    }
    /**
     * This method checks whether the given user has been blocked.
     * @param account Account varible to be blocked
     * @return boolean variable to represent blocked or not.
     */
    public boolean isBlocked(Account account){
        for (Account blocked : blockedAccounts) {
            if(blocked.equals(account)){
                return true;
            }
        }
        return false;
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
        return posts[id - 1];
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
    public Post[] getPosts() {
        return posts;
    }
    /**
     * This get method returns the users followings
     * @return Account array variable to represent users followings 
     */
    public Account[] getFollowing(){
        return following;
    }
    /**
     * This get method returns the users followers
     * @return Account array variable to represent users followers 
     */
    public Account[] getFollowers(){
        return followers;
    }
    /**
     * This get method returns the users messages
     * @return Message array variable to represent users messages
     */
    public Message[] getMessages(){
        return messages;
    }
}
