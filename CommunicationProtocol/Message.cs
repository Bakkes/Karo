using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CommunicationProtocol
{
    /// <summary>
    /// Standaard bericht type voor het communiceren over zetten en spelvoortgang.
    /// </summary>
    /// <seealso cref="MessageType"/>
    /// <seealso cref="Turn"/>
    [Serializable()]
    public class Message
    {
        /// <summary>
        /// Type communicatiebericht
        /// </summary>
        /// <seealso cref="MessageType"/>
        public MessageType Type { get; set; }
        /// <summary>
        /// Zet, gedaan of te doen, afhanklijk van het type bericht.
        /// </summary>
        /// <seealso cref="Turn"/>
        public Turn Turn { get; set; }
    }
    /// <summary>
    /// Uitbreiding voor de standaard berichten om informatie te bevatten over de disconnect
    /// </summary>
    /// <seealso cref="Message"/>
    /// <seealso cref="DisconnectReason"/>
    [Serializable()]
    public class DisconnectMessage : Message
    {
        /// <summary>
        /// Reden van disconnect.
        /// </summary>
        /// <seealso cref="DisconnectReason"/>
        public DisconnectReason Reason { get; set; }
    }
    /// <summary>
    /// Uitbreiding voor de standaard berichten om informatie te bevatten over de winst
    /// </summary>
    /// <seealso cref="Message"/>
    /// <seealso cref="Player"/>
    [Serializable()]
    public class WinDetectedMessage : Message
    {
        /// <summary>
        /// Winnende speler, gewoonlijk Player.Me voor de versturende speler bij winst voor hem/haar
        /// </summary>
        /// <seealso cref="Player"/>
        public Player Winner { get; set; }
    }
}
