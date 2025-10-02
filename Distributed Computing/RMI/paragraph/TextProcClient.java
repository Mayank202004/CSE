import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.Scanner;

public class TextProcClient {

    public static void main(String[] args) {
        try {
            // Connect to RMI registry on localhost
            Registry registry = LocateRegistry.getRegistry("localhost");

            // Lookup the remote object
            TextProc stub = (TextProc) registry.lookup("TextProcService");

            // Take input from the user
            Scanner scanner = new Scanner(System.in);
            System.out.println("Enter a paragraph (end input with an empty line):");

            StringBuilder paragraphBuilder = new StringBuilder();
            while (true) {
                String line = scanner.nextLine();
                if (line.isEmpty()) {
                    break; // Stop input on empty line
                }
                paragraphBuilder.append(line).append("\n");
            }
            scanner.close();

            String paragraph = paragraphBuilder.toString();

            // Remote call
            String result = stub.analyzeText(paragraph);

            System.out.println("\nServer response:\n" + result);

        } catch (Exception e) {
            System.err.println("Client exception: " + e.getMessage());
            e.printStackTrace();
        }
    }
}

