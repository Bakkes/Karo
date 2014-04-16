using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using engine.wrapper;

namespace _2DFrontend
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            MoveWrapper mv;
            mv = new MoveWrapper(MoveType.JUMP, 0, 1, MoveDirection.NORTH, 2);
            KaroGame game = new KaroGame();
            game.ExecuteMove(new MoveWrapper(MoveType.JUMP, -20, 30, MoveDirection.SOUTH, 99), Players.Max);
            int test = 2;
            Vector2DWrapper vw = new Vector2DWrapper(20.0, 40.0);
            double x = vw.X;
            double y = vw.Y;

            vw.X = 10;
            vw.Y = 30;

            x = vw.X;
            y = vw.Y;
        }
    }
}
