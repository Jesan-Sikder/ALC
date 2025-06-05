import java. util . Scanner;

public class name {
    String namex;
    char sec;
 String Hometown;
 int id;
 String sentence;
    public static void main(String []args) {
        Scanner input = new Scanner (System.in);
        System.out.println("Name : ");
        String  namex  = input.nextLine();
        // input.nextLine();

        System.out.println("Section : ");
        char sec  = input.next().charAt(0);
        input.nextLine();

        System.out.println("Home Town : ");
        String Hometown   = input.nextLine();
        // input.nextLine();

        System.out.println("ID : ");
        int id   = input.nextInt();
        input.nextLine();

        System.out.println("Sentence : ");
        String sentence= input.nextLine();


        System.out.printf("Name  = %s\n",namex);

        System.out.printf("Section  = %c\n",sec);
        
        System.out.printf("Home Town  = %s\n",Hometown);
        
        System.out.printf("ID  = %d\n",id);

        System.out.printf("Sentence  = %s\n",sentence);

     }
}

