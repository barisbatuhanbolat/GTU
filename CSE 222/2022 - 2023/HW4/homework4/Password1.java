package homework4;
import java.util.Stack;
/**
 * Password1 class for doing password1 operations
 * @author Barış Batuhan Bolat
 */
public class Password1 {
        
    /**
     * Stack method to check if password1 contains username letters
     * <p>
     * Time complexity is O(n*m). Where n is the length of password and m is the length of the username.
     * @param username String variable to represent username
     * @param password1 String variable to represent password1
     * @param error String[] variable to hold error messages(Holds only one string)
     * @return true if password1 contains username letters
     */
    public boolean containsUserNameSpirit(String username, String password1,String[] error){
        if(username.length() == 0){
            error[0] = "The username is invalid. It should have at least 1 character.";
            return false;
        }
        if(password1.length() == 0){
            error[0] = "The password1 is invalid. It should have at least 1 character.";
            return false;
        }
        if(!password1.contains("{") && !password1.contains("(") && !password1.contains("[")){
            error[0] = "The password1 is invalid. It should have at least 2 brackets.";
            return false;
        }
        Stack<Character> password = new Stack<Character>();

        for(int i = 0; i<password1.length();i++){
            password.push(password1.charAt(i));
        }
        
        int i = 0;
        while(i < password.size()){
            for(int j = 0; j<username.length();j++){
                if(password.peek() == username.charAt(j)){
                    return true;
                }
            }
            password.pop();
            i++;
        }
        error[0] = "The password1 is invalid. It should have at least 1 character from the username.";
        return false;
    }
    /**
     * Stack method to check if password1 is balanced with paranthesis
     * <p>
     * Time Complexity = O(n)
     * @param password1 String variable to represent password1
     * @param error String[] variable to hold error messages(Holds only one string)
     * @return true if password1 is balanced with paranthesis 
     */
    public boolean isBalancedPassword(String password1,String[] error){
        
        password1 = password1.replaceAll("[a-zA-Z]", "");
        Stack<Character> password = new Stack<Character>();

        for (int i = 0; i < password1.length(); i++) {
            char ch = password1.charAt(i);

            if (ch == '(' || ch == '{' || ch == '[') {
                password.push(ch);
            }

            else if (ch == ')' || ch == '}' || ch == ']') {
                if (password.isEmpty()) {
                    error[0] = "The password1 is invalid. It should be balanced.";
                    return false;
                }
                char top = password.pop();
                if ((ch == ')' && top != '(') || (ch == '}' && top != '{') || (ch == ']' && top != '[')) {
                    error[0] = "The password1 is invalid. It should be balanced.";
                    return false;
                }
            }
        }
        return password.isEmpty();
    }
    /**
     * Wrapper method to check string can be written as palindrome.
     * @param password1 String variable to represent password1
     * @param error String[] variable to hold error messages(Holds only one string)
     * @return true if password1 can be written as palindrome
     */
    public boolean isPalindromePossible(String password1,String[] error) {
        
        if(password1.length()<8){
            error[0] = "The password1 is invalid. It should have at least 8 characters.";
            return false;
        }
        String password = password1.replaceAll("[^a-zA-Z]", "");
        return isPalindromePossibleHelper(password,error);
    }
    /**
     * Helper recursive method to determine password1 can be written as palindrome
     * <p>
     * Time complexity = O(n^2)
     * @param password String variable to represent password1
     * @param error String[] variable to hold error messages(Holds only one string)
     * @return true if password1 can be written as palindrome
     */
    private boolean isPalindromePossibleHelper(String password,String[] error) {
        if (password.length() <= 1) {
            return true;
        }
        
        char ch = password.charAt(0);
        int last = password.lastIndexOf(ch);
        
        if (last == 0) {
            error[0] = "The password1 is invalid. It should be possible to obtain a palindrome from the password1.";
            return false;
        }
        
        String remaining = password.substring(1, last) + password.substring(last + 1);
        return isPalindromePossibleHelper(remaining,error);
    }
}
