namespace _2DFrontend
{
    partial class LoadBox
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
            this.txtBoardString = new System.Windows.Forms.TextBox();
            this.btnLoad = new System.Windows.Forms.Button();
            this.btnCancel = new System.Windows.Forms.Button();
            this.numTLX = new System.Windows.Forms.NumericUpDown();
            this.numTLY = new System.Windows.Forms.NumericUpDown();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.cbPlayer = new System.Windows.Forms.ComboBox();
            ((System.ComponentModel.ISupportInitialize)(this.numTLX)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numTLY)).BeginInit();
            this.SuspendLayout();
            // 
            // txtBoardString
            // 
            this.txtBoardString.Dock = System.Windows.Forms.DockStyle.Top;
            this.txtBoardString.HideSelection = false;
            this.txtBoardString.Location = new System.Drawing.Point(0, 0);
            this.txtBoardString.Multiline = true;
            this.txtBoardString.Name = "txtBoardString";
            this.txtBoardString.Size = new System.Drawing.Size(523, 266);
            this.txtBoardString.TabIndex = 0;
            this.txtBoardString.KeyDown += new System.Windows.Forms.KeyEventHandler(this.txtBoardString_KeyDown);
            // 
            // btnLoad
            // 
            this.btnLoad.Location = new System.Drawing.Point(436, 272);
            this.btnLoad.Name = "btnLoad";
            this.btnLoad.Size = new System.Drawing.Size(75, 23);
            this.btnLoad.TabIndex = 1;
            this.btnLoad.Text = "Load";
            this.btnLoad.UseVisualStyleBackColor = true;
            this.btnLoad.Click += new System.EventHandler(this.btnLoad_Click);
            // 
            // btnCancel
            // 
            this.btnCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.btnCancel.Location = new System.Drawing.Point(13, 272);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(75, 23);
            this.btnCancel.TabIndex = 2;
            this.btnCancel.Text = "Cancel";
            this.btnCancel.UseVisualStyleBackColor = true;
            this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
            // 
            // numTLX
            // 
            this.numTLX.Location = new System.Drawing.Point(147, 275);
            this.numTLX.Maximum = new decimal(new int[] {
            19,
            0,
            0,
            0});
            this.numTLX.Name = "numTLX";
            this.numTLX.Size = new System.Drawing.Size(42, 20);
            this.numTLX.TabIndex = 3;
            // 
            // numTLY
            // 
            this.numTLY.Location = new System.Drawing.Point(195, 275);
            this.numTLY.Maximum = new decimal(new int[] {
            19,
            0,
            0,
            0});
            this.numTLY.Name = "numTLY";
            this.numTLY.Size = new System.Drawing.Size(42, 20);
            this.numTLY.TabIndex = 4;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(94, 277);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(47, 13);
            this.label1.TabIndex = 5;
            this.label1.Text = "Top Left";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(243, 277);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(76, 13);
            this.label2.TabIndex = 6;
            this.label2.Text = "Current Player:";
            // 
            // cbPlayer
            // 
            this.cbPlayer.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbPlayer.FormattingEnabled = true;
            this.cbPlayer.Items.AddRange(new object[] {
            "Green (Min)",
            "Red (Max)"});
            this.cbPlayer.Location = new System.Drawing.Point(325, 274);
            this.cbPlayer.Name = "cbPlayer";
            this.cbPlayer.Size = new System.Drawing.Size(105, 21);
            this.cbPlayer.TabIndex = 7;
            // 
            // LoadBox
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.btnCancel;
            this.ClientSize = new System.Drawing.Size(523, 307);
            this.ControlBox = false;
            this.Controls.Add(this.cbPlayer);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.numTLY);
            this.Controls.Add(this.numTLX);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.btnLoad);
            this.Controls.Add(this.txtBoardString);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "LoadBox";
            this.ShowIcon = false;
            this.ShowInTaskbar = false;
            this.Text = "Load from Board String";
            ((System.ComponentModel.ISupportInitialize)(this.numTLX)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numTLY)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox txtBoardString;
        private System.Windows.Forms.Button btnLoad;
        private System.Windows.Forms.Button btnCancel;
        private System.Windows.Forms.NumericUpDown numTLX;
        private System.Windows.Forms.NumericUpDown numTLY;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox cbPlayer;
    }
}