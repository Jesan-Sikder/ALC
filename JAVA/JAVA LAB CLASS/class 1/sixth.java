import java.util.Scanner;

public class sixth {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Before Swap: ");
        int a = sc.nextInt();
        int b = sc.nextInt();

        System.out.println("After Swap: ");
        int s = a;
        a = b;
        b = s;
        System.out.println("After Swap: a = " + a + ", b = " + b);

    }
}
