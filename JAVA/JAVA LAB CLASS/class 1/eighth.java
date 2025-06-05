import java.util.Scanner;

public class eighth {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Principal: ");
        int principal = sc.nextInt();
        System.out.print("Rate: ");

        int rate = sc.nextInt();
        System.out.print("Time: ");

        int time = sc.nextInt();
        float si = (principal * rate * time) / 100;

        System.out.println("Simple Interest : " + si);
    }
}
