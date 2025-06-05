import java.util.Scanner;

public class e3 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter three numbers: ");
        int a = sc.nextInt(), b = sc.nextInt(), c = sc.nextInt();

        if (a >= b && a >= c)
            System.out.println("The largest number is " + a);
        else if (b >= a && b >= c)
            System.out.println("The largest number is " + b);
        else
            System.out.println("The largest number is " + c);
    }
}
