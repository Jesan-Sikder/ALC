import java.util.Scanner;

public class string {

    /****************************************************************/
    public static void println(Object o) {
        System.out.println(o);  
    }
    public static void print(Object o) {
      System.out.print(o);  
  }
    /****************************************************************/
  
    public static void main(String[] args) {
  
 println("Give the input here :");
  
  
char a ;
Scanner input  = new Scanner(System.in);
a= input.next().charAt(0);
System.out.printf("the char  is =%c\n",a);
String word = input.next();



System.out.printf("the word   is =%s\n",word);
input.nextLine();
String sentence  = input.nextLine();



System.out.printf("%s", sentence);












  
    }
  }

  

