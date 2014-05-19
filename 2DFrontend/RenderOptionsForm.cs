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
    partial class RenderOptionsForm : Form
    {
        private KaroPanel _karoPanel;

        public RenderOptionsForm(KaroPanel karoPanel)
        {
            InitializeComponent();
            _karoPanel = karoPanel;
            txtScale.Text = _karoPanel.Scale.ToString();
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            try
            {
                float scale = float.Parse(txtScale.Text);
                if (scale <= 0)
                    throw new Exception("Illegal Size");

                _karoPanel.Scale = scale;
                _karoPanel.Invalidate();
                txtScale.BackColor = SystemColors.Window;
            }
            catch (Exception)
            {
                txtScale.BackColor = Color.Red;
            }
        }
    }
}
