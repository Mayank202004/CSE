import java.rmi.Naming;

public class RMIClient {
    public static void main(String[] args) {
        try {
            // Look up the remote object from the RMI registry
            ServerInterface server = (ServerInterface) Naming.lookup("rmi://localhost/Server");

            // Call remote methods
            System.out.println("Current Date and Time: " + server.getCurrentDateTime());
            System.out.println("Current Year: " + server.getCurrentYear());
            System.out.println("System Information: ");
            System.out.println(server.getSystemInfo());
        } catch (Exception e) {
            System.out.println("Client exception: " + e.getMessage());
            e.printStackTrace();
        }
    }
}

