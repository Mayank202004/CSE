import java.rmi.Remote;
import java.rmi.RemoteException;

public interface TextProc extends Remote {
    String analyzeText(String paragraph) throws RemoteException;
}

