import java.util.Scanner;

public class e6 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
    
        int num;
        System.out.printf("Enter two numbers : ");

        int a = input.nextInt();
        int b = input.nextInt();

        System.out.printf("Choose operation(+,-,*,/) : ");

        char wow = input.next().charAt(0);

        

        

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