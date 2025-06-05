import java.util.Scanner;
public class nig {
    /****************************************************************/
    public static void println(Object o) {
        System.out.println(o);  
    }
    public static void print(Object o) {
      System.out.print(o);  
  }
    /****************************************************************/
  
    public static void main(String[] args) {
  
 println("Give the input( number ) here :");
  
  Scanner input  = new Scanner(System.in);
  int x,y;
  x = input.nextInt();
  
  System.out.printf("The number is = "+x);
  System.out.printf("\n");
  
  if(x%2==0){
     println("Even");
  }
  else{
    println("ODD");
  }
  
  
  
  
  
    }
  }
  