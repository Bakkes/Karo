namespace _2DFrontend
{
    partial class Karo
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
			this.karoPanel1 = new _2DFrontend.KaroPanel();
			this.SuspendLayout();
			// 
			// karoPanel1
			// 
			this.karoPanel1.BackColor = System.Drawing.Color.CornflowerBlue;
			this.karoPanel1.Location = new System.Drawing.Point(12, 12);
			this.karoPanel1.Name = "karoPanel1";
			this.karoPanel1.Size = new System.Drawing.Size(800, 545);
			this.karoPanel1.TabIndex = 0;
			// 
			// Karo
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(1058, 569);
			this.Controls.Add(this.karoPanel1);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D;
			this.Name = "Karo";
			this.Text = "Karo";
			this.ResumeLayout(false);

        }

        #endregion

		private KaroPanel karoPanel1;

	}
}

