import java.util.Scanner;
public class yo {
    /****************************************************************/
    public static void println(Object o) {
        System.out.println(o);  
    }
    public static void print(Object o) {
      System.out.print(o);  
  }
    /****************************************************************/
  
    public static void main(String[] args) {
  
  
  Scanner input  = new Scanner(System.in);
  float x,y;
  x = input.nextFloat();
  y = input.nextFloat();

  
//   Scanner input  = new Scanner(System.in);
  
//  boolean a;
//   a= input .nextFloat();
  System.out.printf("Addition : "+(x+y));
  println(" ");
  System.out.printf("Subtraction : "+(x-y));
  println(" ");

  System.out.printf("Multiplication : "+(x*y));
  println(" ");

//   System.out.printf("Division : "+(x/y));
  System.out.printf("Division : %.1f\n",(x/y));

//   float x,y;
//   x = input.nextFloat();
//   y = input.nextFloat();

//   System.out.printf("Addition : "+(x+y));
//   println(" ");
//   System.out.printf("Subtraction : "+(x-y));
//   println(" ");

//   System.out.printf("Multiplication : "+(x*y));
//   println(" ");

//   System.out.printf("Division : "+(x/y));
//   System.out.printf("Division : %f\n",(x/y));

  
  
  
  
  
  
  
    }
  }
  