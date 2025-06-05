// import java.util.Scanner;

// public class fui {
//     public static void main(String[] args) {
//         Scanner input = new Scanner(System.in);
//         System.out.printf("Enter number : \n");

//         int number = input.nextInt();
//         for(int i =0; i<number ;i++){
//             System.out.printf("Hello jesan\n");
//         }
       
// }
// }
import java.util.Scanner;

public class fui {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        System.out.printf("Enter number : \n");
int sum =0;
        int number = input.nextInt();
        for(int i =1; i<=number ;i++){
            sum+=i;
        }
        System.out.printf("%d\n",sum);
       
}
}