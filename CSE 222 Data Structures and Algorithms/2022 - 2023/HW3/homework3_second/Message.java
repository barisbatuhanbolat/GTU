package homework3_second;
/**
 * Message class for keeping message details
 * @author Barış Batuhan Bolat
 */
public class Message {
    private final int messageID;
    private Account sender;
    private Account receiver;
    private String content;
    /**
     * Default constructor for Message class.
     * <p>
     * This constructor calls other constructor with invalid parameters.
     */
    public Message(){
        this(0,null,null,"");
    }
    /**
     * Constructor for Message class
     * @param ID Uniqe integer variable for identify Message object
     * @param sender Account variable to identify sender user
     * @param receiver Account variable to identify receiver user
     * @param content String variable to identify message content
     */
    public Message(int ID,Account sender,Account receiver,String content){
        this.messageID = ID;
        this.sender = sender;
        this.receiver = receiver;
        this.content = content;
    }
    /**
     * Get method for messageID
     * @return integer variable to identify messageID
     */
    public int getID(){
        return messageID;
    }
    /**
     * Get method for sender
     * @return Account variable to identify who send message
     */  
    public Account getSender(){
        return sender;
    }
    /**
     * Get method for receiver
     * @return Account variable to identify who receive message
     */    
    public Account getReceiver(){
        return receiver;
    }
    /**
     * Get method for content
     * @return String variable to identify message content
     */    
    public String getContent(){
        return content;
    }
}
