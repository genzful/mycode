import socket
import sys
import subprocess
import os

class CommandServer:
    def __init__(self, port):
        self.HOST = "127.0.0.1";
        self.PORT = int(port);
        self.s = None;
        self._initialize_socket();
        
    def _initialize_socket(self):
        self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM);
        self.s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1);
        self.s.bind((self.HOST, self.PORT));
        self.s.listen();
        
    def handle_client(self, conn, addr):
        try:
            print(f"Connected! {addr}");
            startmsg = b"wussup bro, send me a msg, I'll execute it\n";
            conn.send(startmsg);
            
            while True:
                try:
                    data = conn.recv(4096);
                    if not data:
                        print(f"{addr} disconnected");
                        break;

                    command = data.decode('utf-8', errors='ignore').strip();

                    if not command:
                        conn.send(b"error of command\n");
                        continue;

                    if command.lower() in ['exit', 'quit', 'q']:
                        conn.send(b"Goodbye!\n");
                        print(f"Client {addr} requested exit");
                        break;
                    
                    print(f"executing command from {addr}: {command}");
                    
                    try:
                        process = subprocess.Popen(
                            command,
                            shell=True,
                            stdout=subprocess.PIPE,
                            stderr=subprocess.PIPE,
                            text=True
                        );

                        stdout, stderr = process.communicate(timeout=30);

                        result = "";
                        if stdout:
                            result += stdout;
                        if stderr:
                            result += f"error:\n{stderr}";
                        if not stdout and not stderr:
                            result = f"idk bro {process.returncode})";

                        conn.sendall(result.encode('utf-8'));
                        
                    except subprocess.TimeoutExpired:
                        conn.send(b"error: command execution timed out\n");
                        process.kill();
                        
                    except Exception as e:
                        error_msg = f"error: {str(e)}\n";
                        conn.send(error_msg.encode('utf-8'));
                        
                except socket.error:
                    print(f"connection lost {addr}");
                    break;
                except Exception as e:
                    print(f"error: {e}");
                    conn.send(f"serv error: {str(e)}\n".encode('utf-8'));
                    
        finally:
            conn.close();
            
    def run(self):
        print(f"Server listening on {self.HOST}:{self.PORT}");
        
        while True:
            try:
                conn, addr = self.s.accept();
                self.handle_client(conn, addr);
            except KeyboardInterrupt:
                break;
            except Exception as e:
                print(f"error: {e}");
                continue;
            
def main(port):
    server = CommandServer(port);
    server.run();
    
if __name__ == "__main__":
    if len(sys.argv) != 2:
        print(f"Usage: {sys.argv[0]} <port>");
        sys.exit(1);
    
    try:
        main(sys.argv[1]);
    except KeyboardInterrupt:
        pass;
    except Exception as e:
        print(f"error: {e}");