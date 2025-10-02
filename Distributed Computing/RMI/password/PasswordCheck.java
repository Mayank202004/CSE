import java.rmi.Remote;
import java.rmi.RemoteException;

public interface PasswordCheck extends Remote {
    String checkPassword(String password) throws RemoteException;
}

