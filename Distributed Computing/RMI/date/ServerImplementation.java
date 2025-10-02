import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.Date;

public class ServerImplementation extends UnicastRemoteObject implements ServerInterface {

    public ServerImplementation() throws RemoteException {
        super();
    }

    @Override
    public String getCurrentDateTime() throws RemoteException {
        System.out.println("[Server] : Received request for current date and time");
        return new Date().toString();
    }

    @Override
    public int getCurrentYear() throws RemoteException {
        System.out.println("[Server] : Received Request for year");
        return new Date().getYear() + 1900;  // getYear() returns years since 1900
    }

    @Override
    public String getSystemInfo() throws RemoteException {
        System.out.println("[Server] : Received Request for system info");
        return "OS: " + System.getProperty("os.name") + "\n" +
               "Version: " + System.getProperty("os.version") + "\n" +
               "Architecture: " + System.getProperty("os.arch");
    }
}

