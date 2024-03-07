import java.io.*;
import java.net.*;

public class Client {
    public static void main(String[] args) {
        final String serverAddress = "127.0.0.1"; 
        final int serverPort = 8080; 

        try {
            // Establecer conexión con el servidor
            Socket socket = new Socket(serverAddress, serverPort);
            System.out.println("Conectado al servidor");

        
            BufferedReader input = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintWriter output = new PrintWriter(socket.getOutputStream(), true);
            BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

            while (true) {
                // la consola lee el numero ingresado
                System.out.print("Ingrese un número entero (0 para salir): ");
                int num = Integer.parseInt(reader.readLine());
                
                // se envia el numero al servidor
                output.println(num);
                
                // si el numero es igual a 0 sale del bucle
                if (num == 0) {
                    break;
                }
                
                // recibe la respuesta del servidor
                String response = input.readLine();
                System.out.println("Servidor responde: " + response);
            }

            // cierra el socket
            socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
