using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using ProcessInterface;

namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        ImageProcess m_clsImageProcess = new ImageProcess();
        bool bOpenFlag = false;
        public Form1()
        {
            InitializeComponent();
            buttonUpdate(false);
        }

        private void btnOpenFile_Click(object sender, EventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.Filter = "Prt files (*.prt)|*.prt";
            dlg.FilterIndex = 1;
            dlg.RestoreDirectory = true;
            if (dlg.ShowDialog() == DialogResult.OK){
                tbPrtPath.Text = dlg.FileName;
                bOpenFlag = true;
                buttonUpdate(bOpenFlag);
            }
        }

        public void buttonUpdate(bool bFlag)
        {
            if(bFlag){
                btnCreatePreview.Enabled = true;
                btnPrint.Enabled = true;
            }
            else{
                btnCreatePreview.Enabled = false;
                btnPrint.Enabled = false;
            }
        }

        public void SetProcess(int nPos)
        {
            if(nPos >= 100)
            {
                progressBar.Value = 100;
            }
            else
            {
                progressBar.Value = nPos;
            }
        }

        private void btnCreatePreview_Click(object sender, EventArgs e)
        {
            string strPrview = tbPrtPath.Text.Substring(0, tbPrtPath.Text.Length - 4);
            strPrview += ".jpg";

            progressBar.Value = 0;
            progressBar.Minimum = 0;
            progressBar.Maximum = 100;

            ProcessInterface.cProcessPosCallback posFunc = new ProcessInterface.cProcessPosCallback(SetProcess);

            int nRef = ImageProcess.CreatePrtPreview((String)tbPrtPath.Text, posFunc);
            if (nRef == 0)
            {
                // 显示
                pbPreview.Load(strPrview);
                progressBar.Value = 100; // 如果已经存在预览文件则不重新生成，直接打开。
            }
            else if(nRef == 1)
            {
                MessageBox.Show("Open prt file is failed!!");
            }
            else if(nRef == 2){


                MessageBox.Show("Create preview file is failed!!");
            }
        }
    }
}
