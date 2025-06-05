import java.util.Scanner;

public class lala {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        System.out.printf("Enter three numbers : \n");

        int number1 = input.nextInt();
        int number2 = input.nextInt();

        int number3 = input.nextInt();

        if (number1 > number2) {
            if (number1 > number3) {
                System.out.printf("The largest number is %d\n", number1);

            }
        } else if (number2 > number1 && number2 > number3) {
            if (number2 > number3) {
                System.out.printf("The largest number is %d\n", number2);

            }
        } else {
            System.out.printf("The largest number is %d\n", number3);

        }

    }
}
