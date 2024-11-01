package homework3_third;


public class TestClass1 {
    public static void main(String args[]){
        System.out.println("\n---------------------------Scenario 1---------------------------");

        Account gizemsungu = new Account(1,"gizemsungu","13.01.1993","Istanbul");

        Account sibelgulmez = new Account(2,"sibelgulmez","10.03.1995","Istanbul");

        Account gokhankaya = new Account(3,"gokhankaya","13.01.1993","Istanbul");

        sibelgulmez.Login();

        sibelgulmez.sharePost("I like Java.");
        sibelgulmez.sharePost("Java the coffee...");

        sibelgulmez.followAccount(gizemsungu);
        sibelgulmez.followAccount(gokhankaya);


        sibelgulmez.LogOut();

        gokhankaya.Login();
        gokhankaya.viewProfile(sibelgulmez);

        gokhankaya.viewPosts(sibelgulmez);

        gokhankaya.likePost(sibelgulmez.getPost(1));
        gokhankaya.commentPost(sibelgulmez.getPost(1), "Me too");

        gokhankaya.followAccount(sibelgulmez);
        gokhankaya.followAccount(gizemsungu);

        gokhankaya.sendMessage(gizemsungu,"This homework is too easy !");

        gokhankaya.LogOut();

        gizemsungu.Login();

        gizemsungu.checkOutbox();
        gizemsungu.checkInbox();

        gizemsungu.viewInbox();

        gizemsungu.viewProfile(sibelgulmez);
        
        gizemsungu.viewPosts(sibelgulmez);
        gizemsungu.viewInteractions(sibelgulmez);

        gizemsungu.likePost(sibelgulmez.getPost(1));
        gizemsungu.likePost(sibelgulmez.getPost(2));

        gizemsungu.viewInteractions(sibelgulmez);
        
    }
}
