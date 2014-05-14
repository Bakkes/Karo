using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CommunicationProtocol
{
    /// <summary>
    /// Type van een zet. 
    /// </summary>
    public enum MoveType
    {
        /// <summary>
        /// Een 'jump'-zet springt over de tegenstander heen, zich 2 plekken verplaatsend.
        /// </summary>
        Jump,
        /// <summary>
        /// Een 'Move'-zet verplaatst zich 1 plek.
        /// </summary>
        Move,
        /// <summary>
        /// Een 'Insert'-zet voegt een steen aan het bord toe. Dit is de eerste fase van het spel.
        /// </summary>
        Insert
    }
    /// <summary>
    /// Richting voor aanduiding van 'to' locaties bij het verleggen van een tegel.
    /// </summary>
    public enum Direction
    {
        /// <summary>
        /// Geen, de ToTile geeft de directe locatie aan.
        /// </summary>
        None,
        /// <summary>
        /// Geeft de positie ten noorden van de ToTile aan.
        /// </summary>
        North,
        /// <summary>
        /// Geeft de positie ten oosten van de ToTile aan.
        /// </summary>
        East,
        /// <summary>
        /// Geeft de positie ten zuiden van de ToTile aan.
        /// </summary>
        South,
        /// <summary>
        /// Geeft de positie ten westen van de ToTile aan.
        /// </summary>
        West,

		NorthEast,

		NorthWest,

		SouthEast,

		SouthWest
    }
    /// <summary>
    /// Berichttype voor communicatie tussen client en server
    /// </summary>
    public enum MessageType
    {
        /// <summary>
        /// Bericht om verbonden event te triggeren bij andere instantie.
        /// </summary>
        Connected,
        /// <summary>
        /// Bericht om zet gedaan event te triggeren bij andere instantie.
        /// </summary>
        Turn,
        /// <summary>
        /// Bericht om disconnect event te triggeren bij andere instantie.
        /// </summary>
        Disconnect,
        /// <summary>
        /// Bericht om invalide zet event te triggeren bij andere instantie.
        /// </summary>
        SentMoveInvalid,
        /// <summary>
        /// Bericht om winst afgekeurd event te triggeren bij andere instantie.
        /// </summary>
        WinRejected,
        /// <summary>
        /// Bericht om winst gedetecteerd event te triggeren bij andere instantie.
        /// </summary>
        WinDetected,
        /// <summary>
        /// Bericht om winst geaccepteerd event te triggeren bij andere instantie.
        /// </summary>
        WinAccepted,
        /// <summary>
        /// Bericht om eerste zet event te triggeren bij andere instantie.
        /// </summary>
        RequestFirstMove
    }
    /// <summary>
    /// Reden van Disconnect
    /// </summary>
    public enum DisconnectReason
    {
        /// <summary>
        /// Bijgaande zet is invalide
        /// </summary>
        InvalidMove,
        /// <summary>
        /// Verbinding met andere insantie is verloren.
        /// </summary>
        ConnectionLost,
        /// <summary>
        /// Spel is afgelopen, de verbinding is verbroken.
        /// </summary>
        GameEnded,
        /// <summary>
        /// Spel is afgelopen, er is onenigheid over de winnaar. 
        /// Een scheidsrechter dient de winnaar te verklaren.
        /// </summary>
        WinnerDisputed
    }
    /// <summary>
    /// Aanduiding van speler, vanuit de versturende kant.
    /// </summary>
    public enum Player
    {
        /// <summary>
        /// Ontvangen speler
        /// </summary>
        You,
        /// <summary>
        /// Versturende speler
        /// </summary>
        Me
    }
}
