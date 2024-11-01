package homework4;
/**
 * Password2 class for doing password2 operations
 * @author Barış Batuhan Bolat
 */
public class Password2 {
    /**
     * Wrapper method to check string can be written as sum of denominations.
     * @param password2 Integer variable to represent password2
     * @param denominations int[] variable to holds denominations
     * @param error String[] variable to hold error messages(Holds only one string)
     * @return true if password2 can be write by summing denominations with constant coefficients
     */
    public boolean isExactDivision(int password2, int[] denominations,String[] error){
        if(password2<10 || password2>1000){
            error[0] = "The password2 is invalid. Password must be between 10 and 10000";
            return false;
        }
        return isExactDivisionHelper(password2, denominations, 0,error);
    }
    /**
     * Checks password2 if it can be written by summation of denominations.
     * <p>
     * Time complexity = O(2^n)
     * @param password2 Integer variable to represent password2
     * @param denominations int[] variable to holds denominations
     * @param index int variable to track denominations
     * @param error String[] variable to hold error messages(Holds only one string)
     * @return true if password2 can be write by summing denominations with constant coefficients
     */
    private boolean isExactDivisionHelper(int password2, int[] denominations,int index,String[] error) {
        if (password2 == 0) {
            return true;
        }
        if (password2 < 0 || index == denominations.length) {
            error[0] = "The password2 is invalid. It is not compatible with the denominations.";
            return false;
        }
        return isExactDivisionHelper(password2 - denominations[index], denominations, index,error) || 
                isExactDivisionHelper(password2, denominations, index + 1,error);
    }
}