package homework3_second;

public class TestClass4 {
    public static void main(String args[]){
        System.out.println("\u001B[32m"+"\n---------------------------Scenario 4---------------------------" + "\u001B[0m");
        
        Account gizemsungu = new Account(1,"gizemsungu","13.01.1993","Istanbul");
        Account sibelgulmez = new Account(2,"sibelgulmez","10.03.1995","Istanbul");
        Account gokhankaya = new Account(3,"gokhankaya","13.01.1993","Istanbul");
        Account account1 = new Account(4,"account1","01.01.2000","Istanbul");
        Account account2 = new Account(5,"account2","01.01.2000","Istanbul");
        Account account3 = new Account(6,"account3","01.01.2000","Istanbul");
        Account account4 = new Account(7,"account4","01.01.2000","Istanbul");
        Account account5 = new Account(8,"account5","01.01.2000","Istanbul");
        Account account6 = new Account(9,"account6","01.01.2000","Istanbul");
        Account account7 = new Account(10,"account7","01.01.2000","Istanbul");

        gizemsungu.Login();
        gizemsungu.followAccount(sibelgulmez);
        gizemsungu.followAccount(gokhankaya);
        gizemsungu.followAccount(account3);
        gizemsungu.followAccount(account4);

        gizemsungu.viewProfile(gizemsungu);
        
        gizemsungu.LogOut();

        sibelgulmez.Login();
        sibelgulmez.sharePost("Post 1");
        sibelgulmez.sharePost("Post 2");
        sibelgulmez.LogOut();

        gizemsungu.Login();

        gizemsungu.likePost(sibelgulmez.getPost(2));
        gizemsungu.commentPost(sibelgulmez.getPost(2), "Hello");
        
        gizemsungu.viewProfile(sibelgulmez);
        gizemsungu.viewInteractions(sibelgulmez);

        gizemsungu.unLikePost(sibelgulmez.getPost(2));
        gizemsungu.unCommentPost(sibelgulmez.getPost(2),"Hello");

        gizemsungu.viewProfile(sibelgulmez);
        gizemsungu.viewInteractions(sibelgulmez);

        gizemsungu.block(account4);

        gizemsungu.unFollowAccount(sibelgulmez);
        gizemsungu.unFollowAccount(account3);

        gizemsungu.unblock(account4);
        
        gizemsungu.viewProfile(gizemsungu);
        
        gizemsungu.viewHistory();

        gizemsungu.LogOut();
    }
}
