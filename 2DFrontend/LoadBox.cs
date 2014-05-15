using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace _2DFrontend
{
    public partial class LoadBox : Form 
    {

        public string BoardString
        {
            get
            {
                return txtBoardString.Text;
            }
        }

        public int LeftTopX
        {
            get
            {
                return (int)numTLX.Value;
            }
        }

        public int LeftTopY
        {
            get
            {
                return (int)numTLY.Value;
            }
        }

        public LoadBox()
        {
            InitializeComponent();
            DialogResult = System.Windows.Forms.DialogResult.Cancel;
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            DialogResult = System.Windows.Forms.DialogResult.Cancel;
            Close();
        }

        private string RemoveFromString(string s, string[] characters)
        {
            string newString = String.Copy(s);
            foreach (string character in characters) {
                newString = newString.Replace(character, "");
            }

            return newString;
        }

        private void btnLoad_Click(object sender, EventArgs e)
        {
            txtBoardString.Text = RemoveFromString(txtBoardString.Text, new string[] { "\"", "\\n", " ", "\t", ";" });

            string boardString = RemoveFromString(txtBoardString.Text, new string[] { "\r", "\n" });
            string[] boardPieces = boardString.Split(new string[] { "," }, StringSplitOptions.RemoveEmptyEntries);

            if (txtBoardString.Text.Split('\n').Length != 20)
            {
                MessageBox.Show(String.Format("Invalid amount of lines detected. Expected: 20, Found: {0}", txtBoardString.Text.Split('\n').Length));
                return;
            }

            if (boardPieces.Length != 400)
            {
                MessageBox.Show(String.Format("Invalid amount of cells detected. Expected: 400, Found: {0}", boardPieces.Length));
                return;
            }

            foreach (string cell in boardPieces)
            {
                try
                {
                    Int32.Parse(cell);
                }
                catch (FormatException)
                {
                    MessageBox.Show(String.Format("Invalid Cell value detected: \"{0}\" is not an integer", cell));
                    return;
                }
            }

            DialogResult = System.Windows.Forms.DialogResult.OK;
            Close();
        }
    }
}
