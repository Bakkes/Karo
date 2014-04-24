using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net.Sockets;
using System.Runtime.Serialization.Formatters.Binary;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace CommunicationProtocol
{
    /// <summary>
    /// ICommunication bevat gedeelde functionaliteit van de Client/Server klassen.
    /// </summary>
    public abstract class ICommunication
    {
        internal int _port;
        internal TcpClient _client;
        internal Thread _listenThread;

        //delegates
        /// <summary>
        /// Delegate voor connected event
        /// </summary>
        public delegate void ConnectedHandler();
        /// <summary>
        /// Delegate voro Disconnected event
        /// </summary>
        /// <param name="reason">Disconnect reden</param>
        public delegate void DisconnectedHandler(DisconnectReason reason);
        /// <summary>
        /// Delegate voor SentInvalidMove event
        /// </summary>
        /// <param name="t">Invalide zet</param>
        public delegate void SentMoveInvalidHandler(Turn t);
        /// <summary>
        /// Delgate voro WinRejected event
        /// </summary>
        public delegate void WinRejectedHandler();
        /// <summary>
        /// Delgate voor WinAccepted event
        /// </summary>
        public delegate void WinAcceptedHandler();
        /// <summary>
        /// Delgate voor WinDetected event
        /// </summary>
        /// <param name="t">Winnende zet</param>
        /// <param name="p">Winnende speler</param>
        public delegate void WinDetectedHandler(Turn t, Player p);
        /// <summary>
        /// Delgate voor TurnReceived event
        /// </summary>
        /// <param name="t">Zet</param>
        public delegate void TurnReceivedHandler(Turn t);
        /// <summary>
        /// Delgate voor RequestFirstMove event
        /// </summary>
        public delegate void RequestFirstMoveHandler();
        
        //events
        /// <summary>
        /// Event wordt gegooid nadat Client met Server geconnect is
        /// </summary>
        public event ConnectedHandler Connected;
        /// <summary>
        /// Event wordt gegooid nadat er een disconnect plaats gevonden heeft
        /// </summary>
        public event DisconnectedHandler Disconnected;
        /// <summary>
        /// Event wordt gegooid nadat er een turn ontvangen is
        /// </summary>
        public event TurnReceivedHandler TurnReceived;
        /// <summary>
        /// Event wordt gegooid nadat andere instatie bepaald heeft dat de laatst verstuurde zet niet valide was
        /// </summary>
        public event SentMoveInvalidHandler SentMoveInvalid;
        /// <summary>
        /// Event wordt gegooid nadat de andere instantie de detectie van een winst heeft afgekeurd
        /// </summary>
        public event WinRejectedHandler WinRejected;
        /// <summary>
        /// Event wordt gegooid nadat de andere instantie de detectie van een winst heeft geaccepteerd
        /// </summary>
        public event WinAcceptedHandler WinAccepted;
        /// <summary>
        /// Event wordt gegooid nadat de andere instantie een winst heeft gedetecteerd. Deze winst kan voor beide spelers zijn. 
        /// </summary>
        public event WinDetectedHandler WinDetected;
        /// <summary>
        /// Event wordt eenmalig gegooid nadat bepaald is wie mag beginnen. Hierin wordt de eerste zet gedaan.
        /// </summary>
        public event RequestFirstMoveHandler RequestFirstMove;

        /// <summary>
        /// Abstracte methode die overschreven dient te worden door overervende klassen.
        /// In dit geval zal hierin client/server specifieke communicatie plaats vinden.
        /// </summary>
        public abstract void StartCommunicating();

        /// <summary>
        /// Abstractie methode die overschreven dient te worden door overervende klassen.
        /// Client/Server zullen hierin connecties afbreken en opruimen.
        /// </summary>
        public abstract void CleanUp();

        /// <summary>
        /// Methode om het connected event te activeren
        /// </summary>
        /// <seealso cref="Connected"/>
        internal void OnConnected()
        {
            if (Connected != null)
            {
                Connected();
            }
        }
        /// <summary>
        /// Methode om het Disconnected event te activeren
        /// </summary>
        /// <param name="reason">Reden van disconnect</param>
        /// <seealso cref="Disconnected"/>
        internal void OnDisconnected(DisconnectReason reason)
        {
            if (Disconnected != null)
            {
                Disconnected(reason);
            }
        }
        /// <summary>
        /// Methode om het TurnReceived event te activeren
        /// </summary>
        /// <param name="t">Ontvangen zet</param>
        internal void OnTurnReceived(Turn t)
        {
            if (TurnReceived != null)
            {
                TurnReceived(t);
            }
        }
        /// <summary>
        /// Methode om het SentMoveInvalid event te activeren.
        /// Dit geeft aan de de verzonden zet invalide is bevonden door de andere partij.
        /// Na dit bericht wordt een disconnect bericht verstuurd en het disconnected event van deze instantie aangeroepen.
        /// </summary>
        /// <param name="t">De invalide bevonden zet</param>
        /// <seealso cref="SentMoveInvalid"/>
        /// <seealso cref="OnDisconnected"/>
        internal void OnSentMoveInvalid(Turn t)
        {
            if (SentMoveInvalid != null)
            {
                SentMoveInvalid(t);
                DisconnectMessage dc = new DisconnectMessage();
                dc.Reason = DisconnectReason.InvalidMove;
                dc.Type = MessageType.Disconnect;
                SendMessage(dc);
                OnDisconnected(dc.Reason);
            }
        }
        /// <summary>
        /// Methode om het WinRejected event te activeren.
        /// Dit geeft aan de de gevonden winst invalide is bevonden door de andere partij.
        /// Na dit bericht wordt een disconnect bericht verstuurd en het disconnected event van deze instantie aangeroepen.
        /// </summary>
        /// <seealso cref="WinRejected"/>
        /// <seealso cref="OnDisconnected"/>
        internal void OnWinRejected()
        {
            if (WinRejected != null)
            {
                DisconnectMessage dc = new DisconnectMessage();
                dc.Reason = DisconnectReason.WinnerDisputed;
                dc.Type = MessageType.Disconnect;
                SendMessage(dc);
                WinRejected();
                OnDisconnected(dc.Reason);
            }
        }
        /// <summary>
        /// Methode om het WinAccepted event te activeren.
        /// Dit geeft aan de de gevonden winst valide is bevonden door de andere partij.
        /// Na dit bericht wordt een disconnect bericht verstuurd en het disconnected event van deze instantie aangeroepen.
        /// </summary>
        /// <seealso cref="WinAccepted"/>
        /// <seealso cref="OnDisconnected"/>
        internal void OnWinAccepted()
        {
            if (WinAccepted != null)
            {
                DisconnectMessage dc = new DisconnectMessage();
                dc.Reason = DisconnectReason.GameEnded;
                dc.Type = MessageType.Disconnect;
                SendMessage(dc);
                WinAccepted();
                OnDisconnected(dc.Reason);
            }
        }
        
        /// <summary>
        /// Methode om het WinDetected event te activeren.
        /// Dit geeft aan dat de andere partij een winst heeft gevonden na de meegegeven zet.
        /// </summary>
        /// <param name="t">De winnende zet</param>
        /// <param name="p">De winnende speler, normaal Player.Me</param>
        /// <seealso cref="Turn"/>
        /// <seealso cref="Player"/>
        internal void OnWinDetected(Turn t, Player p)
        {
            if (WinDetected != null)
            {
                WinDetected(t, p);
            }
        }
        /// <summary>
        /// Methode om het binnenkomende bericht te verwerken en het bijbehorende event te triggeren.
        /// </summary>
        /// <param name="m">Ontvangen bericht</param>
        /// <seealso cref="Message"/>
        /// <seealso cref="Proces_MessageReceived"/>
        internal void OnMessageReceived(Message m)
        {
            new Thread(() => Proces_MessageReceived(m)).Start();
        }
        /// <summary>
        /// Methode om het RequestFirstMove event te activeren.
        /// Wanneer dit event wordt aangeroepen wordt de instantie gevraagd om de eerste zet te plaatsen.
        /// De winnende speler is bepaald door de klasse server in de methode StartCommunicating()
        /// </summary>
        /// <seealso cref="RequestFirstMove"/>
        internal void OnRequestFirstMove()
        {
            if (RequestFirstMove != null)
            {
                RequestFirstMove();
            }
        }
        
        //
        /// <summary>
        /// Methode voor de afhandeling van een binnenkomend bericht, hierin wordt het bijbehorende event aangeroepen.
        /// </summary>
        /// <param name="m">Binnenkomend bericht</param>
        private void Proces_MessageReceived(Message m)
        {
            switch (m.Type)
            {
                case MessageType.Connected:
                    OnConnected();
                    break;
                case MessageType.Turn:
                    OnTurnReceived(m.Turn);
                    break;
                case MessageType.Disconnect:
                    DisconnectMessage dm = (DisconnectMessage)m;
                    OnDisconnected(dm.Reason);
                    break;
                case MessageType.SentMoveInvalid:
                    OnSentMoveInvalid(m.Turn);
                    break;
                case MessageType.WinRejected:
                    OnWinRejected();
                    break;
                case MessageType.WinDetected:
                    OnWinDetected(m.Turn, ((WinDetectedMessage)m).Winner);
                    break;
                case MessageType.WinAccepted:
                    OnWinAccepted();
                    break;
                case MessageType.RequestFirstMove:
                    OnRequestFirstMove();
                    break;
                default:
                    break;
            }
        }
        /// <summary>
        /// Stuur een bericht naar de andere game instantie
        /// 'Voor intern gebruik' 
        /// </summary>
        /// <param name="m">Bericht dat verzonden dient te worden</param>
        /// <seealso cref="OnDisconnected"/>
        internal void SendMessage(Message m)
        {
            try
            {
                BinaryFormatter bFormatter = new BinaryFormatter();
                MemoryStream ms = new MemoryStream();
                bFormatter.Serialize(ms, m);
                Byte[] data = ms.ToArray();
                NetworkStream ns = _client.GetStream();
                ns.Write(data, 0, data.Length);
            }
            catch (IOException e)
            {
                OnDisconnected(DisconnectReason.ConnectionLost);
            }
        }
        
        //Public methoden voor gebruik door game instanties
        /// <summary>
        /// Verstuur een zet naar de andere instantie.
        /// Maakt gebruik van de interne methode SendMessage()
        /// </summary>
        /// <param name="t">Een gevulde zet</param>
        /// <seealso cref="Turn"/>
        /// <seealso cref="SendMessage"/>
        public void SendTurn(Turn t)
        {
            SendMessage(t.ToMessage());
        }
        /// <summary>
        /// Verstuurt naar de andere instantie dat de ontvangen zet ongeldig is.
        /// </summary>
        /// <param name="t">De turn die als ongeldig gezien wordt</param>
        /// <seealso cref="Message"/>
        /// <seealso cref="SendMessage"/>
        public void SendMoveInvalid(Turn t)
        {
            Message m = new Message();
            m.Turn = t;
            m.Type = MessageType.SentMoveInvalid;
            SendMessage(m);
        }
        /// <summary>
        /// Verstuur naar de andere instantie dat er een winnaar gevonden is.
        /// </summary>
        /// <param name="winner">Wie er gewonnen heeft, in normale situatie verstuur je hier Player.Me</param>
        /// <param name="t">Winnende zet</param>
        /// <seealso cref="WinDetectedMessage"/>
        /// <seealso cref="Player"/>
        /// <seealso cref="SendMessage"/>
        public void SendWinDetected(Player winner, Turn t)
        {
            WinDetectedMessage m = new WinDetectedMessage();
            m.Type = MessageType.WinDetected;
            m.Winner = winner;
            m.Turn = t;
            SendMessage(m);
        }
        /// <summary>
        /// Vertuur een reactie op WinDetected dat je het eens bent met de gedetecteerde winst.
        /// </summary>
        /// <seealso cref="Message"/>
        /// <seealso cref="SendMessage"/>
        /// <seealso cref="MessageType"/>
        public void SendWinAccepted()
        {
            Message m = new Message();
            m.Type = MessageType.WinAccepted;
            SendMessage(m);
        }
        /// <summary>
        /// Verstuur een reactie op WinDetected dat er onenigheid is over de gedetecteerde winst
        /// </summary>
        /// <seealso cref="Message"/>
        /// <seealso cref="SendMessage"/>
        public void SendWinDisputed()
        {
            Message m = new Message();
            m.Type = MessageType.WinRejected;
            SendMessage(m);
        }
        /// <summary>
        /// Verstuur een aanvraag om de eerste move te doen. 
        /// Voor intern gebruik na diceroll om startende speler aan te geven.
        /// </summary>
        /// <seealso cref="Message"/>
        /// <seealso cref="SendMessage"/>
        internal void SendRequestFirstMove()
        {
            Message m = new Message();
            m.Type = MessageType.RequestFirstMove;
            SendMessage(m);
        }
        /// <summary>
        /// Verstuur dat je verbinding gaat verbreken
        /// </summary>
        /// <param name="r">Reden van verbroken verbinding</param>
        /// <seealso cref="DisconnectReason"/>
        /// <seealso cref="DisconnectMessage"/>
        public void SendDisconnect(DisconnectReason r)
        {
            DisconnectMessage m = new DisconnectMessage();
            m.Type = MessageType.Disconnect;
            m.Reason = r;
            SendMessage(m);
            OnDisconnected(r);
        }
        /// <summary>
        /// Start de communicatie om berichten af te handelen.
        /// </summary>
        /// <seealso cref="IsConnected"/>
        public void DoCommunication()
        {
            try
            {
                int i = 0;
                while (_client.Connected)
                {
                    if (_client.Available > 1)
                    {
                        BinaryFormatter bFormatter = new BinaryFormatter();
                        Message m = (Message)bFormatter.Deserialize(_client.GetStream());
                        OnMessageReceived(m);
                    }
                    Thread.Sleep(100);
                    if (i > 10)
                    {
                        if (!IsConnected(_client.Client))
                        {
                            OnDisconnected(DisconnectReason.ConnectionLost);
                            break;
                        }
                        i = 0;
                    }
                    i++;
                }
            }
            catch (Exception e)
            {
                OnDisconnected(DisconnectReason.ConnectionLost);
            }
        }
        /// <summary>
        /// Methode om te evalueren of er nog steeds connectie is met de andere instantie
        /// </summary>
        /// <param name="socket">TCPClient</param>
        /// <returns>True bij verbonden, False bij verbinding verbroken</returns>
        public bool IsConnected(Socket socket)
        {
            try
            {
                return !(socket.Poll(1000, SelectMode.SelectRead) && socket.Available == 0);
            }
            catch (SocketException) { return false; }
        }
    }
}
