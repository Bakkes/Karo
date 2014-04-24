using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CommunicationProtocol
{
    /// <summary>
    /// Versimpelde implementatie van een zet als generieke manier om te communiceren tussen twee verschillende implementaties van karo
    /// </summary>
    [Serializable()]
    public class Turn
    {
        /// <summary>
        /// Type zet
        /// </summary>
        /// <seealso cref="MoveType"/>
        public MoveType MoveType { get; set; }
        /// <summary>
        /// Nullable int FromTile. Dit is de plaats waar de te verplaatsen pion weg komt.
        /// Deze parameter is optioneel.
        /// </summary>
        public int? FromTile { get; set; }
        /// <summary>
        /// Nullabel int EmptyTile. Dit is de plaats waar een tegel weg gepakt wordt bij het veranderen van het bord.
        /// In dit geval is een Direction relatief aan de ToTile verplicht om aan te geven waar deze komt te liggen.
        /// Deze parameter is optioneel.
        /// </summary>
        /// <seealso cref="Direction"/>
        /// <seealso cref="ToTile"/>
        public int? EmptyTile { get; set; }
        /// <summary>
        /// Nullable int ToTile. Dit is de plaats waar de te verplaatsen pion heen gaat.
        /// Dit kan een relatieve positie zijn als Direction geen Direction.None is.
        /// </summary>
        /// <seealso cref="Direction"/>
        public int ToTile { get; set; }
        /// <summary>
        /// De direction wordt voor locaties op het bord op none gezet. Bij het aangeven van locaties die niet in het huidige bord liggen (het 'verbouwen' van het bord) wordt een relatieve positie meegegeven relatief aan de ToTile
        /// </summary>
        /// <seealso cref="ToTile"/>
        /// <seealso cref="Direction"/>
        public Direction Direction { get; set; }
        /// <summary>
        /// Bij winst wordt de move meegestuurd aan de andere instantie om te valideren. 
        /// Hierbij dient deze parameter op true gezet te worden.
        /// </summary>
        public bool isWinningMove { get; set; }
        /// <summary>
        /// Zet Turn om in een Message
        /// </summary>
        /// <returns>Message van messagetype Turn. Gevuld met de huidige turn.</returns>
        /// <seealso cref="Message"/>
        internal Message ToMessage()
        {
            Message m = new Message();
            m.Type = MessageType.Turn;
            m.Turn = this;
            return m;
        }
    }
}
