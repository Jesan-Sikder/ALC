import java.util.Scanner;

public class calc {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
    
        int num;
        System.out.printf("Enter first  numbers : \n");

        int a = input.nextInt();
        System.out.printf("Enter arithmetic operation  : \n");

        char wow = input.next().charAt(0);

        System.out.printf("Enter second  numbers : \n");

        int b = input.nextInt();
        

        switch (wow) {
            case '+':

                System.out.printf("Result = %d\n", a + b);
                break;
            case '-':

            System.out.printf("Result = %d\n", a - b);

                break;
            case '*':

            System.out.printf("Result =  %d\n", a * b);

                break;
            case '/':

            System.out.printf("Result =  %d\n", a / b);
                break;
        }
    }
}