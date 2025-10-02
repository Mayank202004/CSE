import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.rmi.registry.Registry;
import java.rmi.registry.LocateRegistry;

public class PasswordCheckImpl extends UnicastRemoteObject implements PasswordCheck {

    private static final String CORRECT_PASSWORD = "open123";

    protected PasswordCheckImpl() throws RemoteException {
        super();
    }

    @Override
    public String checkPassword(String password) throws RemoteException {
        
        if (CORRECT_PASSWORD.equals(password)) {
            System.out.println("[Server] : Received " + password + " -> Password Matched");
            return "Welcome! Password is correct.";
        } else {
        System.out.println("[Server] : Received " + password + " -> Password Did Not Match");
            return null; 
        }
    }

    public static void main(String[] args) {
        try {
            LocateRegistry.createRegistry(1099);
            PasswordCheckImpl obj = new PasswordCheckImpl();
            Registry registry = LocateRegistry.getRegistry();
            registry.rebind("PasswordCheckService", obj);

            System.out.println("PasswordCheck RMI Server is running...");
        } catch (Exception e) {
            System.err.println("Server exception: " + e.getMessage());
            e.printStackTrace();
        }
    }
}

