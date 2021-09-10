using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.IO.Ports;
using System.Xml;
using System.Windows.Forms.VisualStyles;
using System.Runtime.CompilerServices;

namespace dieukhien
{
    public partial class giaodiendieukhien : Form
    {
        const double pi = Math.PI;
        //%%%%%%%%%%%%%%%%%%%%%%%%
        const double L1 = 4.896;
        const double L2 = 15.00;
        const double L3 = 15.00;
        //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        const Int16 gioihantraithe1 = 91;
        const Int16 gioihanphaithe1 = -91;
        const Int16 gioihantrenthe2 = 101;
        const Int16 gioihanduoithe2 = 15;
        const Int16 gioihantrenthe3 = -40;
        const Int16 gioihanduoithe3 = -166;

        bool ktgioihan;
        //%%%%%%%%%%%%%%%%%%%%%%%%%
        double X, Y, Z;
        double the1, the2, the3;
        //%%%%%%%%%%%%%%%%%%%%%%%%%
        string g1, g2, g3;
        string time;
        //%%%%%%%%%%%%%%%%%%%%%%%%%%
        string home = "t 3 0.00 90.00 -165.00";
        //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        Int16 i;

        double[] the1qhqd = new double[200];
        double[] the2qhqd = new double[200];
        double[] the3qhqd = new double[200];


        //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

        //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        delegate void readdata(string text);
        public giaodiendieukhien()
        {
            InitializeComponent();
        }
        private void Form1_Load(object sender, EventArgs e) //dùng load các dữ liệu ban đầu khi mở form lên
        {
            string[] BaudRate = { "300", "1200", "2400", "4800", "9600", "19200", "38400", "57600", "74880", "115200", "230400", "250000", "500000", "1000000", "2000000"};
            cbbBR.Items.AddRange(BaudRate);
            cbbBR.SelectedIndex = 4;
            string[] comlist = SerialPort.GetPortNames();
            Array.Sort(comlist);
            cbbCOM.Items.AddRange(comlist);

            serialPort1.DataReceived += DataReceive;
        }

        //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        
        // các hàm liên quan tới việc kết nối xuống arduino

