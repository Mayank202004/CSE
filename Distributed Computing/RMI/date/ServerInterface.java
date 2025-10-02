import java.rmi.Remote;
import java.rmi.RemoteException;

public interface ServerInterface extends Remote {
    String getCurrentDateTime() throws RemoteException;
    int getCurrentYear() throws RemoteException;
    String getSystemInfo() throws RemoteException;
}

