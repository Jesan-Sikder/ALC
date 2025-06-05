import java.util.Scanner;

public class multi {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        System.out.printf("Enter number : \n");
int sum =0;
        int number = input.nextInt();
        for(int i =1; i<=10 ;i++){
        System.out.printf("%d * %d  =  %d\n",number ,i,number*i);
            
        }
       
}
}