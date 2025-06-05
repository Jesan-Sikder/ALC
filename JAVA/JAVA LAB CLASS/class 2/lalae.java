import java. util . Scanner;

public class lalae {
    public static void main(String []args) {
        Scanner input  = new Scanner (System.in);
     System.out.printf("Enter three numbers : \n");

  int number1  = input.nextInt();
  

  
  if(number1>=90 ){
     System.out.printf("Grade A\n");
  
  }
  else if(number1>=75){
    System.out.printf("Grade B\n");

  }
  else if(number1>=50){
    System.out.printf("Grade C\n");

  }
  else {
    System.out.printf("Grade F\n");

  }
  
       }
}
