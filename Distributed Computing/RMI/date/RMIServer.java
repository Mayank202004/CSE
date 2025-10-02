import java.rmi.Naming;
import java.rmi.registry.LocateRegistry;

public class RMIServer {
    public static void main(String[] args) {
        try {
            // Create and export the remote object
            ServerImplementation server = new ServerImplementation();

            // Start the RMI registry on port 1099 (default)
            LocateRegistry.createRegistry(1099);

            // Bind the object to the RMI registry
            Naming.rebind("rmi://localhost/Server", server);

            System.out.println("Server is running and ready to accept client requests...");
        } catch (Exception e) {
            System.out.println("Server exception: " + e.getMessage());
            e.printStackTrace();
        }
    }
}

