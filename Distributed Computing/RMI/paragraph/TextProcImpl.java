import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.rmi.registry.Registry;
import java.rmi.registry.LocateRegistry;

public class TextProcImpl extends UnicastRemoteObject implements TextProc {

    protected TextProcImpl() throws RemoteException {
        super();
    }

    @Override
    public String analyzeText(String paragraph) throws RemoteException {
        System.out.println("[Server] : Received request from client.");
        int charCount = paragraph.length();
        int wordCount = paragraph.trim().isEmpty() ? 0 : paragraph.trim().split("\\s+").length;
        int lineCount = paragraph.split("\r\n|\r|\n").length;

        return "Characters: " + charCount +
               "\nWords: " + wordCount +
               "\nLines: " + lineCount;
    }

    public static void main(String[] args) {
        try {
            // Start RMI registry
            LocateRegistry.createRegistry(1099);

            // Create instance and bind it
            TextProcImpl obj = new TextProcImpl();
            Registry registry = LocateRegistry.getRegistry();
            registry.rebind("TextProcService", obj);

            System.out.println("TextProc RMI Server is running...");
        } catch (Exception e) {
            System.err.println("Server exception: " + e.getMessage());
            e.printStackTrace();
        }
    }
}

