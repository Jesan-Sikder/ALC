public class car {
    private String make;
    private String model;
    private int year;

    public void start() {
        System.out.println("starting bruhhh");
    }

    public void stop() {
        System.out.println("stop...");
    }

    public void drive(int speed) {
        System.out.printf("cars speed is  %d", speed);
    }

    public static void main(String[] args) {

        car jcar = new car();
        jcar.make = "audi";
        jcar.model = "audi";

        jcar.year = 2025;
        System.out.printf("%s\n", jcar.make);
        System.out.printf("%s\n", jcar.model);

        System.out.printf("%d\n", jcar.year);

        jcar.start();
        jcar.drive(150);
        jcar.stop();
    }
}
