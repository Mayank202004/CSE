import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.Scanner;

public class PasswordCheckClient {

    public static void main(String[] args) {
        try {
            Registry registry = LocateRegistry.getRegistry("localhost");
            PasswordCheck stub = (PasswordCheck) registry.lookup("PasswordCheckService");

            Scanner scanner = new Scanner(System.in);
            String response;

            while (true) {
                System.out.print("Enter password: ");
                String input = scanner.nextLine();

                response = stub.checkPassword(input);
                if (response != null) {
                    System.out.println(response);
                    break;
                } else {
                    System.out.println("Incorrect password. Try again.");
                }
            }

            scanner.close();

        } catch (Exception e) {
            System.err.println("Client exception: " + e.getMessage());
            e.printStackTrace();
        }
    }
}

