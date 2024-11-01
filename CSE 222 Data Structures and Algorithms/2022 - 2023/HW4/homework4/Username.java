package homework4;
/**
 * Username class for doing username operations
 * @author Barış Batuhan Bolat
 */
public class Username {
    /**
     * Recursive method to check if the username contains only letters
     * <p>
     * Time Complexity = O(n)
     * @param username String variable to represent username
     * @param error String[] variable to hold error messages(Holds only one string)
     * @return true if it contains only letters
     */
    public boolean checkIfValidUsername(String username,String[] error){
        if(username.length() == 0){
            error[0] = "The username is invalid. It should have at least 1 character.";
            return false;
        }
        if(!Character.isLetter(username.charAt(0))){
            error[0] = "The username is invalid. It should have letters only.";
            return false;
        }
        if (username.length() == 1) {
            return true;
        }
        return checkIfValidUsername(username.substring(1),error);
    }
}
