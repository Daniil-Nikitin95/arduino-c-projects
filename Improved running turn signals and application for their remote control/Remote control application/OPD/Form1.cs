using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;

namespace OPD
{
    public partial class Form1 : Form
    {
        SerialPort port;

        bool left = false, right = false, alarm = false;
        bool sound = true;

        int[] friq = new int[3] { 20, 30, 45 };

        public Form1()
        {
            InitializeComponent();
          
            label1.Text = String.Format("Скорость ленты: {0}", friq[0]);
            label2.Text = String.Format("Частота звукого сигнала: 2500");

            comboBox1.Items.Clear();
            comboBox1.Hide();   //список портов не виден, если порт == 1 или его нет

            string[] portnames = SerialPort.GetPortNames();

            if (portnames.Length == 0)
            {
                MessageBox.Show("COM Port не найден");
                this.Close();
                Application.Exit();
            }

            if (portnames.Length > 1)       //если есть несколько портов, то их список заносится в comboBox1, для подключения нужно выбрать порт и нажать Connect
            {
                comboBox1.Show();              
                button4.Text = "Connect";
                foreach (string s in portnames)
                {
                    comboBox1.Items.Add(s);
                }
            }

            if (portnames.Length == 1)      //при 1 порте все нормально
            {
                port = new SerialPort(portnames[0], 9600, Parity.None, 8, StopBits.One);
                port.Open();
                port.Write("4");    //устанавливам частоту в соответствии с начальной позицией скролла
            }

        }


        private void Form1_Load(object sender, EventArgs e)
        {

        }       

        

        private void button4_Click(object sender, EventArgs e)      //disconnect
        {
            left = false;
            right = false;
            alarm = false;

            if (!sound) port.Write("7");

            port.Write("0");
            Application.Exit();
        }
        private void button1_Click(object sender, EventArgs e)
        {
            right = false;
            alarm = false;

            if (left)
            {
                port.Write("0");
                left = false;
            }  
            else
            {
                port.Write("1");
                left = true;
            }                                                 
        }

        private void trackBar1_Scroll(object sender, EventArgs e)
        {                       
            if (trackBar1.Value == 0)
            {
                label1.Text = String.Format("Скорость ленты: {0}", friq[0]);
                port.Write("4");    //25
            }
            if (trackBar1.Value == 1)
            {
                label1.Text = String.Format("Скорость ленты: {0}", friq[1]);
                port.Write("5");    //30
            }
            if (trackBar1.Value == 2)
            {
                label1.Text = String.Format("Скорость ленты: {0}", friq[2]);
                port.Write("6");    //45
            }           
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)   //вкл/выкл звук пищалки
        {
            if (checkBox1.Checked) { trackBar2.Hide(); label2.Hide(); sound = false; }
            else { trackBar2.Show(); label2.Show(); sound = true; }
            port.Write("7");
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void trackBar2_Scroll(object sender, EventArgs e)
        {
            if (trackBar2.Value == 0)
            {
                label2.Text = String.Format("Частота звукого сигнала: 1000");
                port.Write("a");
            }
            if (trackBar2.Value == 1)
            {
                label2.Text = String.Format("Частота звукого сигнала: 1250");
                port.Write("b");
            }
            if (trackBar2.Value == 3)
            {
                label2.Text = String.Format("Частота звукого сигнала: 1500");
                port.Write("c");
            }
            if (trackBar2.Value == 4)
            {
                label2.Text = String.Format("Частота звукого сигнала: 1750");
                port.Write("d");
            }
            if (trackBar2.Value == 5)
            {
                label2.Text = String.Format("Частота звукого сигнала: 2000");
                port.Write("e");
            }
            if (trackBar2.Value == 6)
            {
                label2.Text = String.Format("Частота звукого сигнала: 2250");
                port.Write("f");
            }
            if (trackBar2.Value == 7)
            {
                label2.Text = String.Format("Частота звукого сигнала: 2500");
                port.Write("g");
            }
            if (trackBar2.Value == 8)
            {
                label2.Text = String.Format("Частота звукого сигнала: 2750");
                port.Write("h");
            }
            if (trackBar2.Value == 9)
            {
                label2.Text = String.Format("Частота звукого сигнала: 3000");
                port.Write("i");
            }
            if (trackBar2.Value == 10)
            {
                label2.Text = String.Format("Частота звукого сигнала: 3250");
                port.Write("j");
            }
            

        }

        private void button2_Click(object sender, EventArgs e)
        {
            left = false;
            alarm = false;

            if (right)
            {
                port.Write("0");
                right = false;
            }
            else
            {
                port.Write("3");
                right = true;
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            right = false;
            left = false;

            if (alarm)
            {
                port.Write("0");
                alarm = false;
            }
            else
            {
                port.Write("2");
                alarm = true;
            }
        }     
        
    }
}
