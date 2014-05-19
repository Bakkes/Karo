﻿using System;
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

        private void btnLoad_Click(object sender, EventArgs e)
        {
            string boardString = txtBoardString.Text.Replace("\r", "").Replace("\n", "").Replace(" ", "");
            string[] boardPieces = boardString.Split(new string[] { "," }, StringSplitOptions.RemoveEmptyEntries);

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
