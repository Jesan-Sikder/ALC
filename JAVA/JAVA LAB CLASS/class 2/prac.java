import java. util . Scanner;

public class prac {
    public static void main(String []args) {
        Scanner input  = new Scanner (System.in);
  int number  = input.nextInt();
  if(number==0){
     System.out.println("The number is Zero ");
  
  }
  else if(number>0){
     System.out.printf("%d number is Positive \n",number);
  }
  else{
    System.out.printf("%d number is Negative \n",number);
    
  }
  
       }
}
