package homework4;
/**
 * Driver class for
 * @author Barış Batuhan Bolat
 */
public class MuseumSecurity{
    public static void LoginSystem(String username,String password1,int password2){
        System.out.println("username: '"+username+"' - password1: '"+password1+"' - password2: '"+password2+"'");
        int [] denominations = {4,17,29};
        String[] error = new String[1];
        error[0] = "";

        Username usernameControl = new Username();
        Password1 password1Control = new Password1();
        Password2 password2Control = new Password2();

        boolean control1 = usernameControl.checkIfValidUsername(username, error);
        if(control1){
            boolean control2 = password1Control.containsUserNameSpirit(username, password1, error);
            if(control2){
               boolean control3 = password1Control.isBalancedPassword(password1, error);
               if(control3){
                    boolean control4 = password1Control.isPalindromePossible(password1, error);
                    if(control4){
                        boolean control5 = password2Control.isExactDivision(password2, denominations, error);
                        if(control5){
                            System.out.println("The username and passwords are valid. The door is opening, please wait..");
                        }
                        else{
                            System.out.println(error[0]);
                        }
                    }
                    else{
                        System.out.println(error[0]);
                    }
                }
                else{
                    System.out.println(error[0]);
                }
            }
            else{
                System.out.println(error[0]);
            }
        }
        else{
            System.out.println(error[0]);
        }
    }
    
    public static void main(String args[]){
        System.out.println("Test 1");
        LoginSystem("sibelgulmez", "[rac()ecar]", 74);

        System.out.println("Test 2");
        LoginSystem("", "[rac()ecar]", 74);

        System.out.println("Test 3");
        LoginSystem("sibel1", "[rac()ecar]", 74);

        System.out.println("Test 4");
        LoginSystem("sibel", "pass[]", 74);

        System.out.println("Test 5");
        LoginSystem("sibel", "abcdabcd", 74);

        System.out.println("Test 6");
        LoginSystem("sibel", "[[[[]]]]", 74);

        System.out.println("Test 7");
        LoginSystem("sibel", "[no](no)", 74);

        System.out.println("Test 8");
        LoginSystem("sibel", "[rac()ecar]]", 74);

        System.out.println("Test 9");
        LoginSystem("sibel", "[rac()ecars]", 74);  

        System.out.println("Test 10");
        LoginSystem("sibel", "[rac()ecar]", 5);

        System.out.println("Test 11");
        LoginSystem("sibel", "[rac()ecar]", 35);    

    }
}
