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
	public delegate void ConnectionFailed();
    /// <summary>
    /// Client implementatie
    /// </summary>
    public class Client : ICommunication
    {
        private Client client;
        private IPAddress _ip;
        private Thread _communicationThread;
		public ConnectionFailed OnConnectionFailed;
        /// <summary>
        /// Constructor van de client. Deze verbind met de server en start de communicatie in een apart thread.
        /// </summary>
        /// <param name="target">Ip adres van de server</param>
        /// <param name="port">Poort van de server</param>
        public Client(IPAddress target, int port)
        {
            if (client == null)
            {
                client = this;
                _ip = target;
                _port = port;
            }
        }
        /// <summary>
        /// Methode om connectie op te ruimen.
        /// </summary>
        public override void CleanUp()
        {
            if (_client != null)
            {
                _client.Close();
                _client = null;
            }
        }
        public override void StartCommunicating()
        {
			_communicationThread = new Thread(new ThreadStart(Connect));
			_communicationThread.Start();
        }

		private void Connect()
		{
			_client = new TcpClient();
			try
			{
				_client.Connect(_ip, _port);
			}
			catch (SocketException se)
			{
				if (OnConnectionFailed != null)
					OnConnectionFailed();
			}
			DoCommunication();
		}
    }
}
