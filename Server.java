import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class Servidor {

    public static void main(String[] args) {
        final int PUERTO = 12345; // Puerto definido como 12345

        try {
            // Se crea un ServerSocket que estará escuchando conexiones en el puerto 12345
            ServerSocket serverSocket = new ServerSocket(PUERTO);
            System.out.println("Servidor esperando conexiones...");

            // Espera para algun cliente se conecte
            Socket socket = serverSocket.accept();
            System.out.println("Cliente conectado desde: " + socket.getInetAddress());

            // Se establecen los flujos de entrada y salida para comunicarse con el cliente
            BufferedReader entrada = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintWriter salida = new PrintWriter(socket.getOutputStream(), true);

            // Se lee el mensaje del cliente
            String mensajeCliente = entrada.readLine();
            System.out.println("Mensaje recibido del cliente: " + mensajeCliente);

            // Se envia mensaje al cliente
            salida.println("Hola que tal");

            // Se cierra el socket y el server
            socket.close();
            serverSocket.close();
        } catch (IOException e) {
            // En caso de error, se imprime la traza del error
            e.printStackTrace();
        }
    }
}