        private void btketnoi_Click(object sender, EventArgs e) //sự kiện nhấn nút kết nối tới cổng COM
        {
            if (cbbCOM.Text == "")
            {
                MessageBox.Show("Vui lòng chọn cổng COM", "Thông báo", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            else
            {
                try
                {

                    if (serialPort1.IsOpen)
                    {
                        serialPort1.Close();
                        btketnoi.Text = "Connect";
                        cbbCOM.Enabled = true;
                        cbbBR.Enabled = true;

                    }
                    else
                    {
                        serialPort1.PortName = cbbCOM.Text;
                        serialPort1.BaudRate = Convert.ToInt32(cbbBR.Text);
                        serialPort1.Open();
                        btketnoi.Text = "Disconnect";
                        cbbCOM.Enabled = false;
                        cbbBR.Enabled = false;
                    }
                }
                catch
                {
                    MessageBox.Show("Không thể kết nối tới cổng COM", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
        }   
        
        private void timer1_Tick(object sender, EventArgs e) //sau mỗi giây sẻ kiểm tra trạng thái kết nối của cổng COM
        {
            if (!serialPort1.IsOpen)
            {
                lbTTKN.Text = "Not Connected";
                lbTTKN.ForeColor = Color.Red;

                btketnoi.Text = "Connect";
                cbbCOM.Enabled = true;
                cbbBR.Enabled = true;
            }
            else
            {
                lbTTKN.Text = "Connected";
                lbTTKN.ForeColor = Color.Green;
            }
        }
        
        private void Form1_FormClosing(object sender, FormClosingEventArgs e) //đóng cửa sổ thì ngắt kết nối tới cổng COM
        {
            if (serialPort1.IsOpen)
            {
                serialPort1.Close();
            }
        }
        
        //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        
        //các hàm liên quan tới việc nhận và xử lí các dữ liệu giao tiếp giữa arduino và form
        
        private void DataReceive(object sender, SerialDataReceivedEventArgs e) //mỗi khi có dữ liệu được gửi lên thì nhận và xuất dữ liệu ra màn hình
        {
            try
            {
                if (serialPort1.IsOpen)
                {
                    string datainput = serialPort1.ReadLine();
                    if (datainput != null)
                    {
                        readdata data = new readdata(hienthidata);
                        this.Invoke(data, new object[] { datainput });
                    }
                }
            }
            catch
            {
            }
        }

        private void hienthidata(string text) //hàm xuất dữ liệu ra màn hình
        {
            tbdisplay.Text += "\n"+text;
            tbdisplay.SelectionStart = tbdisplay.Text.Length;
            tbdisplay.ScrollToCaret();

            if (text.Substring(0, 4) == "the1")
            {
                tbthe1.Text = text.Substring(5);
            }
            else if (text.Substring(0, 4) == "the2")
            {
                tbthe2.Text = text.Substring(5);
            }
            else if (text.Substring(0, 4) == "the3")
            {
                tbthe3.Text = text.Substring(5);
            }

            if ((tbthe1.Text != "") && (tbthe2.Text != "") && (tbthe3.Text != ""))
            {
                giaithuan(Convert.ToDouble(tbthe1.Text), Convert.ToDouble(tbthe2.Text), Convert.ToDouble(tbthe3.Text));
                tbtoadoxph.Text = Convert.ToString(X);
                tbtoadoyph.Text = Convert.ToString(Y);
                tbtoadozph.Text = Convert.ToString(Z);
            }
        }

        private void btxoa_Click(object sender, EventArgs e) //button xóa các dữ liệu cũ trên màn hình
        {
            tbdisplay.Clear();
        }

        private void btgui_Click(object sender, EventArgs e) //button gửi dữ liệu nhập trong ô data xuống arduino
        {
            try
            {
                if (tbdata.Text != "")
                {
                    serialPort1.Write(tbdata.Text);
                    tbdata.ResetText();
                }
                else if (tbdata.Text.Trim() == "")
                {
                    MessageBox.Show("Vui lòng nhập dữ liệu", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
            catch
            {
                MessageBox.Show("Không thể gửi dữ liệu", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void tbdata_KeyDown(object sender, KeyEventArgs e) //dùng nút enter trên phim để gửi dữ liệu
        {
            if (e.KeyCode == Keys.Enter)
            {
                btgui_Click(sender, e);
            }
        }

        private void bthome_Click(object sender, EventArgs e) //khi nhấn home thì về vị trí bắt đầu
        {
            try
            {
                serialPort1.Write(home);
            }
            catch
            {
                MessageBox.Show("Không thể gửi dữ liệu", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void btstop_Click(object sender, EventArgs e) //khi nhấn stop thì dừng robot
        {
            try
            {
                serialPort1.Write("p");
            }
            catch
            {
                MessageBox.Show("Không thể gửi dữ liệu", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void label1_Click(object sender, EventArgs e) //cập nhật dữ liệu từ arduino 
        {
            try
            {
                serialPort1.Write("d");
            }
            catch
            {
                MessageBox.Show("Không thể gửi dữ liệu", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

        //các hàm điều khiển theo chế độ 

        private void btchayvt_Click(object sender, EventArgs e) //điều khiển theo chế độ vận tốc 
        {
            string v1, v2, v3;
            if ((tbgocthe1v.Text == "") && (tbgocthe2v.Text == "") && (tbgocthe3v.Text == ""))
            {
                MessageBox.Show("Vui lòng nhập dữ liệu", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            else
            {
                //%%%%%%%%%%%%%%%%%%%%%%%%%

                if (tbgocthe1v.Text == "")
                {
                    tbgocthe1v.Text = tbthe1.Text;
                    g1 = tbgocthe1v.Text;
                }
                else
                    g1 = tbgocthe1v.Text;

                if (tbgocthe2v.Text == "")
                { 
                    tbgocthe2v.Text = tbthe2.Text;
                    g2 = tbgocthe2v.Text;
                }
                else
                    g2 = tbgocthe2v.Text;

                if (tbgocthe3v.Text == "")
                { 
                    tbgocthe3v.Text = tbthe3.Text;
                    g3 = tbgocthe3v.Text;
                }
                else
                    g3 = tbgocthe3v.Text;

                //%%%%%%%%%%%%%%%%%%%%%%%%%%%%

                if (tbtocdothe1.Text == "")
                {
                    v1 = "0";
                    tbtocdothe1.Text = "0";
                }
                else
                    v1 = tbtocdothe1.Text;

                if (tbtocdothe2.Text == "")
                {
                    v2 = "0";
                    tbtocdothe2.Text = "0";
                }
                else
                    v2 = tbtocdothe2.Text;

                if (tbtocdothe3.Text == "")
                {
                    v3 = "0";
                    tbtocdothe3.Text = "0";
                }
                else
                    v3 = tbtocdothe3.Text;

                //%%%%%%%%%%%%%%%%%%%%%%%%%%%%

                giaithuan(Convert.ToDouble(g1), Convert.ToDouble(g2), Convert.ToDouble(g3));
                tbtoadoxvantoc.Text = Convert.ToString(X);
                tbtoadoyvantoc.Text = Convert.ToString(Y);
                tbtoadozvantoc.Text = Convert.ToString(Z);

                //%%%%%%%%%%%%%%%%%%%%%%%%%%%%
                try
                {
                    serialPort1.Write("v " + g1 + " " + v1 + " " + g2 + " " + v2 + " " + g3 + " " + v3);
                }
                catch
                {
                    MessageBox.Show("Không thể gửi dữ liệu", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
        }

        private void btchaytime_Click(object sender, EventArgs e) // điều khiển theo chế độ thời gian đáp ứng
        {
            if (tbthoigian.Text == "")
                MessageBox.Show("Vui lòng nhập dữ liệu", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            else
                time = tbthoigian.Text;
            if ((tbgocthe1t.Text == "") && (tbgocthe2t.Text == "") && (tbgocthe3t.Text == ""))
            {
                MessageBox.Show("Vui lòng nhập dữ liệu", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            else
            {
                if (tbgocthe1t.Text == "")
                {
                    tbgocthe1t.Text = tbthe1.Text;
                    g1 = tbgocthe1t.Text;
                }
                else
                    g1 = tbgocthe1t.Text;

                if (tbgocthe2t.Text == "")
                {
                    tbgocthe2t.Text = tbthe2.Text;
                    g2 = tbgocthe2t.Text;
                }
                else
                    g2 = tbgocthe2t.Text;

                if (tbgocthe3t.Text == "")
                {
                    tbgocthe3t.Text = tbthe3.Text;
                    g3 = tbgocthe3t.Text;
                }
                else
                    g3 = tbgocthe3t.Text;

                //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

                giaithuan(Convert.ToDouble(g1), Convert.ToDouble(g2), Convert.ToDouble(g3));
                tbtoadoxtime.Text = Convert.ToString(X);
                tbtoadoytime.Text = Convert.ToString(Y);
                tbtoadoztime.Text = Convert.ToString(Z);

                //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
                try
                {
                    serialPort1.Write("t "+ time + " " + g1 + " " + g2 + " " + g3);
                }
                catch
                {
                    MessageBox.Show("Không thể gửi dữ liệu", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
        }

        private void btchaynghich_Click(object sender, EventArgs e) //điều khiển theo chế độ nghich
        {
            if ((tbtoadoxdat.Text == "") || (tbtoadoydat.Text == "") || (tbtoadozdat.Text == "") || (tbtimenghich.Text == ""))
            {
                MessageBox.Show("Vui lòng nhập dữ liệu", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            else
            {
                giainghich(Convert.ToDouble(tbtoadoxdat.Text), Convert.ToDouble(tbtoadoydat.Text), Convert.ToDouble(tbtoadozdat.Text),0);
                tbthe1nghich.Text = Convert.ToString(the1);
                tbthe2nghich.Text = Convert.ToString(the2);
                tbthe3nghich.Text = Convert.ToString(the3);

                try
                {
                    serialPort1.Write("t " + tbtimenghich.Text + " " + tbthe1nghich.Text + " " + tbthe2nghich.Text + " " + tbthe3nghich.Text);
                }
                catch
                {
                    MessageBox.Show("Không thể gửi dữ liệu", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
        }
        
        private void btchayqhqd_Click(object sender, EventArgs e) // điều khiển động cơ trong chế độ quy hoạch quỹ đạo
        {
            if ((tbxqhqd.Text == "") || (tbyqhqd.Text == "") || (tbzqhqd.Text == "") || (tbtimeqhqd.Text == ""))
            {
                MessageBox.Show("Vui lòng nhập dữ liệu, hoặc hệ thống đang bận", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            else
            {
                string[] tbx = tbxqhqd.Text.Split(',');
                string[] tby = tbyqhqd.Text.Split(',');
                string[] tbz = tbzqhqd.Text.Split(',');

                if ((tbx.Length == tby.Length) && (tbx.Length == tbz.Length))
                {
                    Int16 lengthqhqd = Convert.ToInt16(tbx.Length);

                    double dbut;
                    if (tbdbut.Text == "")
                    {
                        dbut = 0;
                    }
                    else
                    {
                        dbut = Convert.ToDouble(tbdbut.Text);
                    }

                    ktgioihan = true;

                    for (i = 0; i < lengthqhqd; i++)
                    {
                        giainghich(Convert.ToDouble(tbx[i]), Convert.ToDouble(tby[i]), Convert.ToDouble(tbz[i]), dbut);

                        if ((the1 > gioihantraithe1) || (the1 < gioihanphaithe1) || (the2 > gioihantrenthe2) || (the2 < gioihanduoithe2) || (the3 > gioihantrenthe3) || (the3 < gioihanduoithe3))
                        {
                            ktgioihan = false;
                        }

                        the1qhqd[i] = the1;
                        the2qhqd[i] = the2;
                        the3qhqd[i] = the3;
                    }

                    string texttheqh = "";
                    double timeqh = Convert.ToDouble(tbtimeqhqd.Text) / (lengthqhqd - 1);
                    timeqh = Math.Round(timeqh, 3);

                    for (i = 0; i < lengthqhqd; i++)
                    {
                        texttheqh += Convert.ToString(the1qhqd[i]) + ", ";
                    }
                    for (i = 0; i < lengthqhqd; i++)
                    {
                        texttheqh += Convert.ToString(the2qhqd[i]) + ", ";
                    }
                    for (i = 0; i < lengthqhqd; i++)
                    {
                        texttheqh += Convert.ToString(the3qhqd[i]) + ", ";
                    }

                    textBox1.Text = "b, " + Convert.ToString(lengthqhqd) + ", " + Convert.ToString(timeqh) + ", " + texttheqh;

                    if (ktgioihan == true)
                    {
                        try
                        {
                            serialPort1.Write("b, " + Convert.ToString(lengthqhqd) + ", " + Convert.ToString(timeqh) + ", " + texttheqh);
                        }
                        catch
                        {
                            MessageBox.Show("Không thể gửi dữ liệu", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                        }
                    }
                    else
                    {
                        MessageBox.Show("Số liệu nằm ngoài vùng hoạt động", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    }
                }
                else
                {
                    MessageBox.Show("Dữ liệu không hợp lệ", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
        }

        //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

        //chế độ circle

        private void ckbthuan_CheckedChanged(object sender, EventArgs e)
        {
            if (ckbnghich.Checked)
            {
                ckbnghich.Checked = false;
            }
        }

        private void ckbnghich_CheckedChanged(object sender, EventArgs e)
        {
            if (ckbthuan.Checked)
            {
                ckbthuan.Checked = false;
            }
        }

        private void btsendcircle_Click(object sender, EventArgs e)
        {
            if ((tbxcircle.Text != "") && (tbycircle.Text != "") && (tbzcircle.Text != "") && (tbrcircle.Text != "") && (tbtimecircle.Text != "") && (tbslpqhcircle.Text != ""))
            {
                if ((ckbthuan.Checked) || (ckbnghich.Checked))
                {
                    Int16 chieu;
                    if (ckbthuan.Checked)
                    {
                        chieu = 1;
                    }
                    else
                    {
                        chieu = -1;
                    }

                    double xtam = Convert.ToDouble(tbxcircle.Text);
                    double ytam = Convert.ToDouble(tbycircle.Text);
                    double ztam = Convert.ToDouble(tbzcircle.Text);

                    Int16 lengthcirclr = Convert.ToInt16(tbslpqhcircle.Text);

                    double rcircle = Convert.ToDouble(tbrcircle.Text);

                    double dcircle;
                    if (tbdcircle.Text == "")
                    {
                        dcircle = 0;
                    }
                    else
                    {
                        dcircle = Convert.ToDouble(tbdcircle.Text);
                    }

                    double xcircle;
                    double ycircle;
                    double zcircle;

                    ktgioihan = true;

                    for (i = 0; i < lengthcirclr; i++)
                    {
                        double goc = (chieu * 2 * pi * i) / (lengthcirclr - 1);
                        xcircle = xtam + rcircle * Math.Cos(goc);
                        ycircle = ytam + rcircle * Math.Sin(goc);
                        zcircle = ztam;
                        giainghich(xcircle, ycircle, zcircle, dcircle);

                        if ((the1 > gioihantraithe1) || (the1 < gioihanphaithe1) || (the2 > gioihantrenthe2) || (the2 < gioihanduoithe2) || (the3 > gioihantrenthe3) || (the3 < gioihanduoithe3))
                        {
                            ktgioihan = false;
                        }

                        the1qhqd[i] = the1;
                        the2qhqd[i] = the2;
                        the3qhqd[i] = the3;
                    }

                    double timecircle = Convert.ToDouble(tbtimecircle.Text) / (lengthcirclr - 1);
                    timecircle = Math.Round(timecircle, 3);

                    string textthecircle = "";
                    for (i = 0; i < lengthcirclr; i++)
                    {
                        textthecircle += Convert.ToString(the1qhqd[i]) + ", ";
                    }
                    for (i = 0; i < lengthcirclr; i++)
                    {
                        textthecircle += Convert.ToString(the2qhqd[i]) + ", ";
                    }
                    for (i = 0; i < lengthcirclr; i++)
                    {
                        textthecircle += Convert.ToString(the3qhqd[i]) + ", ";
                    }

                    textBox1.Text = "b, " + Convert.ToString(lengthcirclr) + ", " + Convert.ToString(timecircle) + ", " + textthecircle;
                    if (ktgioihan == true)
                    {
                        try
                        {
                            serialPort1.Write("b, " + Convert.ToString(lengthcirclr) + ", " + Convert.ToString(timecircle) + ", " + textthecircle);

                        }
                        catch
                        {
                            MessageBox.Show("Không thể gửi dữ liệu", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                        }
                    }
                    else
                    {
                        MessageBox.Show("Số liệu nằm ngoài vùng hoạt động", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    }
                }
                else
                {
                    MessageBox.Show("Vui lòng chọn chiều quay", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
            else
            {
                MessageBox.Show("Vui lòng nhập dữ liệu", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        //chế độ line

        private void btsendline_Click(object sender, EventArgs e)
        {
            if ((tbxlinebegin.Text != "") && (tbylinebegin.Text != "") && (tbzlinebegin.Text != "") && (tbxlineend.Text != "") && (tbylineend.Text != "") && (tbzlineend.Text != "") && (tbslpqdline.Text != "") && (tbtimeline.Text != ""))
            {
                double xb = Convert.ToDouble(tbxlinebegin.Text);
                double yb = Convert.ToDouble(tbylinebegin.Text);
                double zb = Convert.ToDouble(tbzlinebegin.Text);

                double xe = Convert.ToDouble(tbxlineend.Text);
                double ye = Convert.ToDouble(tbylineend.Text);
                double ze = Convert.ToDouble(tbzlineend.Text);

                double lengthline = Convert.ToDouble(tbslpqdline.Text);

                double dline;
                if (tbdline.Text == "")
                {
                    dline = 0;
                }
                else
                {
                    dline = Convert.ToDouble(tbdline.Text);
                }

                double xline;
                double yline;
                double zline;

                ktgioihan = true;

                for (i = 0 ; i < lengthline; i++)
                {
                    xline = xb + (xe - xb) * i / (lengthline - 1);
                    yline = yb + (ye - yb) * i / (lengthline - 1);
                    zline = zb + (ze - zb) * i / (lengthline - 1);

                    giainghich(xline, yline, zline, dline);

                    if ((the1 > gioihantraithe1) || (the1 < gioihanphaithe1) || (the2 > gioihantrenthe2) || (the2 < gioihanduoithe2) || (the3 > gioihantrenthe3) || (the3 < gioihanduoithe3))
                    {
                        ktgioihan = false;
                    }

                    the1qhqd[i] = the1;
                    the2qhqd[i] = the2;
                    the3qhqd[i] = the3;
                }

                double timeline = Convert.ToDouble(tbtimeline.Text) / (lengthline - 1);
                timeline = Math.Round(timeline, 3);

                string texttheline = "";
                for (i = 0; i < lengthline; i++)
                {
                    texttheline += Convert.ToString(the1qhqd[i]) + ", ";
                }
                for (i = 0; i < lengthline; i++)
                {
                    texttheline += Convert.ToString(the2qhqd[i]) + ", ";
                }
                for (i = 0; i < lengthline; i++)
                {
                    texttheline += Convert.ToString(the3qhqd[i]) + ", ";
                }

                textBox1.Text = "b, " + Convert.ToString(lengthline) + ", " + Convert.ToString(timeline) + ", " + texttheline;

                if (ktgioihan == true)
                {
                    try
                    {
                        serialPort1.Write("b, " + Convert.ToString(lengthline) + ", " + Convert.ToString(timeline) + ", " + texttheline);

                    }
                    catch
                    {
                        MessageBox.Show("Không thể gửi dữ liệu", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    }
                }
                else
                {
                    MessageBox.Show("Số liệu nằm ngoài vùng hoạt động", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
            else
            {
                MessageBox.Show("Vui lòng nhập dữ liệu", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

        //  tính thuận, tính nghịch
        private void giainghich(double Px, double Py, double Pz, double d) //tính động học nghich
        {
            if (Px == 0)
            {
                Px = 0.00001;
            }
            the1 = Math.Atan2(Py, Px);

            Px = Px - d * Math.Cos(the1);
            Py = Py - d * Math.Sin(the1);

            double x = Px - L1 * Math.Cos(the1);
            double y = Py - L1 * Math.Sin(the1);

            double anp = Math.Atan2(0, 2 * L3 * L2);
            the3 = anp + Math.Atan2(-Math.Sqrt((2 * L2 * L3) * (2 * L2 * L3) - (x * x + y * y + Pz * Pz - L2 * L2 - L3 * L3) * (x * x + y * y + Pz * Pz - L2 * L2 - L3 * L3)), (x * x + y * y + Pz * Pz - L2 * L2 - L3 * L3));
            the2 = Math.Atan2((Pz * (L3 * Math.Cos(the3) + L2) - L3 * Math.Sin(the3) * (Px / Math.Cos(the1) - L1)), (((Px / Math.Cos(the1) - L1) * (L3 * Math.Cos(the3) + L2) + L3 * Math.Sin(the3) * Pz)));

            the1 = Math.Round((the1 * 180 / pi),3);
            the2 = Math.Round((the2 * 180 / pi),3);
            the3 = Math.Round((the3 * 180 / pi),3);
        }

        private void giaithuan(double the1in, double the2in, double the3in) //tính động học thuan
        {
            the1in = the1in * pi / 180;
            the2in = the2in * pi / 180;
            the3in = the3in * pi / 180;
            X = Math.Cos(the1in) * (L1 + L3 * Math.Cos(the2in + the3in) + L2 * Math.Cos(the2in));
            Y = Math.Sin(the1in) * (L1 + L3 * Math.Cos(the2in + the3in) + L2 * Math.Cos(the2in));
            Z = L3 * Math.Sin(the2in + the3in) + L2 * Math.Sin(the2in);

            X = Math.Round(X, 3);
            Y = Math.Round(Y, 3);
            Z = Math.Round(Z, 3);
        }

    }
}
