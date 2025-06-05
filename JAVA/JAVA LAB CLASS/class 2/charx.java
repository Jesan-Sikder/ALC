import java. util . Scanner;
public class charx {
    public static void main(String []args) {
        Scanner input = new Scanner (System.in);
        char one  = input.next().charAt(1);
        System.out.printf("The char is  = %c\n",one);
        String word = input.next();
        System.out.printf("The word is = %s\n",word);
        input.nextLine();
        
        String sentence  = input.nextLine();
        System.out.printf("The Sentence is = %s\n",sentence);


     }
}
