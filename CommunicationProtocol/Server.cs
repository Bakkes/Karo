using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Runtime.Serialization.Formatters.Binary;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace CommunicationProtocol
{
    /// <summary>
    /// Server implementatie
    /// </summary>
    public class Server : ICommunication
    {
        private Server server;
        private TcpListener _listener { get; set; }
        /// <summary>
        /// Constructor van server instantie. De instantie start een thread om te luisteren naar tcp connecties
        /// </summary>
        /// <param name="port">poort waarop de client kan verbinden</param>
        public Server(int port)
        {
            if (server == null)
            {
                server = this;
                _port = port;
                _listener = new TcpListener(IPAddress.Any, port);
                _listenThread = new Thread(new ThreadStart(StartCommunicating));
                _listenThread.Start();
            }
        }
        public override void StartCommunicating()
        {
            _listener.Start();
            _client = _listener.AcceptTcpClient();
            if (_client.Connected)
            {
                OnConnected();
            }
            if (_client.Connected)
            {
                Message connectedMessage = new Message();
                connectedMessage.Type = MessageType.Connected;
                SendMessage(connectedMessage);
                
                Random r = new Random();
                double x = r.NextDouble();
                Console.Write("Diceroll: " + x);
				SendRequestFirstMove();
				/*
                if (x >= 0.5)
                {
                    Console.Write(" server starts\n");
                    OnRequestFirstMove();
                }
                else
                {
                    Console.Write(" client starts\n");
                    SendRequestFirstMove();
                }*/
            }
            DoCommunication();
            _listener.Stop();
        }
        /// <summary>
        /// Methode om connectie op te ruimen.
        /// </summary>
        public override void CleanUp()
        {
            if (_listener != null)
            {
                _listener.Stop();
                _listener = null;
            }
            if (_client != null)
            {
                _client.Close();
                _client = null;
            }
        }
    }
}
