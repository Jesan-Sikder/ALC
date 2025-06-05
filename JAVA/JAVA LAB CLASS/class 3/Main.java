
class Main{
    int age;
    int gender ;
    public void  ismamal(){
        System.err.println("this is a mamal");
    }
    public void friend(){
        System.err.println("this is a friendly mamal");

    }
    public static void main(String[] agrs){
        Main dog = new Main();
        dog.age = 10;
        dog.gender = 0;
        System.out.printf("this animal age is = %d\n",dog.age);
        System.out.printf("this animal age is = %d\n",dog.gender);
        dog.ismamal();
        dog.friend();

    }
}